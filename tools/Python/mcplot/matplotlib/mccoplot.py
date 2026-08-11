#!/usr/bin/env python3
'''
matplotlib mccoplot frontend.

This is a companion to mcplotdiff.py (mcplot-diff-matplotlib), sharing
part of its command-line syntax and monitor-matching logic. Instead of
computing and plotting the *difference* between two simulation results,
mccoplot.py overlays any number (2 or more) of datasets on the same axes,
for direct visual comparison of curve shape and position across all of
them at once, rather than the difference tool's pairwise "how big is the
gap". Unlike the diff tools (which are deliberately staying two-way only),
this is an interactive, end-user comparison tool - typically used with a
handful (2-8 or so) of related runs, e.g. sweeping a parameter or comparing
several code versions/platforms against each other directly, not against
one designated reference.

Only 1D monitors are supported: datasets are matched by output filename via
mccodelib.mcplotdiffloader.match_monitors_multi() (shared with the
mcplot-coplot-html/-pyqtgraph frontends), and any monitor that isn't a
matching 1D monitor across *every* dataset is skipped with a warning -
overlaying more than two 2D images doesn't have an equally natural
single-plot representation, so that case is left to the (two-way) diff
tools instead.

Rendering reuses plotfuncs.py's panel-layout helpers (figure sizing, panel
grid math, font scaling, title wrapping) - the same ones mcplot.py and
mcplotdiff.py use - but with its own drawing/driver code, since a co-plot
panel overlays N curves rather than showing one Data1D/Data2D from a plot
graph. There's deliberately no click-based drill-down here (unlike ordinary
mcplot-matplotlib): a co-plot panel is already the finest level of detail
on offer, so there's nothing further to navigate into. Keyboard shortcuts
(log toggle, save png/pdf/svg/jpg, quit, help) are otherwise identical,
reusing plotfuncs.py's keypress()/print_help()/dumpfile() directly.
'''
import argparse
import logging
import os
import sys
import matplotlib
import numpy as np

sys.path.append(os.path.join(os.path.dirname(__file__), '..', '..'))

import plotfuncs

from mccodelib import mcplotdiffloader as diffloader
from mccodelib import mccode_config


def _plot_coplot_panel(datas, labels, colours, i, n, log):
    ''' plot one overlaid N-dataset group into subplot i of n '''
    dims = plotfuncs._calc_panel_size(n)
    subplt = plotfuncs.pylab.subplot(dims[1], dims[0], i + 1)

    fontsize = plotfuncs._panel_fontsize(n)
    title_fontsize = plotfuncs._title_fontsize(n)
    verbose = (n == 1)

    d0 = datas[0]
    xmin = d0.xlimits[0]
    xmax = d0.xlimits[1]
    plotfuncs.pylab.xlim(xmin, xmax)

    ylabel = d0.ylabel
    series = []  # (x, y, yerr) per dataset, post log-transform if needed
    for data in datas:
        x = np.array(data.xvals).astype(float)
        y = np.array(data.yvals).astype(float)
        yerr = np.array(data.y_err_vals).astype(float)
        if log:
            y = y.copy()
            invalid = np.where(y <= 0)
            valid = np.where(y > 0)
            if len(valid[0]):
                min_valid = np.min(y[valid])
                y[invalid] = min_valid / 10
            yerr = yerr / y
            y = np.log(y)
        series.append((x, y, yerr))
    if log:
        ylabel = "log(" + d0.ylabel + ")"

    for (x, y, yerr), label, colour in zip(series, labels, colours):
        plotfuncs.pylab.errorbar(x, y, yerr, color=colour, label=label)

    plotfuncs.pylab.xlabel(d0.xlabel, fontsize=fontsize, fontweight='bold')
    plotfuncs.pylab.ylabel(ylabel, fontsize=fontsize, fontweight='bold')

    # short title in an overview grid, fuller detail (matching d0.title and
    # every dataset's I/statistics) once drilled down to a single panel -
    # the same "verbose only at n==1" convention plotfuncs.plot_single_data
    # uses for ordinary (non-coplot) monitors. For n==2, this produces
    # exactly the same two-line stats block the original two-dataset-only
    # version did.
    if verbose:
        try:
            lines = ['%s [%s]' % (d0.component, d0.filename), d0.title]
            for data, label in zip(datas, labels):
                lines.append('%s: I=%s Err=%s N=%s; %s' % (
                    label, data.values[0], data.values[1], data.values[2], data.statistics))
            title = '\n'.join(lines)
        except Exception:
            title = '%s [%s]' % (d0.component, d0.filename)
    else:
        title = '%s [%s]' % (d0.component, d0.filename)
    title = plotfuncs._wrap_title(title, plotfuncs._title_wrap_width(n, title_fontsize))
    plotfuncs.pylab.title(title, fontsize=title_fontsize, fontweight='bold')

    leg = plotfuncs.pylab.legend(loc='upper left', fontsize=title_fontsize, framealpha=0.85,
                                  handlelength=1.2, handletextpad=0.5, borderpad=0.4)
    leg.set_draggable(True)

    return subplt


class McCoplotPlotter():
    ''' Matplotlib co-plot frontend: renders a grid of overlaid N-dataset
        monitor groups, with the same overview <-> single-panel navigation
        as ordinary mcplot-matplotlib/mcplotdiff-matplotlib (click a panel
        to view it full-size; right-click, 'b', or back-navigate to
        return), reusing plotfuncs.py's generic click()/keypress()/
        print_help()/dumpfile() directly - none of those depend on there
        being an actual plot graph, they just need a list of "click_cbs"
        (one per currently-visible panel) and a "back_cb". Since a co-plot
        group has no further level of detail beyond the single-panel view
        (unlike an ordinary monitor's plot graph, which can have further
        primaries/secondaries to sweep through), click_cbs is simply empty
        once drilled down - only the back-navigation remains active. '''

    def __init__(self, pairs, labels, colours, log, path_note=None):
        self.pairs = pairs  # [(key, [data_0, ..., data_N-1]), ...]
        self.labels = labels
        self.colours = colours
        self.log = log
        self.path_note = path_note
        self.current = None  # None = overview grid; else index into self.pairs
        self.event_dc_cid = None

    def _flip_log(self):
        self.log = not self.log

    def _visible_pairs(self):
        if self.current is None:
            return self.pairs
        return [self.pairs[self.current]]

    def _show_overview(self):
        self.current = None
        self._replot()

    def _show_single(self, idx):
        self.current = idx
        self._replot()

    def _click_proxy(self, event):
        ''' state-updating proxy for plotfuncs.click(), mirroring
            McMatplotlibPlotter._click_proxy() '''
        dc_cb = lambda: plotfuncs.pylab.disconnect(self.event_dc_cid)
        plotfuncs.click(event, subplts=self.subplts, click_cbs=self.click_cbs,
                         ctrl_cbs=[], back_cb=self._show_overview, dc_cb=dc_cb)

    def _keypress_proxy(self, event):
        plotfuncs.keypress(event, back_cb=self._show_overview, replot_cb=self._replot,
                            togglelog_cb=self._flip_log)

    def _render(self):
        visible = self._visible_pairs()
        n = len(visible)
        fig_w, fig_h = plotfuncs._figure_size(n)
        fig = plotfuncs.pylab.figure(figsize=(fig_w, fig_h))

        self.subplts = [
            _plot_coplot_panel(datas, self.labels, self.colours, i, n, self.log)
            for i, (key, datas) in enumerate(visible)
        ]

        fig.subplots_adjust(left=0.06, right=0.98, top=0.97, bottom=0.06,
                             wspace=0.3, hspace=0.35)

        if self.path_note:
            # labels are bare letters here (see resolve_labels()), since
            # the source paths' basenames collided (e.g. all ending in
            # ".../<instrument>/1/") - shown once as a figure-level title
            # (matplotlib's actual "figure title" concept, distinct from
            # each panel's own title) rather than repeated inside every
            # panel, which would get cluttered across a multi-panel
            # overview.
            fig.suptitle(self.path_note, fontsize=9, y=0.998, va='top')
            fig.subplots_adjust(top=0.90 if n == 1 else 0.92)

        # Left-click on a panel drills into it (only meaningful in overview
        # mode - once already on a single panel there's nowhere further to
        # go, so click_cbs is left empty and only right-click/'b' back-
        # navigation remains live).
        if self.current is None:
            self.click_cbs = [lambda idx=i: self._show_single(idx) for i in range(n)]
        else:
            self.click_cbs = []

        return fig

    def _replot(self):
        ''' Re-renders from scratch and re-enters the GUI event loop.

            pylab.show() must be called again here, not just once from
            plot() below - the SAME pattern plotfuncs.McMatplotlibPlotter.
            plot_node() already uses for every click/keypress-triggered
            redraw. Without it: _render() calls pylab.close() (destroying
            the figure the original blocking show() call was watching) and
            then creates a brand new figure via pylab.figure() - but with
            no show() call for that new figure, many backends' blocking
            event loop exits as soon as the figure count momentarily hits
            zero, so the process falls straight through the original
            show() and the new figure is never actually displayed. The
            visible symptom is exactly what it looks like: any click
            (drilling into a panel, going back, or even just toggling log
            via 'l') appears to close the window outright. '''
        plotfuncs.pylab.close()
        self._render()
        self.event_dc_cid = plotfuncs.pylab.connect('button_press_event', self._click_proxy)
        plotfuncs.pylab.connect('key_press_event', self._keypress_proxy)
        plotfuncs.pylab.show()

    def plot(self):
        ''' render and show the interactive grid '''
        self._replot()

    def html(self, fileobj):
        ''' render and save to html using mpld3 '''
        import mpld3
        plotfuncs.pylab.close()
        self._render()
        mpld3.save_html(plotfuncs.pylab.gcf(), fileobj)


def main(args):
    ''' load and match N simulation results' 1D monitors, then hand the
        resulting groups to the matplotlib co-plot frontend above. '''
    logging.basicConfig(level=logging.INFO)

    # ensure keyboardinterrupt ctr-c
    import signal
    signal.signal(signal.SIGINT, signal.SIG_DFL)

    try:
        paths = args.datasets
        if len(paths) < 2:
            print("mccoplot: need at least 2 datasets to co-plot, got %d" % len(paths))
            quit()

        given_labels = args.labels[0].split(',') if args.labels else [None] * len(paths)
        if len(given_labels) != len(paths):
            print("mccoplot: --labels has %d entries but %d datasets were given"
                  % (len(given_labels), len(paths)))
            quit()
        given_labels = [l if l else None for l in given_labels]

        given_colours = args.colours[0].split(',') if args.colours else None

        if args.format or args.output:
            matplotlib.use('template')

        if args.backend:
            try:
                matplotlib.use(args.backend)
            except Exception as e:
                print('backend use error: ' + e.__str__())
                return

        from matplotlib import pylab
        plotfuncs.pylab = pylab

        labels, used_fallback = diffloader.resolve_labels(paths, given_labels)
        colours = diffloader.resolve_colours(len(paths), given_colours)

        # When the auto-derived labels collided (e.g. several runs all
        # ending in a plain ".../<instrument>/1/" folder) and
        # resolve_labels() fell back to bare letters, those letters carry
        # no identifying information on their own - show the full source
        # paths as a figure-level suptitle instead, while the per-panel
        # legend keeps just the letters.
        path_note = None
        if used_fallback:
            path_note = "   ".join("%s: %s" % (lbl, p) for lbl, p in zip(labels, paths))

        monitors_list = []
        try:
            for p in paths:
                monitors, _ = diffloader.load_monitors(p)
                monitors_list.append(monitors)
        except Exception as e:
            print('mccoplot loader: ' + e.__str__())
            plotfuncs.print_help(nogui=True)
            quit()

        pairs = diffloader.match_monitors_multi(monitors_list, labels)

        if len(pairs) == 0:
            print("mccoplot: no matching 1D monitors found across all %d datasets, nothing to plot."
                  % len(paths))
            quit()

        if args.test:
            print("mccoplot: %d matched 1D monitor group(s) across %d datasets:" % (len(pairs), len(paths)))
            for key, datas in pairs:
                print("  - %s (%s)" % (key, datas[0].component))

        # default base name for --format/--output dumps and for --html,
        # since there's no single simulation file to derive it from -
        # deliberately built from the actual input paths (dirsafe_name),
        # not the display labels: those may legitimately collapse to bare
        # letters when their basenames collide (see resolve_labels()),
        # which would otherwise make every such comparison overwrite the
        # same "coplot_A_vs_B....*" files - a real problem for batch/CI
        # use running many comparisons out of one working directory.
        plotfuncs.filenamebase = "coplot_" + "_vs_".join(diffloader.dirsafe_name(p) for p in paths)

        plotter = McCoplotPlotter(pairs, labels, colours, log=args.log, path_note=path_note)

        if (sys.platform == "linux" or sys.platform == "linux2") and args.html:
            # save to html and exit
            plotter.html(open('%s.html' % plotfuncs.filenamebase, 'w'))
        else:
            # display gui / prepare graphics dump
            plotfuncs.print_help(nogui=True)
            plotter.plot()

        if args.output or args.format:
            try:
                plotfuncs.dumpfile(args.format, args.output)
            except Exception as e:
                print('dumpfile issue: ' + e.__str__())

    except KeyboardInterrupt:
        print('keyboard interrupt')
    except Exception as e:
        print('mccoplot error: %s' % e.__str__())
        raise e


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument('datasets', nargs='+',
                         help='2 or more simulation files or directories to co-plot together '
                              '(e.g. "mccoplot run_a run_b run_c")')
    parser.add_argument('-L', '--labels', nargs=1,
                         help='comma-separated short labels, one per dataset, in the same order '
                              '(e.g. --labels "RunA,RunB,RunC"); default: derived from each path')
    parser.add_argument('-C', '--colours', nargs=1,
                         help='comma-separated overlay colours, one per dataset, in the same order; '
                              'default: %s' % ', '.join(diffloader.DEFAULT_PALETTE))
    parser.add_argument('-t', '--test', action='store_true', default=False, help='print the matched monitor groups before plotting')
    parser.add_argument('--html', action='store_true', help='save plot to html using mpld3 (linux only)')
    parser.add_argument('--format', dest='format', help='save plot to pdf/png/eps/svg... without bringing up window')
    parser.add_argument('--output', nargs=1, dest='output', default=None,
                         help='save plot to given file without bringing up window. Extension '
                              '(e.g. pdf/png/eps/svg) can be specified in the file name or --format')
    parser.add_argument('--log', action='store_true', help='initiate plot(s) with log of signal')
    parser.add_argument('--backend', dest='backend', help='use non-default backend for matplotlib plot')

    args = parser.parse_args()

    mccode_config.load_config("user")

    main(args)
