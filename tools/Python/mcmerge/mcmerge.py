#!/usr/bin/env python3
"""Merge 2 or more McStas/McXtrace datasets (runs or scans, ASCII or NeXus) into one.

Runs with the same parameter values are pooled, weighted by their ray counts, as
if simulated in one run. Parameter values that differ give a scan dataset.
Anything doubtful is refused: --force overrides where a merge is still possible,
and marks the output with 'Merged_forced'.
"""
import argparse
import re
import shutil
import sys
from datetime import datetime
from pathlib import Path

import numpy as np

try:
    import h5py
except ImportError:  # only needed for NeXus
    h5py = None

TIMING_VERSION = (3, 10, 3)  # first release to mark completed runs with timings
CHUNK = 100000  # event list rows handled at a time
ENC = dict(encoding='utf-8', errors='surrogateescape')


class MergeError(Exception):
    pass


# Checks =======================================================================

class Guard:
    """Collects what is wrong: denied() can not be overridden, doubtful() can, by --force"""
    def __init__(self):
        self.hard, self.soft, self.warnings = [], [], []

    @staticmethod
    def _add(lst, msg):
        if msg not in lst:
            lst.append(msg)

    def denied(self, msg):
        self._add(self.hard, msg)

    def doubtful(self, msg):
        self._add(self.soft, msg)

    def warn(self, msg):
        self._add(self.warnings, msg)


# Statistics ===================================================================

def sigma(n, p, p2):
    """As mcestimate_error in mccode-r.c"""
    m = np.where(n > 1, n, 2.)
    return np.where(n > 1, np.sqrt(m/(m - 1)*np.abs(p2 - (p/m)**2)), p)


def second_moment(n, p, err):
    """p2 from the error bar, the inverse of sigma()"""
    m = np.where(n > 1, n, 1.)
    return np.where(n > 1, err**2*(m - 1)/m + (p/m)**2, err**2)


def pool(ncounts, n, p, err):
    """Pool (run, ...) arrays of events, intensities and errors. Returns n, p, err, p2"""
    w = np.asarray(ncounts, float)/np.sum(ncounts)
    w = w.reshape(-1, *[1]*(np.ndim(p) - 1))
    n_, p_ = n.sum(0), (w*p).sum(0)
    p2 = (w*w*second_moment(n, p, err)).sum(0)
    return n_, p_, sigma(n_, p_, p2), p2


# Data model ===================================================================

class Monitor:
    """One 'begin data' block. Arrays are (rows=y, columns=x), as in the ASCII files"""
    def __init__(self, head, kind):
        self.head, self.kind = head, kind
        self.I = self.E = self.N = None  # noqa: E741
        self.x = None       # 1D axis
        self.source = None  # list: (path, line of the last block) or (path, data set name)
        self.path = None    # NeXus: group path within the entry

    @property
    def columns(self):
        return self.head.get('variables', '').split()

    def values(self):
        """Total intensity, error, events"""
        try:
            v = [float(x) for x in self.head['values'].split()]
            return v if len(v) == 3 else [0., 0., 0.]
        except (KeyError, ValueError):
            return [0., 0., 0.]

    def is_log_signal(self):
        """Log of the signal (dropped from Monitor_nD): the intensity can not be recovered"""
        return '[log]' in self.head.get('title', '') or (
            self.kind == '1d' and '(log)' in self.head.get('ylabel', ''))

    def rows(self):
        """Number of events. The row count in 'type' is not reliable"""
        if self.source is None:
            return 0
        path, where = self.source
        if isinstance(where, str):
            with h5py.File(path, 'r') as f:
                return f[where].shape[0]
        with open(path, **ENC) as f:
            return sum(1 for i, s in enumerate(f) if i >= where and s.strip() and s[0] != '#')

    def events(self):
        """Event list in chunks"""
        if self.source is None:
            return
        path, where = self.source
        if isinstance(where, str):
            with h5py.File(path, 'r') as f:
                for i in range(0, f[where].shape[0], CHUNK):
                    yield f[where][i:i + CHUNK]
            return
        with open(path, **ENC) as f:
            chunk = []
            for i, s in enumerate(f):
                if i >= where and s.strip() and s[0] != '#':
                    chunk.append(s.split())
                    if len(chunk) == CHUNK:
                        yield np.array(chunk, float)
                        chunk = []
            if chunk:
                yield np.array(chunk, float)


class Run:
    def __init__(self, label):
        self.label = label
        self.instrument = {}      # 'begin instrument' block
        self.sim = {}             # 'begin simulation' block
        self.name = ''
        self.flavour = 'mccode'   # not recorded in NeXus
        self.params = {}
        self.mons = {}            # key -> Monitor
        self.timing = None        # Init, Trace, Finally [s]; None: not a completed run
        self.saves = False        # has intermediate saves
        self.ratio = False        # some block was written by an unfinished run
        self.text = None          # instrument source
        self.ncount = 0
        self.nodes = 1
        self.merged_from, self.merged_forced = [], []
        self.nexus = None         # (file, entry)
        self.dir = None

    @property
    def version(self):
        m = re.search(r'(\d+)\.(\d+)(?:\.(\d+))?', self.sim.get('Creator', ''))
        return tuple(int(x or 0) for x in m.groups()) if m else (0, 0, 0)

    @property
    def old(self):
        return self.version < TIMING_VERSION

    def seeds(self):
        """Seed ranges used: node i of an MPI run has seed+i"""
        lines = self.merged_from or [self.provenance()]
        return [(int(s), int(n)) for s, n in (re.search(r'Seed=(-?\d+) Nodes=(\d+)', x).groups() for x in lines)]

    def provenance(self):
        return 'Ncount=%i Seed=%s Nodes=%i Directory=%s' % (
            self.ncount, self.sim.get('Seed', '0'), self.nodes, self.label)

    def add(self, head, mon):
        """Monitors match on component and axes: file names may hold a time stamp"""
        axes = (head.get('xvar', '').strip(), head.get('yvar', '').strip() if mon.kind == '2d' else '')
        key = (head.get('component', ''), mon.kind, *axes)
        i = 0
        while (*key, i) in self.mons:
            i += 1
        self.mons[(*key, i)] = mon

    def finish(self):
        self.ratio = any('ratio' in m.head for m in self.mons.values())
        n = [int(float(m.head['Ncount'])) for m in self.mons.values() if 'Ncount' in m.head]
        self.ncount = max(n) if n else int(float(self.sim.get('Ncount', 0)))


def kind_of(head):
    m = re.match(r'(?:array_([0-3])d|(list))', head.get('type', ''))
    if not m:
        raise MergeError("unknown data type '%s' of %s" % (head.get('type'), head.get('component')))
    return 'list' if m[2] else {'0': '0d', '1': '1d'}.get(m[1], '2d')  # 3D is written as 2D


# ASCII input ==================================================================

def split_key(s):
    k, _, v = s.partition(':')
    return k.strip(), v.strip()


def read_ascii_run(d, label):
    run = Run(label)
    run.dir = d
    lines = (d/'mccode.sim').read_text(**ENC).splitlines()
    run.saves = sum(' simulation description file for ' in s for s in lines) > 1
    run.flavour = lines[0].split()[0]
    heads, sect, block = [], None, {}
    program = ''
    for s in lines:  # repeated blocks (intermediate saves): the last one is used
        if s.startswith('Program:'):
            program = split_key(s)[1]
        elif s.startswith('begin '):
            sect, block = s[6:].split(':')[0].strip(), {}
            if sect == 'instrument':
                run.name, run.instrument = split_key(s)[1], block
            elif sect == 'simulation':
                run.sim, run.merged_from, run.merged_forced = block, [], []
            elif sect == 'data':
                heads.append(block)
            elif sect == 'timing':
                run.timing = block
        elif s.startswith('end '):
            sect = None
        elif sect:
            k, v = split_key(s)
            if k == 'Param':
                name, _, value = v.partition('=')
                run.params[name] = value
            elif k == 'Merged_from':
                run.merged_from.append(v)
            elif k == 'Merged_forced':
                run.merged_forced.append(v)
            else:
                block[k] = v
    run.sim.setdefault('Creator', program)
    if run.timing is not None:
        run.timing = {k: float(v.split()[0]) for k, v in run.timing.items()}
    run.nodes = int(run.sim.get('Nodes', 1))
    # 2D and list blocks are only written at the first save: keep those
    for head in {(h.get('component'), h.get('filename')): h for h in heads}.values():
        mon = Monitor(head, kind_of(head))
        if mon.kind == '0d':
            i, e, n = mon.values()
            mon.I, mon.E, mon.N = np.array(i), np.array(e), np.array(n)
        else:
            f = d/head.get('filename', '')
            if not f.is_file():
                raise MergeError('%s: data file %s is missing' % (label, head.get('filename')))
            saves = load_ascii_monitor(mon, f, label)
            run.saves |= saves
            if saves and mon.kind == '2d' and not no_errors([mon]):  # header totals are of the first save
                update_statistics(mon, second_moment(mon.N, mon.I, mon.E))
        run.add(head, mon)
    for f in sorted(d.glob('*.instr'))[:1] or sorted(d.parent.glob('*.instr'))[:1]:
        run.text = f.read_text(**ENC)
    run.finish()
    return run


def load_ascii_monitor(mon, path, label):
    """Load the last data block of a file. Returns True if there are more blocks"""
    with open(path, **ENC) as f:
        marks = [(i, s[:6]) for i, s in enumerate(f) if s.startswith(('# Format:', '# Data ['))]
    starts = [i for i, s in marks if s == '# Form']
    blocks = [i for i, s in marks if s == '# Data'] or starts
    if not starts:
        raise MergeError('%s: %s is not a McCode text file' % (label, path.name))
    if mon.kind == 'list':
        mon.source = (path, blocks[-1])
        return len(blocks) > 1
    parts, rows = {}, []
    with open(path, **ENC) as f:
        for i, s in enumerate(f):
            if i < starts[-1]:
                continue
            m = re.match(r'# (Data|Errors|Events) \[', s)
            if m:
                rows = parts[m[1]] = []
            elif s.strip() and s[0] != '#':
                rows.append(s.split())
    try:
        if mon.kind == '1d':
            a = np.array(rows, float).reshape(-1, 4)
            mon.x, mon.I, mon.E, mon.N = a.T
        else:
            a = {k: np.array(v, float) for k, v in parts.items()}
            mon.I, mon.E, mon.N = a['Data'], a.get('Errors'), a.get('Events')
    except (ValueError, KeyError) as e:
        raise MergeError('%s: can not read %s: %s' % (label, path.name, e))
    return len(blocks) > 1


# NeXus input ==================================================================

def text(v):
    if isinstance(v, np.ndarray) and v.size:
        v = v.flat[0]
    return v.decode('utf-8', 'surrogateescape') if isinstance(v, bytes) else str(v)


def attrs(obj):
    return {k: text(v).strip() for k, v in obj.attrs.items()}


def read_nexus(path, label):
    if h5py is None:
        raise MergeError('%s: NeXus needs the h5py Python package' % label)
    with h5py.File(path, 'r') as f:
        names = [k for k in f if text(f[k].attrs.get('NX_class', '')) == 'NXentry']
        names.sort(key=lambda k: int(re.sub(r'\D', '', k) or 0))
        runs = []
        for k in names:
            run = read_nexus_entry(f[k], path, label if len(names) == 1 else '%s/%s' % (label, k))
            # same parameters and seed as the entry before: that one was an intermediate save
            if runs and (runs[-1].params, runs[-1].sim.get('Seed')) == (run.params, run.sim.get('Seed')) \
                    and runs[-1].timing is None:
                runs.pop()
                run.saves = True
            runs.append(run)
    return runs


def read_nexus_entry(e, path, label):
    run = Run(label)
    run.dir, run.nexus = path.parent, (path, e.name.strip('/'))
    run.sim = attrs(e['simulation'])
    run.sim['Creator'] = run.sim.pop('program', attrs(e).get('program_name', ''))
    run.sim['Ncount'] = run.sim.pop('Ncount_requested', run.sim.get('Ncount', 0))
    for k in ('Merged_from', 'Merged_forced'):
        setattr(run, k.lower(), [s for s in run.sim.pop(k, '').split('\n') if s])
    if 'Param' in e['simulation']:
        run.params = {k: v for k, v in attrs(e['simulation/Param']).items() if k != 'NX_class'}
    run.instrument = attrs(e['instrument'])
    run.name = run.instrument.pop('name', '')
    run.instrument.pop('NX_class', None)
    if 'description' in e['instrument']:
        run.text = text(e['instrument/description'][()])
    if 'timing_init' in e:
        run.timing = {k: float(text(e['timing_' + k.lower()][()]).split()[0]) for k in ('Init', 'Trace', 'Finally')}
    # the number of MPI nodes is not recorded, only seen from the event lists
    run.nodes = max(1, int(run.sim.pop('Nodes', 0)), len(list(path.parent.glob('mccode_node*.h5'))))
    if 'components' in e['instrument']:
        groups = [g['output'][o] for g in e['instrument/components'].values() if 'output' in g for o in g['output']]
    else:
        groups = list(e['data'].values())
    for g in groups:
        head = attrs(g)
        if 'type' not in head:  # e.g. pixel index maps
            continue
        mon = Monitor(head, kind_of(head))
        mon.path = g.name[len(e.name) + 1:]
        if 'dataset columns' in head:
            head['variables'] = head['dataset columns']
        if mon.kind == '0d':
            mon.I, mon.E, mon.N = np.array(mon.values())
        elif mon.kind == 'list':
            if 'events' in g:
                ds = g['events']
                for v in ds.virtual_sources() if ds.is_virtual else ():
                    if not (path.parent/v.file_name).is_file():  # would read as zeros
                        raise MergeError('%s: event file %s is missing' % (label, v.file_name))
                mon.source = (path, ds.name)
        else:
            mon.I, mon.E, mon.N = (g[k][()].reshape(g[k].shape[0], -1).T if k in g else None
                                   for k in ('data', 'errors', 'ncount'))
            if mon.kind == '1d':
                mon.I, mon.E, mon.N = (None if a is None else a.ravel() for a in (mon.I, mon.E, mon.N))
                mon.x = next((d[()] for d in g.values() if 'axis' in d.attrs), np.arange(mon.I.size, dtype=float))
        run.add(head, mon)
    run.finish()
    return run


# Datasets =====================================================================

def read_dataset(arg, guard):
    """All runs of a dataset: one, or the steps of a scan"""
    d = Path(arg)
    if d.is_file():
        d = d.parent
    label = str(arg)
    if not d.is_dir():
        raise MergeError('%s: no such dataset' % label)
    scan = (d/'mccode.dat').is_file()
    if (d/'mccode.h5').is_file():
        runs = read_nexus(d/'mccode.h5', label)
    elif scan:
        steps = sorted((s for s in d.iterdir() if s.name.isdigit()), key=lambda s: int(s.name))
        runs = []
        for s in steps:
            if not (s/'mccode.sim').is_file():
                guard.denied('%s/%s: incomplete scan step' % (label, s.name))
            else:
                runs.append(read_ascii_run(s, '%s/%s' % (label, s.name)))
    elif (d/'mccode.sim').is_file():
        runs = [read_ascii_run(d, label)]
    else:
        raise MergeError('%s: neither mccode.sim nor mccode.h5 found' % label)
    if not runs:
        raise MergeError('%s: no runs found' % label)
    if scan:
        m = re.search(r'^# Numpoints: (\d+)', (d/'mccode.dat').read_text(**ENC), re.M)
        # ponytail: mcrun -M writes the points per parameter, so a short multi-scan is not seen here
        if m and len(runs) < int(m[1]):
            guard.denied('%s: incomplete scan, %i of %s steps' % (label, len(runs), m[1]))
    return runs


def normalise(v):
    try:
        return float(v)
    except ValueError:
        return v


def check_runs(runs, guard):
    first = runs[0]
    for r in runs:
        if r.ratio or (r.timing is None and not r.old):
            guard.denied('%s: interrupted run, its ray count is unknown' % r.label)
        elif r.timing is None:
            guard.doubtful('%s: made by %s, before %s: may be an interrupted run' % (
                r.label, r.sim['Creator'] or 'an unknown version', '.'.join(map(str, TIMING_VERSION))))
        if r.ncount < 1:
            guard.denied('%s: no rays' % r.label)
        if r.saves and r.version <= TIMING_VERSION:
            guard.doubtful('%s: has intermediate saves, its error bars may be wrong' % r.label)
        elif r.saves:
            guard.warn('%s: has intermediate saves, the last one is used' % r.label)
        if r.sim.get('Instrument') != first.sim.get('Instrument') or r.name != first.name:
            guard.denied('%s: other instrument (%s) than %s (%s)' % (
                r.label, r.sim.get('Instrument'), first.label, first.sim.get('Instrument')))
        elif sorted(r.mons) != sorted(first.mons):
            names = ', '.join(sorted({k[0] for k in set(r.mons) ^ set(first.mons)}))
            guard.denied('%s: other monitors than %s: %s' % (r.label, first.label, names))
        for k in ('Creator', 'Gravitation', 'Trace'):
            if r.sim.get(k) != first.sim.get(k):
                guard.doubtful('%s: %s is %s, but %s in %s' % (r.label, k, r.sim.get(k), first.sim.get(k), first.label))
        if r.text and first.text and r.text.split() != first.text.split():
            guard.doubtful('%s: other instrument source than %s' % (r.label, first.label))
        for m in r.merged_forced:
            guard.warn('%s: already a forced merge: %s' % (r.label, m))


def group_runs(runs, guard):
    """Group the runs on parameter values. Returns the groups and the parameters that differ"""
    names = list(dict.fromkeys(k for r in runs for k in r.params))
    for k in list(names):
        unknown = [r for r in runs if k not in r.params
                   or (r.params[k] == 'NULL' and not re.search(r'\b%s\(string\)' % re.escape(k),
                                                               r.instrument.get('Parameters', '')))]
        if unknown:
            guard.doubtful('%s: value of parameter %s not recorded, taken as equal' % (unknown[0].label, k))
            names.remove(k)
        elif any(r.params[k] == 'NULL' and r.version <= TIMING_VERSION for r in runs):
            guard.warn('parameter %s is NULL: the value may not have been recorded' % k)
    groups = {}
    for r in runs:
        groups.setdefault(tuple(normalise(r.params[k]) for k in names), []).append(r)
    differ = [i for i in range(len(names)) if len({g[i] for g in groups}) > 1]
    keys = list(groups)
    if all(isinstance(g[i], float) for g in keys for i in differ):
        keys.sort(key=lambda g: [g[i] for i in differ])
    return [groups[k] for k in keys], [names[i] for i in differ]


def check_group(group, guard):
    """Can these runs be pooled?"""
    if len(group) < 2:
        return
    ranges = sorted((s, s + n, r.label) for r in group for s, n in r.seeds())
    for a, b in zip(ranges, ranges[1:]):
        if b[0] < a[1]:
            guard.doubtful('%s and %s: seeds overlap, so the runs are not independent' % (a[2], b[2]))
    if any(r.nexus for r in group) and any(0 < b[0] - a[0] < 1000 for a, b in zip(ranges, ranges[1:])):
        guard.warn('%s: NeXus does not record the number of MPI nodes: seeds must be at least that far apart'
                   % group[0].label)
    first = group[0]
    for key in first.mons:
        mons = [r.mons[key] for r in group]
        m, name = mons[0], first.mons[key].head.get('filename') or key[0]
        if any(x.is_log_signal() for x in mons):
            guard.denied('%s: %s holds the log of the signal, the intensity is lost' % (first.label, name))
        if m.kind == 'list':
            if any(x.columns != m.columns for x in mons):
                guard.denied('%s: %s has other columns in another run' % (first.label, name))
            elif 'p' not in m.columns:
                guard.doubtful('%s: event list %s has no p column, so events are not scaled' % (first.label, name))
            continue
        if any(np.shape(x.I) != np.shape(m.I) for x in mons):
            guard.denied('%s: %s has another number of bins in another run' % (first.label, name))
            continue
        if any(limits(x) != limits(m) for x in mons):
            guard.doubtful('%s: %s has other limits in another run (auto limits?), adding its bins is wrong'
                           % (first.label, name))
        if no_errors(mons):
            guard.warn('%s has no error bars, only its intensity is averaged' % name)
            continue
        v = np.array([x.values() for x in mons])
        ok = (v[:, 1] > 0) & (v[:, 2] > 10)
        i, e = v[ok, 0], v[ok, 1]
        z = np.abs(i[:, None] - i)/np.hypot(e[:, None], e) if len(i) else np.zeros(1)
        if z.max() > 5:
            guard.doubtful('%s: the intensities in %s differ by %.1f sigma' % (first.label, name, z.max()))


def limits(mon):
    s = mon.head.get('xlimits') or mon.head.get('xylimits') or ''
    return [normalise(x) for x in s.split()]


def no_errors(mons):
    return mons[0].kind not in ('list', '0d') and any(
        x.E is None or x.N is None or (not np.any(x.E) and np.any(x.I)) for x in mons)


# Merging ======================================================================

def merge_group(group, label, forced):
    """One run from runs with the same parameters. A single run is kept as it is"""
    first = group[0]
    out = Run(label)
    for k in ('instrument', 'sim', 'name', 'flavour', 'params', 'text', 'dir', 'nodes'):
        setattr(out, k, getattr(first, k))
    out.sim = dict(first.sim, Directory=label)
    out.template = next((r for r in group if r.nexus), None)
    out.ncount = sum(r.ncount for r in group)
    out.sim['Ncount'] = str(out.ncount)
    if all(r.timing for r in group):
        out.timing = {k: sum(r.timing.get(k, 0) for r in group) for k in ('Init', 'Trace', 'Finally')}
    if len(group) > 1:
        out.merged_from = [s for r in group for s in r.merged_from or [r.provenance()]]
    else:
        out.merged_from = first.merged_from
    out.merged_forced = list(dict.fromkeys([*forced, *(s for r in group for s in r.merged_forced)]))
    for key in first.mons:
        mons = [r.mons[key] for r in group]
        m = Monitor(dict(mons[0].head), mons[0].kind)
        m.x, m.parts = mons[0].x, list(zip(mons, [r.ncount/out.ncount for r in group]))
        m.head['Ncount'] = str(out.ncount)
        if len(group) == 1:
            m.I, m.E, m.N = mons[0].I, mons[0].E, mons[0].N
        elif m.kind != 'list':
            merge_histogram(m, mons, [r.ncount for r in group])
        out.mons[key] = m
    return out


def merge_histogram(m, mons, ncounts):
    p = np.array([x.I for x in mons], float)
    if no_errors(mons):
        m.I = np.average(p, axis=0, weights=ncounts)
        m.E = None if mons[0].E is None else np.zeros_like(m.I)
        m.N = None if any(x.N is None for x in mons) else np.sum([x.N for x in mons], axis=0)
        p2 = np.zeros_like(m.I)
    else:
        m.N, m.I, m.E, p2 = pool(ncounts, np.array([x.N for x in mons], float), p,
                                 np.array([x.E for x in mons], float))
    update_statistics(m, p2)


def update_statistics(m, p2):
    """Header totals, as mcdetector_statistics in mccode-r.c"""
    n = m.N if m.N is not None else np.ones_like(m.I)
    ok = np.isfinite(m.I) & np.isfinite(p2) & np.isfinite(n)
    total, events = m.I[ok].sum(), n[ok].sum()
    err = float(sigma(events, total, p2[ok].sum())) if events and not (m.E is not None and not np.any(m.E)) else 0
    m.head['values'] = '%g %g %g' % (total, err, events)
    if m.kind == '0d':
        return
    z = np.where(ok, m.I, 0)
    m.head['signal'] = 'Min=%g; Max=%g; Mean=%g;' % (
        (*((m.I[ok].min(), m.I[ok].max()) if ok.any() else (0, 0)), total/m.I.size))
    lim = limits(m)
    out = []
    for axis, name in ((-1, 'X'), (0, 'Y'))[:m.I.ndim]:
        lo, hi = lim[:2] if name == 'X' else lim[2:4]
        x = lo + (np.arange(m.I.shape[axis]) + 0.5)/m.I.shape[axis]*(hi - lo)
        zx = z if m.I.ndim == 1 else z.sum(0 if name == 'X' else 1)
        mean = (x*zx).sum()/total if total else 0
        var = (x*x*zx).sum()/total - mean**2 if total else 0
        out.append('%s0=%g; d%s=%g;' % (name, mean, name, np.sqrt(max(var, 0))))
    m.head['statistics'] = ' '.join(out)


# ASCII output =================================================================

def sim_header(run):
    """Lines of the 'begin simulation' block, also on top of data files"""
    sim = dict(run.sim)
    sim['Format'] = 'McCode with text headers'
    keys = ('Format', 'URL', 'Creator', 'Instrument', 'Ncount', 'Trace', 'Gravitation', 'Seed', 'Directory', 'Nodes')
    if not run.merged_from and run.nodes > 1:
        sim['Nodes'] = str(run.nodes)
    elif run.merged_from:
        sim.pop('Nodes', None)
    out = ['%s: %s' % (k, sim[k]) for k in keys if k in sim]
    out += ['Param: %s=%s' % kv for kv in run.params.items()]
    out += ['Merged_from: ' + s for s in run.merged_from]
    out += ['Merged_forced: ' + s for s in run.merged_forced]
    return out


def data_header(mon):
    head = dict(mon.head)
    if mon.kind == 'list':
        rows, cols = sum(x.rows() for x, _ in mon.parts), len(mon.columns)
        head.update(type='list(%i, %i)' % (cols, rows), xylimits='1 %i 1 %i' % (rows, cols),
                    signal=list_signal(mon))
    lim = 'xlimits' if mon.kind == '1d' else 'xylimits'
    if lim not in head:
        head[lim] = head.get('xlimits', head.get('xylimits', '0 0 0 0 0 0'))
    keys = ['Date', 'type', 'Source', 'component', 'position', 'title', 'Ncount', 'filename', 'statistics',
            'signal', 'values']
    if mon.kind != '0d':
        keys += ['xvar', 'yvar', 'xlabel', 'ylabel']
        if mon.kind != '1d':
            keys += ['zvar', 'zlabel']
    return ['%s: %s' % (k, head[k]) for k in keys + [lim, 'variables'] if k in head]


def list_signal(mon):
    """The first weight, as the runtime does"""
    for part, w in mon.parts:
        for a in part.events():
            p = a[0, 0]*(w if mon.columns[:1] == ['p'] else 1)
            return 'Min=%g; Max=%g; Mean=0;' % (p, p)
    return 'None'


def scaled_events(mon):
    """Events of all runs, with their weights on the joint statistics"""
    for part, w in mon.parts:
        for a in part.events():
            if 'p' in mon.columns:
                a[:, mon.columns.index('p')] *= w
            yield a


def write_ascii_run(run, d, label):
    d.mkdir(parents=True)
    sim = ['%s simulation description file for %s.' % (run.flavour, run.name),
           'Date:    ' + datetime.now().strftime('%a %b %d %H:%M:%S %Y'),
           'Program: ' + run.sim.get('Creator', ''), '', 'begin instrument: ' + run.name]
    sim += ['  %s: %s' % kv for kv in run.instrument.items()]
    sim += ['end instrument', '', 'begin simulation: ' + label]
    sim += ['  ' + s for s in sim_header(run)] + ['end simulation']
    for mon in run.mons.values():
        head = data_header(mon)
        sim += ['', 'begin data'] + ['  ' + s for s in head] + ['end data']
        if not mon.head.get('filename'):
            continue
        top = sim_header(run)
        if mon.kind == 'list':
            top[0] = 'Format: McCode list with text headers'
        with open(d/mon.head['filename'], 'w', newline='\n', **ENC) as f:
            f.write(''.join('# %s\n' % s for s in top + head))
            tag = '[%s/%s]' % (mon.head['component'], mon.head['filename'])
            if mon.kind == '0d':
                f.write(mon.head['values'] + ' \n')
            elif mon.kind == '1d':
                zero = np.zeros_like(mon.I)
                write_rows(f, np.column_stack([mon.x, mon.I, zero if mon.E is None else mon.E,
                                               zero if mon.N is None else mon.N]))
            elif mon.kind == 'list':
                f.write('# Data %s %s:\n' % (tag, mon.head.get('zvar', 'I')))
                for a in scaled_events(mon):
                    write_rows(f, a)
            else:
                for name, var, a in (('Data', mon.head.get('zvar', 'I'), mon.I), ('Errors', 'I_err', mon.E),
                                     ('Events', 'N', mon.N)):
                    if a is not None:
                        f.write('# %s %s %s:\n' % (name, tag, var))
                        write_rows(f, a)
    if run.timing:  # marks a completed run
        sim += ['', 'begin timing'] + ['  %s: %.2f [s]' % kv for kv in run.timing.items()] + ['end timing']
    (d/'mccode.sim').write_text('\n'.join(sim) + '\n', **ENC)


def write_rows(f, a):
    np.savetxt(f, a, fmt='%.10g', newline=' \n')


# NeXus output =================================================================

def nx_text(s):
    return np.bytes_(str(s).encode('utf-8', 'surrogateescape') or b' ')


def nx_group(parent, name, nxclass):
    g = parent.require_group(name)
    g.attrs['NX_class'] = nx_text(nxclass)
    return g


def copy_tree(src, dst, seen):
    """Copy a group without its event lists, keeping hard links"""
    for k, v in src.attrs.items():
        dst.attrs[k] = v
    for k in src:
        if src.get(k, getlink=True).__class__ is not h5py.HardLink or k == 'events':
            continue
        obj = src[k]
        addr = h5py.h5o.get_info(obj.id).addr
        if addr in seen:
            dst[k] = dst.file[seen[addr]]
        elif isinstance(obj, h5py.Group):
            g = dst.create_group(k)
            seen[addr] = g.name
            copy_tree(obj, g, seen)
        else:
            src.copy(obj, dst, name=k)
            seen[addr] = dst[k].name


def replace_text(g, name, s):
    if name in g:
        del g[name]
    g.create_dataset(name, data=np.array([s.encode()]))


def write_nexus_entry(run, out, name, label):
    e = nx_group(out, name, 'NXentry')
    if run.template:
        path, old = run.template.nexus
        with h5py.File(path, 'r') as f:
            copy_tree(f[old], e, {})
        fix = re.compile('^/%s/' % re.escape(old))

        def retarget(_, obj):
            if 'target' in obj.attrs:
                obj.attrs['target'] = nx_text(fix.sub('/%s/' % name, text(obj.attrs['target'])))
        e.visititems(retarget)
    else:  # from ASCII: no geometry or component parameters
        e.attrs['program_name'] = nx_text(run.sim.get('Creator', ''))
        nx_group(e, 'data', 'NXdetector')
        inst = nx_group(e, 'instrument', 'NXinstrument')
        for k, v in dict(run.instrument, name=run.name).items():
            inst.attrs[k] = nx_text(v)
        if run.text:
            replace_text(inst, 'description', run.text)
        par = nx_group(nx_group(e, 'simulation', 'NXnote'), 'Param', 'NXparameters')
        for k, v in run.params.items():
            par.attrs[k] = nx_text(v)
            replace_text(par, k, v)
    sim = e['simulation']
    for k in ('Format', 'URL', 'Instrument', 'Trace', 'Gravitation', 'Seed'):
        if k in run.sim:
            sim.attrs[k] = nx_text('NeXus' if k == 'Format' else run.sim[k])
    sim.attrs['program'] = nx_text(run.sim.get('Creator', ''))
    sim.attrs['Ncount_requested'] = nx_text(run.ncount)
    sim.attrs['Directory'] = nx_text(label)
    sim.attrs['name'] = nx_text(label + '/mccode')
    if run.nodes > 1 and not run.merged_from:
        sim.attrs['Nodes'] = nx_text(run.nodes)
    for k, v in (('Merged_from', run.merged_from), ('Merged_forced', run.merged_forced)):
        if v:
            sim.attrs[k] = nx_text('\n'.join(v))
    if run.timing:
        for k, v in run.timing.items():
            replace_text(e, 'timing_' + k.lower(), '%.2f [s]' % v)
    comps = list(dict.fromkeys(k[0] for k in run.mons))
    for key, mon in run.mons.items():
        if run.template:
            g = e[run.template.mons[key].path]
        else:
            c = nx_group(e, 'instrument/components/%04i_%s' % (comps.index(key[0]) + 1, key[0]), 'NXdata')
            name = re.sub(r'\W', '_', mon.head.get('filename') or key[0])
            g = nx_group(nx_group(c, 'output', 'NXdetector'), name, 'NXdata')
            if mon.kind != '0d' and name not in e['data']:
                e['data'][name] = g
        write_nexus_monitor(mon, g)


def write_nexus_monitor(mon, g):
    for k, v in mon.head.items():
        if k in g.attrs or 'data' not in g:
            g.attrs[k] = nx_text(v)
    if mon.kind == 'list':
        rows, cols = sum(x.rows() for x, _ in mon.parts), len(mon.columns)
        g.attrs['type'] = nx_text('list(%i, %i)' % (rows, cols))
        g.attrs['xylimits'] = nx_text('1 %i 1 %i' % (rows, cols))
        g.attrs['dataset columns'] = nx_text(mon.head.get('variables', ''))
        g.attrs['signal'] = nx_text(list_signal(mon))
        ds = g.create_dataset('events', (rows, cols), 'f8', chunks=(max(1, min(rows, 8192)), cols),
                              compression='gzip', compression_opts=1)
        ds.attrs['signal'] = nx_text(1)
        i = 0
        for a in scaled_events(mon):
            ds[i:i + len(a)] = a
            i += len(a)
    elif mon.kind != '0d':
        for name, a in (('data', mon.I), ('errors', mon.E), ('ncount', mon.N)):
            if a is None:
                continue
            a = a.T
            if name in g:
                g[name][...] = a.reshape(g[name].shape)
            else:
                g.create_dataset(name, data=a)
                if name == 'data':
                    g[name].attrs['signal'] = nx_text(1)
        if not any('axis' in d.attrs for d in g.values()):
            lim = limits(mon)
            for i, n in enumerate(mon.I.T.shape):
                lo, hi = lim[2*i:2*i + 2]
                ds = g.create_dataset('xy'[i] + 'axis', data=lo + (np.arange(n) + 0.5)/n*(hi - lo))
                ds.attrs['axis'] = nx_text(i + 1)
                ds.attrs['long_name'] = nx_text(mon.head.get('xy'[i] + 'label', ''))


# Scan files ===================================================================

def write_scan_files(points, names, d, nexus):
    """mccode.dat, and mccode.sim for ASCII, as written by mcrun"""
    first = points[0]
    cols = []  # numbers of a scan parameter, or its index if not a number
    for k in names:
        vals = [r.params[k] for r in points]
        num = [normalise(v) for v in vals]
        uniq = list(dict.fromkeys(vals))
        cols.append(num if all(isinstance(v, float) for v in num) else [float(uniq.index(v)) for v in vals])
    keys = [k for k in first.mons if not (nexus and k[1] == 'list')]
    dets = [k[0] for k in keys]
    xvars = ', '.join(names)
    head = {
        'Date': datetime.now().strftime('%a %b %d %H %M %Y'),
        'Ncount': first.ncount,
        'Numpoints': len(points),
        'Param': ', '.join('%s = %s' % (k, first.params[k]) for k in names),
        'type': 'multiarray_1d(%i)' % len(points),
        'title': 'Scan of ' + xvars,
        'xlabel': "'%s'" % xvars,
        'ylabel': "'Intensity'",
        'xvars': xvars,
        'yvars': ' '.join('(%s_I,%s_ERR)' % (x, x) for x in dets),
        'xlimits': '%s %s' % (min(cols[0]), max(cols[0])),
        'filename': 'mccode.dat',
        'variables': ' '.join(names + [x + s for x in dets for s in ('_I', '_ERR')])}
    forced = list(dict.fromkeys(s for r in points for s in r.merged_forced))
    with open(d/'mccode.dat', 'w', newline='\n', **ENC) as f:
        f.write("# Instrument-source: '%s'\n" % first.sim.get('Instrument', ''))
        f.write(''.join('# %s: %s\n' % kv for kv in head.items()))
        f.write(''.join('# Merged_forced: %s\n' % s for s in forced))
        for i, r in enumerate(points):
            row = [c[i] for c in cols] + [v for k in keys for v in r.mons[k].values()[:2]]
            f.write(' '.join('%.10g' % v for v in row) + '\n')
    if nexus:
        return
    sim = ['begin instrument:', '  Creator: ' + first.sim.get('Creator', ''),
           '  Source: ' + first.sim.get('Instrument', ''), '  Parameters:  ' + xvars, '  Trace_enabled: no',
           '  Default_main: yes', '  Embedded_runtime: yes', 'end instrument', '', 'begin simulation']
    sim += ['%s: %s' % (k, head[k]) for k in ('Date', 'Ncount', 'Numpoints', 'Param')]
    sim += ['Merged_forced: ' + s for s in forced] + ['end simulation', '', 'begin data']
    sim += ['%s: %s' % (k, head[k]) for k in ('type', 'title', 'xvars', 'yvars', 'xlabel', 'ylabel', 'xlimits',
                                             'filename', 'variables')] + ['end data']
    (d/'mccode.sim').write_text('\n'.join(sim) + '\n', **ENC)


# Main =========================================================================

def other_files(runs):
    """Files in the datasets that are not merged"""
    found = {}
    for r in runs:
        known = {m.head.get('filename') for m in r.mons.values()}
        for f in r.dir.iterdir():
            if f.is_file() and f.name not in known and not re.match(r'mccode(_node\d+)?\.(sim|dat|h5)$', f.name) \
                    and f.suffix not in ('.instr', '.c', '.out', '.exe'):
                found.setdefault(f.name, r.label)
    return sorted(found)


def write(points, names, runs, out, nexus):
    scan = len(points) > 1
    if nexus:
        if any(not r.template for r in points):
            print('WARNING: ASCII has no geometry or component parameters: not in the NeXus file', file=sys.stderr)
        out.mkdir(parents=True)
        with h5py.File(out/'mccode.h5', 'w') as f:
            for i, r in enumerate(points):
                write_nexus_entry(r, f, 'entry%i' % (i + 1), str(out))
    else:
        for i, r in enumerate(points):
            write_ascii_run(r, out/str(i) if scan else out, r.label)
    if scan:
        write_scan_files(points, names, out, nexus)
    src = next((f for r in runs for d in (r.dir, r.dir.parent) for f in sorted(d.glob('*.instr'))
                if f.name == r.sim.get('Instrument')), None)
    if src:
        shutil.copy(src, out)


def merge(inputs, outdir, fmt=None, force=False):
    """Merge datasets into outdir. Raises MergeError if refused"""
    out, guard = Path(outdir), Guard()
    if len(inputs) < 2:
        raise MergeError('needs at least 2 datasets')
    if out.exists():
        raise MergeError('%s exists already' % outdir)
    runs = []
    for x in inputs:
        try:
            runs += read_dataset(x, guard)
        except MergeError as e:
            guard.denied(str(e))
        except (OSError, KeyError, IndexError, ValueError) as e:
            guard.denied('%s: can not be read: %s' % (x, e))
    groups, names = [], []
    if runs:
        check_runs(runs, guard)
    if runs and not guard.hard:
        groups, names = group_runs(runs, guard)
        for g in groups:
            check_group(g, guard)
        n = [sum(r.ncount for r in g) for g in groups]
        if max(n) != min(n):
            guard.warn('the scan points have different ray counts, %i to %i' % (min(n), max(n)))
        extra = other_files(runs)
        if extra:
            guard.warn('not merged: %s%s' % (', '.join(extra), ' (for MCPL files use mcpltool --merge)'
                                             if any('.mcpl' in x for x in extra) else ''))
    nexus = fmt == 'NeXus' if fmt else bool(runs and runs[0].nexus)
    if nexus and h5py is None:
        guard.denied('NeXus needs the h5py Python package')
    for m in guard.warnings:
        print('WARNING: ' + m, file=sys.stderr)
    if guard.hard:
        raise MergeError('refused:\n  ' + '\n  '.join(guard.hard + guard.soft))
    if guard.soft and not force:
        raise MergeError('refused, --force overrides:\n  ' + '\n  '.join(guard.soft))
    for m in guard.soft:
        print('WARNING: ***FORCED*** ' + m, file=sys.stderr)

    scan = len(groups) > 1
    points = [merge_group(g, '%s/%i' % (out, i) if scan and not nexus else str(out), guard.soft)
              for i, g in enumerate(groups)]
    try:
        write(points, names, runs, out, nexus)
    except (OSError, ValueError) as e:  # e.g. a damaged event list: leave no half dataset behind
        shutil.rmtree(out, ignore_errors=True)
        raise MergeError('%s not written: %s' % (out, e))
    print('%s: %i runs, %.6g rays -> %s' % (out, len(runs), sum(r.ncount for r in points),
          'scan of %s, %i points' % (', '.join(names), len(points)) if scan else 'single dataset'))


def main():
    p = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    p.add_argument('datasets', nargs='+', help='dataset directories, 2 or more')
    p.add_argument('-d', '--dir', required=True, help='output directory, must not exist')
    p.add_argument('--format', choices=('McCode', 'NeXus'), help='output format (default: as the first dataset)')
    p.add_argument('--force', action='store_true',
                   help='merge doubtful datasets anyway. The result may be WRONG, and is marked as forced')
    a = p.parse_args()
    if a.force:
        print('WARNING: --force may give WRONG results', file=sys.stderr)
    try:
        merge(a.datasets, a.dir, a.format, a.force)
    except MergeError as e:
        print('%s: %s' % (p.prog, e), file=sys.stderr)
        sys.exit(-1)


if __name__ == '__main__':
    main()
