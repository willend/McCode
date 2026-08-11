#!/usr/bin/env python3
'''
pyqtgraph mccoplot frontend.

This is a companion to mcplotdiff.py (mcplot-diff-pyqtgraph), sharing part
of its command-line syntax and monitor-matching logic. Instead of
computing and plotting the *difference* between two simulation results,
mccoplot.py overlays any number (2 or more) of datasets on the same axes,
for direct visual comparison across all of them at once. Unlike the diff
tools (which are deliberately staying two-way only), this is an
interactive, end-user comparison tool - typically used with a handful
(2-8 or so) of related runs.

Only 1D monitors are supported: datasets are matched by output filename via
mccodelib.mcplotdiffloader.match_monitors_multi() (shared with the
mcplot-coplot-html and mcplot-coplot-matplotlib frontends), and any monitor
that isn't a matching 1D monitor across *every* dataset is skipped with a
warning.

Unlike ordinary mcplot-pyqtgraph (mccodelib.pqtgfrontend.McPyqtgraphPlotter),
there is no click-based drill-down here: a co-plot panel already overlays
everything comparable for that monitor, so there's nothing further to
navigate into. This script therefore builds its own minimal static-grid
window rather than reusing McPyqtgraphPlotter, though it follows the same
qtpy-based conventions (so the same code runs under PyQt5/PyQt6/PySide2/
PySide6) and reuses plotfuncs.ModLegend for the on-plot legend.
'''
import argparse
import logging
import os
import sys
import math

import numpy as np
import pyqtgraph as pg

# qtpy normalises Qt5/Qt6/PySide2/PySide6 into a single API, same as
# mccodelib.pqtgfrontend.
from qtpy import QtCore, QtWidgets

sys.path.append(os.path.join(os.path.dirname(__file__), '..', '..'))

import plotfuncs

from mccodelib import mcplotdiffloader as diffloader
from mccodelib import mccode_config
from mccodelib import utils

_Qt = QtCore.Qt


# ---------------------------------------------------------------------------
# Helpers for modifier / button comparison that work across Qt5 and Qt6,
# copied from mccodelib.pqtgfrontend's convention (see there for details:
# under Qt5 Qt.ControlModifier is an int, under Qt6 it's an enum member;
# qtpy exposes them at the same attribute path, but comparing enum members
# to ints with == raises a TypeError in Qt6, hence normalising to int).
# ---------------------------------------------------------------------------

def _int_mod(mod):
    try:
        return int(mod)
    except (TypeError, ValueError):
        return mod.value


def _event_mods_int(event):
    try:
        return int(event.modifiers())
    except (TypeError, ValueError):
        return event.modifiers().value


def _event_button_int(event):
    try:
        return int(event.button())
    except (TypeError, ValueError):
        return event.button().value


_LEFT_BUTTON = _int_mod(_Qt.LeftButton)
_RIGHT_BUTTON = _int_mod(_Qt.RightButton)


def get_help_string():
    helplines = []
    helplines.append('')
    helplines.append('q              - quit')
    helplines.append('p              - save png')
    helplines.append('s              - save svg')
    helplines.append('l              - log toggle')
    helplines.append('F1/h           - help')
    helplines.append('click          - display single panel')
    helplines.append('right-click/b  - back to overview')
    return '\n'.join(helplines)


def _legend_fontsize(n_datasets, base_fontsize):
    """ Legend text size, shrinking as the number of co-plotted datasets
        (not the number of panels/monitors in the grid - a separate
        concern already handled by the caller-supplied base_fontsize)
        grows. The legend has one row per dataset, so without this its
        total height grows linearly and unboundedly with N, increasingly
        overlapping (and, since ModLegend draws an opaque-ish background,
        visually hiding) the plotted curves in the panel's corner - this
        is what "adding more datasets extends the axes"/"cuts the
        right-most datasets" turned out to actually be: not the axes
        moving at all, but a growing legend box progressively covering
        more of the real data underneath it. """
    if n_datasets <= 4:
        return base_fontsize
    elif n_datasets <= 8:
        return max(7, base_fontsize - 2)
    else:
        return max(6, base_fontsize - 4)


def plot_coplot_1D(datas, plt, labels, colours, log=False, legend=True, fontsize=10, verbose=False):
    ''' overlay N Data1D objects (datas) into the pyqtgraph PlotItem plt '''
    d0 = datas[0]
    series = []  # (x, y, e) per dataset
    for data in datas:
        x = np.array(data.xvals).astype(float)
        y = np.array(data.yvals).astype(float)
        e = np.array(data.y_err_vals).astype(float)
        series.append((x, y, e))

    any_log_ok = False
    if log:
        new_series = []
        for x, y, e in series:
            nonzeros = np.where(y > 0)[0]
            if len(nonzeros) > 0:
                y = y.copy()
                y[y <= 0] = np.min(y[nonzeros]) / 10
                any_log_ok = True
            new_series.append((x, y, e))
        series = new_series
        plt.setLogMode(y=any_log_ok)
    else:
        plt.setLogMode(y=False)

    xmin = min(np.min(x) for x, y, e in series)
    xmax = max(np.max(x) for x, y, e in series)
    plt.setXRange(xmin, xmax, padding=0)

    try:
        header = '%s [%s]' % (d0.component, d0.filename)
        if verbose:
            header = '%s [%s]<br>%s' % (d0.component, d0.filename, d0.title)
    except Exception:
        header = '%s' % d0.component
    plt.setTitle(header)
    plt.getAxis('bottom').setLabel(d0.xlabel)
    plt.getAxis('left').setLabel(d0.ylabel)
    # Fixed, not auto-sized: pg.GraphicsLayout gives every cell in a grid
    # column the *same* width, driven by whichever cell's axis currently
    # needs the most space - so if one panel's left-axis tick labels get
    # wider (e.g. needing an extra digit once a 3rd dataset shifts that
    # panel's merged Y-range enough to cross a tick-precision threshold -
    # something that can depend on exact float values, so it's sensitive
    # to platform/font/DPI in ways that are hard to predict or reproduce
    # consistently), every *other* panel sharing that column gets dragged
    # along with it, even though nothing about their own data changed.
    # Locking every co-plot panel's axis to the same fixed width removes
    # the coupling entirely, regardless of what triggers a width change on
    # any one panel.
    plt.getAxis('left').setWidth(95)

    # TODO (same as plotfuncs.plot_Data1D): no error bars in log mode
    if not log:
        for (x, y, e), colour in zip(series, colours):
            beam = (x[1] - x[0]) * 0.5 if len(x) > 1 else 0
            plt.addItem(pg.ErrorBarItem(x=x, y=y, height=e, beam=beam, pen=colour))

    if legend:
        legend_fontsize = _legend_fontsize(len(datas), fontsize)
        plt.legend = plotfuncs.ModLegend(offset=(-1, 1), text_size='%spt' % str(legend_fontsize))
        plt.legend.setParentItem(plt.vb)

    # actual curves, plotted with an explicit pen per series - since
    # plt.legend is already set, plot(..., name=...) registers each curve
    # with the legend automatically, using the curve's own pen as the
    # swatch colour (no need for the "invisible dummy artist" trick
    # ordinary single-dataset plots use, since here every series is real
    # and worth a legend entry). All names are bare labels ("A"/"B"/... or
    # whatever was given) - deliberately symmetric, rather than one entry
    # carrying the full component/filename/title block: ModLegend lays
    # each entry out in its own row sized to that row's content, so a long
    # multi-line entry next to short words renders visibly misaligned (the
    # descriptive text lives in the panel's own title instead, via
    # plt.setTitle() above).
    for (x, y, e), label, colour in zip(series, labels, colours):
        plt.plot(x, y, pen=colour, name=label)

    plt.setMenuEnabled(False)
    return plt.getViewBox()


class McCoplotPlotter():
    ''' pyqtgraph co-plot frontend: renders a grid of overlaid N-dataset
        monitor groups, with the same overview <-> single-panel navigation
        as ordinary mcplot-pyqtgraph (mccodelib.pqtgfrontend.McPyqtgraphPlotter):
        click a panel to view it full-size; right-click or 'b' to return.
        Since a co-plot group has no further level of detail beyond the
        single-panel view (unlike an ordinary monitor's plot graph, which
        can have further primaries/secondaries to sweep through), a click
        on the single panel itself is a no-op - only the back-navigation
        is live there. '''

    def __init__(self, pairs, labels, colours, invcanvas=False, title=None,
                 path_note=None, filenamebase=None):
        self.pairs = pairs  # [(key, [data_0, ..., data_N-1]), ...]
        self.labels = labels
        self.colours = colours
        self.log = False
        self.path_note = path_note
        self.current = None  # None = overview grid; else index into self.pairs
        self.viewbox_list = []
        self.title = title if title is not None else ('coplot: %s' % ' vs '.join(labels))
        # deliberately NOT derived from labels here: those may legitimately
        # collapse to bare letters when their basenames collide (see
        # resolve_labels()), which would make every such comparison
        # overwrite the same "coplot_A_vs_B....*" export files - a real
        # problem for batch/CI use running many comparisons out of one
        # working directory. Callers should pass the dirsafe_name()-based
        # name explicitly; this fallback only exists for callers that
        # don't care (e.g. quick interactive use, direct construction).
        self.filenamebase = filenamebase if filenamebase is not None else ('coplot_%s' % '_vs_'.join(labels))

        self.app = QtWidgets.QApplication.instance() or QtWidgets.QApplication(sys.argv)

        if invcanvas:
            pg.setConfigOption('background', 'w')
            pg.setConfigOption('foreground', 'k')

    def run(self):
        self._create_window()
        self._replot()

        exec_fn = getattr(self.app, "exec", None) or self.app.exec_
        sys.exit(exec_fn())

    def _create_window(self):
        helpmessage = QtWidgets.QLabel()
        helpmessage.setText("Press 'h' for app shortcuts.")

        statusbar = QtWidgets.QStatusBar()
        statusbar.addWidget(helpmessage)

        self.main_window = QtWidgets.QMainWindow()
        self.graphics_view = pg.GraphicsView(self.main_window)
        self.main_window.setCentralWidget(self.graphics_view)
        self.main_window.setStatusBar(statusbar)
        self.main_window.setWindowTitle(self.title)

        # Screen size - primaryScreen() is available in Qt 5.6+ and Qt 6
        screen = QtWidgets.QApplication.primaryScreen()
        if screen is not None:
            rect = screen.size()
        else:
            # Very old Qt5 fallback
            rect = QtWidgets.QApplication.desktop().screenGeometry()

        w = int(0.7 * rect.width())
        h = int(0.7 * rect.height())
        self.main_window.resize(w, h)

        self.plot_layout = pg.GraphicsLayout(border=None)
        self.graphics_view.setCentralItem(self.plot_layout)
        self.plot_layout.setContentsMargins(2, 2, 2, 2)

        self.main_window.show()
        self.main_window.raise_()
        self.main_window.activateWindow()

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

    def _render(self):
        self.plot_layout.clear()

        visible = self._visible_pairs()
        n = len(visible)
        rowlen = max(1, int(math.sqrt(n * 1.61803398875)))

        row_offset = 0
        if self.path_note:
            # labels are bare letters here (see resolve_labels()), since
            # the source paths' basenames collided (e.g. all ended in
            # ".../<instrument>/1/") - shown here as an on-canvas header
            # row (rather than only in the window title, which
            # dumpfile_pqtg()'s scene export wouldn't capture) so the
            # disambiguation survives into saved PNG/SVG exports too.
            self.plot_layout.addLabel(self.path_note, row=0, col=0, colspan=max(rowlen, 1))
            row_offset = 1

        if n <= 2:
            fontsize = 14
        elif n <= 16:
            fontsize = 10
        else:
            fontsize = 8
        # verbose (fuller title/statistics) once drilled down to the single
        # panel, matching McPyqtgraphPlotter's own n<=4 overview threshold
        # for ordinary monitors, but here n==1 always means "single view"
        # rather than "a small overview", so use that as the trigger.
        verbose = (n == 1)

        self.viewbox_list = []
        for i, (key, datas) in enumerate(visible):
            plt = pg.PlotItem()
            vb = plot_coplot_1D(datas, plt, self.labels, self.colours,
                                 log=self.log, fontsize=fontsize, verbose=verbose)
            self.viewbox_list.append(vb)
            self.plot_layout.addItem(plt, row_offset + i // rowlen, i % rowlen)

    def _get_plot_index(self, pos):
        ''' Index of the viewbox containing scene-position pos, or -1.
            Copied from pqtgfrontend.McPyqtgraphPlotter.get_plot_index(). '''
        if not self.viewbox_list or pos is None:
            return -1
        for idx, viewbox in enumerate(self.viewbox_list):
            topRight = viewbox.mapViewToScene(viewbox.viewRect().topRight())
            bottomLeft = viewbox.mapViewToScene(viewbox.viewRect().bottomLeft())
            rect = QtCore.QRectF()
            rect.setTopRight(topRight)
            rect.setBottomLeft(bottomLeft)
            if rect.contains(pos):
                return idx
        return -1

    def _click_handler(self, event):
        if _event_mods_int(event) != 0:
            return  # no ctrl/alt-click concept for co-plot (no "sweep")

        btn = _event_button_int(event)
        try:
            idx = self._get_plot_index(event.scenePos())
        except AttributeError:
            return
        if idx < 0:
            return

        if btn == _LEFT_BUTTON and self.current is None:
            # only meaningful in overview mode - the single view has
            # nowhere further to drill into
            self._show_single(idx)
        elif btn == _RIGHT_BUTTON and self.current is not None:
            self._show_overview()

    def _show_help(self):
        prefix = "mc" if mccode_config.configuration["MCCODE"] == "mcstas" else "mx"
        QtWidgets.QMessageBox.about(self.main_window, prefix + 'coplot-pyqtgraph', get_help_string())

    def _set_handlers(self):
        try:
            self.plot_layout.scene().sigMouseClicked.disconnect()
        except TypeError:
            pass
        self.plot_layout.scene().sigMouseClicked.connect(self._click_handler)

        K = _Qt
        savefile_cb = lambda fmt: utils.dumpfile_pqtg(
            scene=self.plot_layout.scene(), filenamebase=self.filenamebase, format=fmt)

        def key_handler(ev):
            key = ev.key()
            if key == K.Key_Q:
                QtWidgets.QApplication.quit()
            elif key == K.Key_L:
                self.log = not self.log
                self._replot()
            elif key == K.Key_P:
                savefile_cb('png')
            elif key == K.Key_S or key == 83:  # 83 == ord('s')
                savefile_cb('svg')
            elif key == K.Key_B:
                if self.current is not None:
                    self._show_overview()
            elif key in (K.Key_F1, K.Key_H):
                self._show_help()

        self.plot_layout.scene().keyPressEvent = key_handler

    def _replot(self):
        self._render()
        self._set_handlers()


def main(args):
    ''' load and match N simulation results' 1D monitors, then hand the
        resulting groups to the pyqtgraph co-plot frontend above. '''
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

        labels, used_fallback = diffloader.resolve_labels(paths, given_labels)
        colours = diffloader.resolve_colours(len(paths), given_colours)

        # When the auto-derived labels collided (e.g. several runs all
        # ending in a plain ".../<instrument>/1/" folder) and
        # resolve_labels() fell back to bare letters, those letters carry
        # no identifying information on their own - show the full source
        # paths as an on-canvas header row (see McCoplotPlotter._render())
        # and in the window title, while the per-panel legend keeps just
        # the letters.
        path_note = None
        title = 'coplot: %s' % ' vs '.join(labels)
        if used_fallback:
            path_note = "   ".join("%s: %s" % (lbl, p) for lbl, p in zip(labels, paths))
            title = 'coplot: %s' % path_note

        monitors_list = []
        try:
            for p in paths:
                monitors, _ = diffloader.load_monitors(p)
                monitors_list.append(monitors)
        except Exception as e:
            print('mccoplot loader: ' + e.__str__())
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

        plotter = McCoplotPlotter(pairs, labels, colours,
                                   invcanvas=args.invcanvas, title=title, path_note=path_note,
                                   filenamebase="coplot_" + "_vs_".join(diffloader.dirsafe_name(p) for p in paths))
        print(get_help_string())
        plotter.run()

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
    parser.add_argument('--invcanvas', action='store_true', help='invert canvas background from black to white')
    args = parser.parse_args()

    mccode_config.load_config("user")

    main(args)
