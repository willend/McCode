#!/usr/bin/env python3
"""Check mcmerge on synthetic datasets. Run with pytest, or directly."""
import sys
import tempfile
from pathlib import Path

import numpy as np

sys.path.insert(0, str(Path(__file__).parent))
import mcmerge  # noqa: E402

SIM = '''mcstas simulation description file for toy.
Date:    Tue Nov 24 14:53:03 2026
Program: {creator}

begin instrument: toy
  File: {instr}
  Source: toy
  Parameters: wl(double)
end instrument

begin simulation: {d}
  Format: McCode with text headers
  Creator: {creator}
  Instrument: {instr}
  Ncount: {n}
  Trace: no
  Gravitation: {gravitation}
  Seed: {seed}
  Directory: {d}
  Param: wl={wl}
end simulation
'''
HEAD = '''type: {type}
Source: toy ({instr})
component: {comp}
position: 0 0 1
title: {title}
Ncount: {n}
filename: {file}
statistics: X0=0; dX=0;
signal: Min=0; Max=0; Mean=0;
values: {values}
xvar: {xvar}
yvar: {yvar}
xlabel: {xvar}
ylabel: I
zvar: I
{limname}: {lim}
variables: {variables}
'''


def events(n, seed):
    rng = np.random.default_rng(seed)
    return np.column_stack([rng.exponential(size=n), rng.uniform(-1, 1, (n, 2))])


def make_run(d, ev, seed=1, wl='3', creator='3.10.3, git', gravitation='no', instr='toy.instr',
             lim=1, bins=8, title='toy', columns='p x y', timing=True, ratio=False, scale=1):
    """Write the dataset of these events, weights and errors as by the runtime"""
    d.mkdir(parents=True)
    n = len(ev)
    p, x, y = ev[:, 0]*scale/n, ev[:, 1], ev[:, 2]

    def hist(*axes):
        arg = dict(bins=bins, range=[[-lim, lim]]*len(axes))
        m, i, p2 = (np.histogramdd(axes, weights=w, **arg)[0].T for w in (np.ones_like(p), p, p*p))
        return m, i, mcmerge.sigma(m, i, p2)
    total = p.sum(), float(mcmerge.sigma(n, p.sum(), (p*p).sum())), n
    n1, i1, e1 = hist(x)
    n2, i2, e2 = hist(x, y)
    axis = -lim + (np.arange(bins) + .5)*2*lim/bins
    tables = [
        ('array_0d', 'm0', 'm0.dat', 'xylimits', '0 0 0 0 0 0', 'I I_err N', [[total]]),
        ('array_1d(%i)' % bins, 'm1', 'm1.dat', 'xlimits', '%g %g' % (-lim, lim), 'x I I_err N',
         [np.column_stack([axis, i1, e1, n1])]),
        ('array_2d(%i, %i)' % (bins, bins), 'm2', 'm2.dat', 'xylimits', '%g %g %g %g' % (-lim, lim, -lim, lim),
         'I I_err N', [i2, e2, n2]),
        ('list(%i, 3)' % n, 'l', 'l.list', 'xylimits', '1 %i 1 3' % n, columns, [np.column_stack([p, x, y])])]
    sim = SIM.format(d=d, n=n, seed=seed, wl=wl, creator=creator, gravitation=gravitation, instr=instr)
    for typ, comp, file, limname, limits, variables, data in tables:
        head = HEAD.format(type=typ, comp=comp, file=file, limname=limname, lim=limits, variables=variables,
                           instr=instr, n=n, title=title, values='%.10g %.10g %i' % total, xvar='x', yvar='y')
        if typ == 'array_0d':
            head = ''.join(x + '\n' for x in head.splitlines() if x[:4] not in ('xvar', 'yvar', 'xlab', 'ylab', 'zvar'))
        if ratio:
            head += 'ratio: 1/2\n'
        sim += '\nbegin data\n' + ''.join('  %s\n' % s for s in head.splitlines()) + 'end data\n'
        with open(d/file, 'w') as f:
            f.write('# Format: McCode with text headers\n' + ''.join('# %s\n' % s for s in head.splitlines()))
            for name, a in zip(('Data', 'Errors', 'Events'), data):
                if typ[:8] != 'array_1d':
                    f.write('# %s [%s/%s] I:\n' % (name, comp, file))
                np.savetxt(f, a, fmt='%.10g')
    if timing:
        sim += '\nbegin timing\n  Init: 0.10 [s]\n  Trace: 1.00 [s]\n  Finally: 0.01 [s]\nend timing\n'
    (d/'mccode.sim').write_text(sim)
    return d


def load(d):
    guard = mcmerge.Guard()
    runs = mcmerge.read_dataset(d, guard)
    assert not guard.hard, guard.hard
    return runs


def same(a, b, tol=1e-5):
    """Equal datasets, other than provenance"""
    ra, rb = load(a), load(b)
    assert len(ra) == len(rb)
    for x, y in zip(ra, rb):
        assert x.params == y.params and x.ncount == y.ncount and sorted(x.mons) == sorted(y.mons)
        for k, m in x.mons.items():
            o = y.mons[k]
            if m.kind == 'list':
                u, v = (np.concatenate(list(z.events())) for z in (m, o))
                assert np.allclose(u, v, rtol=tol, atol=0), k
                continue
            for u, v in ((m.I, o.I), (m.E, o.E), (m.N, o.N), (m.values(), o.values())):
                assert np.allclose(u, v, rtol=tol, atol=1e-12), k


def refused(inputs, out, why, forceable):
    """Refused for this reason, --force overrides it or not, and marks the output"""
    for force in (False, True):
        try:
            mcmerge.merge(inputs, out, force=force)
        except mcmerge.MergeError as e:
            assert why in str(e), (why, str(e))
            assert not (force and forceable), (why, str(e))
            assert out in inputs or not out.exists(), why
        else:
            assert force and forceable, 'not refused: ' + why
            assert any(why in s for r in load(out) for s in r.merged_forced), why


def test_pooling(tmp_path):
    """Runs of different length, merged == one run of all events, in any order and format"""
    ev = [events(n, i) for i, n in enumerate((1000, 300, 2500))]
    d = [make_run(tmp_path/('r%i' % i), e, seed=100*i + 1) for i, e in enumerate(ev)]
    truth = make_run(tmp_path/'truth', np.concatenate(ev))
    mcmerge.merge(d, tmp_path/'abc')
    same(tmp_path/'abc', truth)
    mcmerge.merge(d[:2], tmp_path/'ab')
    mcmerge.merge([tmp_path/'ab', d[2]], tmp_path/'ab_c')
    same(tmp_path/'ab_c', tmp_path/'abc')
    assert load(tmp_path/'ab_c')[0].merged_from == load(tmp_path/'abc')[0].merged_from
    refused([tmp_path/'abc', d[1]], tmp_path/'twice', 'seeds overlap', True)
    if mcmerge.h5py:
        mcmerge.merge(d, tmp_path/'nx', 'NeXus')
        same(tmp_path/'nx', truth)
        mcmerge.merge(d[:2], tmp_path/'nxab', 'NeXus')
        mcmerge.merge([tmp_path/'nxab', d[2]], tmp_path/'back', 'McCode')
        same(tmp_path/'back', truth)


def test_scan(tmp_path):
    """Differing parameters make a scan, the same points of scans are pooled"""
    ev = [events(500, i) for i in range(4)]
    d = [make_run(tmp_path/('p%i' % i), e, seed=10*i + 1, wl=w) for i, (e, w) in enumerate(zip(ev, '2323'))]
    mcmerge.merge([d[1], d[0]], tmp_path/'s1')
    mcmerge.merge(d[2:], tmp_path/'s2')
    assert [r.params['wl'] for r in load(tmp_path/'s1')] == ['2', '3']
    same(tmp_path/'s1'/'0', d[0])
    mcmerge.merge([tmp_path/'s1', tmp_path/'s2'], tmp_path/'s12')
    for i in (0, 1):
        same(tmp_path/'s12'/str(i), make_run(tmp_path/('t%i' % i), np.concatenate([ev[i], ev[i + 2]]), wl='23'[i]))
    rows = np.loadtxt(tmp_path/'s12'/'mccode.dat')
    assert rows[:, 0].tolist() == [2, 3] and rows.shape == (2, 1 + 2*4)
    if mcmerge.h5py:
        mcmerge.merge([tmp_path/'s1', tmp_path/'s2'], tmp_path/'nx', 'NeXus')
        same(tmp_path/'nx', tmp_path/'s12')
    dat = tmp_path/'s2'/'mccode.dat'
    dat.write_text(dat.read_text().replace('Numpoints: 2', 'Numpoints: 3'))
    refused([tmp_path/'s1', tmp_path/'s2'], tmp_path/'x', 'incomplete scan', False)


DENIED = {
    'interrupted run': dict(timing=False),
    'ray count is unknown': dict(ratio=True),
    'other instrument': dict(instr='other.instr'),
    'number of bins': dict(bins=9),
    'other columns': dict(columns='p y x'),
    'log of the signal': dict(title='toy [log]')}
FORCEABLE = {
    'before 3.10.3': dict(creator='3.10.2, git', timing=False),
    'Creator': dict(creator='3.11.0, git'),
    'Gravitation': dict(gravitation='yes'),
    'not recorded': dict(wl='NULL'),
    'seeds overlap': dict(seed=1),
    'other limits': dict(lim=2),
    'sigma': dict(scale=2)}


def test_guards(tmp_path):
    a = make_run(tmp_path/'a', events(1000, 1), seed=1)
    for i, (why, arg) in enumerate((*DENIED.items(), *FORCEABLE.items())):
        b = make_run(tmp_path/('b%i' % i), events(1000, 2), **{'seed': 50, **arg})
        refused([a, b], tmp_path/('o%i' % i), why, why in FORCEABLE)
    b = make_run(tmp_path/'b', events(1000, 2), seed=50)
    out = tmp_path/'x'
    refused([a], out, 'at least 2', False)
    refused([a, b], b, 'exists already', False)
    refused([a, tmp_path/'none'], out, 'no such dataset', False)
    with open(b/'l.list', 'a') as f:
        f.write('0.1 0.')
    refused([a, b], out, 'not written', False)
    (b/'l.list').unlink()
    refused([a, b], out, 'l.list is missing', False)
    n = [make_run(tmp_path/s, events(100, i), seed=50*i + 9, columns='I x y') for i, s in enumerate('uv')]
    refused(n, out, 'no p column', True)


if __name__ == '__main__':
    for test in (test_pooling, test_scan, test_guards):
        with tempfile.TemporaryDirectory() as t:
            test(Path(t))
    print('OK')
