'''
Shared logic for computing the difference between two McCode simulation
results, i.e. "diff.monN = a.monN - b.monN" for every monitor present, with
matching binning, in both simulation results 'a' and 'b'.

This is used by the various mcplot-diff frontends (mcplot-diff-html,
mcplot-diff-pyqtgraph, ...) and builds directly on the same
McCodeDataLoader / plot graph machinery used by the ordinary mcplot
frontends (see mcplotloader.py and plotgraph.py). It only adds the
"load two simulations, match up monitors by output filename, subtract"
step, plus a helper to assemble a diff plot graph that can be fed straight
into any existing plot-graph-based frontend (e.g. the interactive
pyqtgraph frontend in pqtgfrontend.py).
'''
import os

import numpy as np

from .mcplotloader import McCodeDataLoader, Data1D, Data2D
from .plotgraph import PNSingle, PNMultiple, DataHandle


# ---------------------------------------------------------------------------
# small path/string helpers
# ---------------------------------------------------------------------------

def file_base_name(file_name):
    if '.' in file_name:
        separator_index = file_name.index('.')
        return file_name[:separator_index]
    return file_name


def path_base_name(path):
    return file_base_name(os.path.basename(path))


def default_labels(path_a, path_b, label_a=None, label_b=None):
    ''' Resolves user-facing short labels for two simulation paths, falling
        back to the basename of each path if a label wasn't given
        explicitly. '''
    if not label_a:
        label_a = path_base_name(os.path.basename(os.path.abspath(path_a.rstrip('/'))))
    if not label_b:
        label_b = path_base_name(os.path.basename(os.path.abspath(path_b.rstrip('/'))))
    return label_a, label_b


# ---------------------------------------------------------------------------
# loading two simulations and matching up their monitors
# ---------------------------------------------------------------------------

def resolve_simfile(path):
    """ Given a user-supplied path (file or directory), return (simfile, simdir)
        the way McCodeDataLoader / mcplot.py expects it. """
    if os.path.isfile(path):
        simfile = path
        simdir = os.path.dirname(path)
        if simdir == '':
            simdir = '.'
    elif os.path.isdir(path):
        simdir = path
        simfile = os.path.join(simdir, 'mccode.sim')
    else:
        raise Exception(path + " is neither a file or a directory")
    return simfile, simdir


def load_monitors(path):
    """ Loads a simulation (folder or single monitor file) and returns
        (monitors, directory), where monitors is a dict mapping a monitor
        'key' (its output filename, e.g. 'PSD.dat') to a Data1D/Data2D
        object. """
    simfile, simdir = resolve_simfile(path)

    loader = McCodeDataLoader(simfile=simfile)
    loader.load()

    root = loader.plot_graph

    if isinstance(root, PNSingle):
        data_lst = [root.getdata_idx(0)]
    elif isinstance(root, PNMultiple):
        data_lst = root.getdata_lst()
    else:
        raise Exception('unsupported/empty simulation result in %s' % path)

    monitors = {}
    for data in data_lst:
        if not isinstance(data, (Data1D, Data2D)):
            # skip 0D / event-list / unknown monitors: nothing sensible to subtract
            continue
        key = data.filename if data.filename else data.component
        if key in monitors:
            # extremely unlikely (duplicate filenames), disambiguate by component
            key = '%s__%s' % (key, data.component)
        monitors[key] = data

    return monitors, getattr(loader, 'directory', simdir)


# ---------------------------------------------------------------------------
# computing the difference datasets
# ---------------------------------------------------------------------------

def diff_1d(key, a, b, label_a, label_b):
    if len(a.xvals) != len(b.xvals):
        print("Warning: skipping '%s' - differing number of bins (%d vs %d)"
              % (key, len(a.xvals), len(b.xvals)))
        return None

    ay = np.array(a.yvals, dtype=float)
    by = np.array(b.yvals, dtype=float)
    aerr = np.array(a.y_err_vals, dtype=float)
    berr = np.array(b.y_err_vals, dtype=float)

    dy = ay - by
    derr = np.sqrt(aerr**2 + berr**2)

    d = Data1D()
    d.filepath = a.filepath
    d.component = a.component
    d.filename = a.filename
    d.xlabel = a.xlabel
    d.ylabel = a.ylabel
    d.xvar = a.xvar
    d.xlimits = a.xlimits
    d.variables = a.variables
    d.yvar = a.yvar

    d.xvals = a.xvals
    d.yvals = dy.tolist()
    d.y_err_vals = derr.tolist()
    d.Nvals = a.Nvals

    I = float(np.sum(dy))
    Ierr = float(np.sqrt(np.sum(derr**2)))
    try:
        N = int(min(a.values[2], b.values[2]))
    except Exception:
        N = 0
    d.values = (I, Ierr, N)
    d.statistics = '%s: %s\n%s: %s' % (label_a, a.statistics, label_b, b.statistics)
    d.title = '\nDiff (%s - %s): %s' % (label_a, label_b, a.title)

    return d


def diff_2d(key, a, b, label_a, label_b):
    za = np.array(a.zvals, dtype=float)
    zb = np.array(b.zvals, dtype=float)

    if za.shape != zb.shape:
        print("Warning: skipping '%s' - differing array shapes (%s vs %s)"
              % (key, str(za.shape), str(zb.shape)))
        return None

    zdiff = za - zb

    d = Data2D()
    d.filepath = a.filepath
    d.component = a.component
    d.filename = a.filename
    d.xlabel = a.xlabel
    d.ylabel = a.ylabel
    d.xvar = a.xvar
    d.yvar = a.yvar
    d.zvar = a.zvar
    d.xlimits = a.xlimits

    d.zvals = zdiff.tolist()
    d.counts = a.counts

    I = float(np.sum(zdiff))
    try:
        Ierr = float(np.sqrt(float(a.values[1])**2 + float(b.values[1])**2))
        N = int(min(a.values[2], b.values[2]))
    except Exception:
        Ierr = 0.0
        N = 0
    d.values = (I, Ierr, N)
    d.statistics = '%s: %s\n%s: %s' % (label_a, a.statistics, label_b, b.statistics)
    d.title = '\nDiff (%s - %s): %s' % (label_a, label_b, a.title)

    return d


def compute_diffs(monitors_a, monitors_b, label_a, label_b):
    """ Matches monitors present in both simulations by output filename and
        subtracts them. Returns an ordered list of diff Data1D/Data2D objects. """
    keys_a = set(monitors_a.keys())
    keys_b = set(monitors_b.keys())

    only_a = keys_a - keys_b
    only_b = keys_b - keys_a
    for k in sorted(only_a):
        print("Warning: monitor '%s' present in '%s' only, skipping" % (k, label_a))
    for k in sorted(only_b):
        print("Warning: monitor '%s' present in '%s' only, skipping" % (k, label_b))

    diffs = []
    # keep the ordering from simulation a where possible
    ordered_keys = [k for k in monitors_a.keys() if k in keys_b]
    for key in ordered_keys:
        a = monitors_a[key]
        b = monitors_b[key]

        if a.component != b.component:
            print("Warning: '%s' component name differs ('%s' vs '%s'), diffing anyway"
                  % (key, a.component, b.component))

        if isinstance(a, Data1D) and isinstance(b, Data1D):
            d = diff_1d(key, a, b, label_a, label_b)
        elif isinstance(a, Data2D) and isinstance(b, Data2D):
            d = diff_2d(key, a, b, label_a, label_b)
        else:
            print("Warning: skipping '%s' - mismatched or unsupported monitor types" % key)
            d = None

        if d is not None:
            diffs.append(d)

    return diffs


def load_and_diff(path_a, path_b, label_a=None, label_b=None):
    """ Convenience one-shot: loads both simulations, resolves labels, and
        returns (diffs, dir_a, dir_b, label_a, label_b). """
    label_a, label_b = default_labels(path_a, path_b, label_a, label_b)
    monitors_a, dir_a = load_monitors(path_a)
    monitors_b, dir_b = load_monitors(path_b)
    diffs = compute_diffs(monitors_a, monitors_b, label_a, label_b)
    return diffs, dir_a, dir_b, label_a, label_b


# ---------------------------------------------------------------------------
# locating pre-existing mcplot-html output for the two original simulations
# ---------------------------------------------------------------------------

def find_original_plot(directory, monitor_filename):
    """ Looks for the mcplot-html page(s) previously generated (by
        mcplot.py / mcplot-html) for a given monitor output file in
        `directory`, e.g. 'PSD.dat' -> 'PSD.dat.html' / 'PSD.dat_log.html'.
        Returns (linear_path_or_None, log_path_or_None); either may be None
        if the corresponding page hasn't been generated (yet). """
    if not directory or not monitor_filename:
        return None, None
    base = os.path.join(directory, monitor_filename)
    linear = base + ".html"
    log = base + "_log.html"
    linear = linear if os.path.isfile(linear) else None
    log = log if os.path.isfile(log) else None
    return linear, log


# ---------------------------------------------------------------------------
# assembling a plot graph from diff data, for plot-graph based frontends
# ---------------------------------------------------------------------------

def build_diff_plotgraph(diffs):
    """ Wraps a list of diff Data1D/Data2D objects (as returned by
        compute_diffs()) into a two-level plot graph (PNMultiple root with
        PNSingle primaries/secondaries), exactly the way
        mcplotloader.load_simulation() does for an ordinary simulation
        folder. This lets diff data be fed directly into any existing plot
        graph frontend, e.g. mccodelib.pqtgfrontend.McPyqtgraphPlotter. """
    handles = [DataHandle(load_fct=None, data=d) for d in diffs]
    root = PNMultiple(handles)
    primnodes = [PNSingle(h) for h in handles]
    root.set_primaries(primnodes)
    root.set_secondaries(primnodes)  # only one way to click here, as in load_simulation()
    return root
