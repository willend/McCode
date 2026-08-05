#!/usr/bin/env python3
'''
pyqtgraph mccoplot frontend.

This is a companion to mcplotdiff.py (mcplot-diff-pyqtgraph), sharing its
command-line syntax and monitor-matching logic. Instead of computing and
plotting the *difference* between two simulation results, mccoplot.py
overlays the two datasets on the same axes, for direct visual comparison of
curve shape and position rather than the size of the gap between them.

Only 1D monitors are supported: a and b are matched by output filename via
mccodelib.mcplotdiffloader.match_1d_monitors() (shared with the
mcplot-coplot-html and mcplot-coplot-matplotlib frontends), and any matched
pair that isn't a 1D/1D match is skipped with a warning.

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

# Default overlay colours (a, b): a colourblind-friendly blue/red pair.
COLOUR_A = '#1f77b4'
COLOUR_B = '#d62728'


def get_help_string():
    helplines = []
    helplines.append('')
    helplines.append('q              - quit')
    helplines.append('p              - save png')
    helplines.append('s              - save svg')
    helplines.append('l              - log toggle')
    helplines.append('F1/h           - help')
    return '\n'.join(helplines)


def plot_coplot_1D(data_a, data_b, plt, label_a, label_b, colour_a, colour_b,
                    log=False, legend=True, fontsize=10, verbose=False):
    ''' overlay data_a and data_b (both Data1D) into the pyqtgraph PlotItem plt '''
    x_a = np.array(data_a.xvals).astype(float)
    y_a = np.array(data_a.yvals).astype(float)
    e_a = np.array(data_a.y_err_vals).astype(float)
    x_b = np.array(data_b.xvals).astype(float)
    y_b = np.array(data_b.yvals).astype(float)
    e_b = np.array(data_b.y_err_vals).astype(float)

    if log:
        def _tolog(y):
            nonzeros = np.where(y > 0)[0]
            if len(nonzeros) > 0:
                y = y.copy()
                y[y <= 0] = np.min(y[nonzeros]) / 10
                return y, True
            return y, False
        y_a, ok_a = _tolog(y_a)
        y_b, ok_b = _tolog(y_b)
        plt.setLogMode(y=(ok_a or ok_b))
    else:
        plt.setLogMode(y=False)

    xmin = min(np.min(x_a), np.min(x_b))
    xmax = max(np.max(x_a), np.max(x_b))
    plt.setXRange(xmin, xmax, padding=0)

    plt.setTitle(" ")
    plt.getAxis('bottom').setLabel(data_a.xlabel)
    plt.getAxis('left').setLabel(data_a.ylabel)

    beam_a = (x_a[1] - x_a[0]) * 0.5 if len(x_a) > 1 else 0
    beam_b = (x_b[1] - x_b[0]) * 0.5 if len(x_b) > 1 else 0

    # TODO (same as plotfuncs.plot_Data1D): no error bars in log mode
    if not log:
        plt.addItem(pg.ErrorBarItem(x=x_a, y=y_a, height=e_a, beam=beam_a, pen=colour_a))
        plt.addItem(pg.ErrorBarItem(x=x_b, y=y_b, height=e_b, beam=beam_b, pen=colour_b))

    if legend:
        plt.legend = plotfuncs.ModLegend(offset=(-1, 1), text_size='%spt' % str(fontsize))
        plt.legend.setParentItem(plt.vb)

    try:
        header = '%s [%s]' % (data_a.component, data_a.filename)
        if verbose:
            header = '%s [%s]<br>%s' % (data_a.component, data_a.filename, data_a.title)
    except Exception:
        header = '%s' % data_a.component
    name_a = '<b>%s</b><br>%s' % (header, label_a)

    # actual curves, plotted with an explicit pen per series - since
    # plt.legend is already set, plot(..., name=...) registers each curve
    # with the legend automatically, using the curve's own pen as the
    # swatch colour (no need for the "invisible dummy artist" trick
    # ordinary single-dataset plots use, since here both series are real
    # and worth a legend entry each).
    plt.plot(x_a, y_a, pen=colour_a, name=name_a)
    plt.plot(x_b, y_b, pen=colour_b, name=label_b)

    plt.setMenuEnabled(False)
    return plt.getViewBox()


class McCoplotPlotter():
    ''' Minimal pyqtgraph co-plot frontend: renders a static grid of
        overlaid (a, b) 1D monitor pairs. Deliberately has no click-based
        drill-down (unlike mccodelib.pqtgfrontend.McPyqtgraphPlotter) - a
        co-plot panel is already the finest level of detail there is. '''

    def __init__(self, pairs, label_a, label_b, colour_a, colour_b, invcanvas=False, title=None):
        self.pairs = pairs
        self.label_a = label_a
        self.label_b = label_b
        self.colour_a = colour_a
        self.colour_b = colour_b
        self.log = False
        self.title = title if title is not None else ('coplot: %s vs %s' % (label_a, label_b))
        self.filenamebase = 'coplot_%s_vs_%s' % (label_a, label_b)

        self.app = QtWidgets.QApplication.instance() or QtWidgets.QApplication(sys.argv)

        if invcanvas:
            pg.setConfigOption('background', 'w')
            pg.setConfigOption('foreground', 'k')

    def run(self):
        self._create_window()
        self._render()
        self._set_keyhandler()

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

    def _render(self):
        self.plot_layout.clear()

        n = len(self.pairs)
        rowlen = max(1, int(math.sqrt(n * 1.61803398875)))

        if n <= 2:
            fontsize = 14
        elif n <= 16:
            fontsize = 10
        else:
            fontsize = 8
        verbose = n <= 4

        for i, (key, data_a, data_b) in enumerate(self.pairs):
            plt = pg.PlotItem()
            plot_coplot_1D(data_a, data_b, plt, self.label_a, self.label_b,
                            self.colour_a, self.colour_b, log=self.log,
                            fontsize=fontsize, verbose=verbose)
            self.plot_layout.addItem(plt, i // rowlen, i % rowlen)

    def _show_help(self):
        prefix = "mc" if mccode_config.configuration["MCCODE"] == "mcstas" else "mx"
        QtWidgets.QMessageBox.about(self.main_window, prefix + 'coplot-pyqtgraph', get_help_string())

    def _set_keyhandler(self):
        K = _Qt
        savefile_cb = lambda fmt: utils.dumpfile_pqtg(
            scene=self.plot_layout.scene(), filenamebase=self.filenamebase, format=fmt)

        def key_handler(ev):
            key = ev.key()
            if key == K.Key_Q:
                QtWidgets.QApplication.quit()
            elif key == K.Key_L:
                self.log = not self.log
                self._render()
            elif key == K.Key_P:
                savefile_cb('png')
            elif key == K.Key_S or key == 83:  # 83 == ord('s')
                savefile_cb('svg')
            elif key in (K.Key_F1, K.Key_H):
                self._show_help()

        self.plot_layout.scene().keyPressEvent = key_handler


def main(args):
    ''' load and match two simulation results' 1D monitors, then hand the
        resulting pairs to the pyqtgraph co-plot frontend above. '''
    logging.basicConfig(level=logging.INFO)

    # ensure keyboardinterrupt ctr-c
    import signal
    signal.signal(signal.SIGINT, signal.SIG_DFL)

    try:
        label_a = args.label_a[0] if args.label_a else None
        label_b = args.label_b[0] if args.label_b else None
        colour_a = args.colour_a[0] if args.colour_a else COLOUR_A
        colour_b = args.colour_b[0] if args.colour_b else COLOUR_B

        label_a, label_b = diffloader.default_labels(args.a, args.b, label_a, label_b)

        try:
            monitors_a, dir_a = diffloader.load_monitors(args.a)
            monitors_b, dir_b = diffloader.load_monitors(args.b)
        except Exception as e:
            print('mccoplot loader: ' + e.__str__())
            quit()

        pairs = diffloader.match_1d_monitors(monitors_a, monitors_b, label_a, label_b)

        if len(pairs) == 0:
            print("mccoplot: no matching 1D monitors found between '%s' and '%s', nothing to plot."
                  % (args.a, args.b))
            quit()

        if args.test:
            print("mccoplot: %d matched 1D monitor pair(s):" % len(pairs))
            for key, data_a, data_b in pairs:
                print("  - %s (%s)" % (key, data_a.component))

        plotter = McCoplotPlotter(pairs, label_a, label_b, colour_a, colour_b,
                                   invcanvas=args.invcanvas,
                                   title='coplot: %s vs %s' % (label_a, label_b))
        print(get_help_string())
        plotter.run()

    except KeyboardInterrupt:
        print('keyboard interrupt')
    except Exception as e:
        print('mccoplot error: %s' % e.__str__())
        raise e


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument('a', help='first simulation file or directory')
    parser.add_argument('b', help='second simulation file or directory, co-plotted alongside "a"')
    parser.add_argument('-A', '--label-a', nargs=1, help='short label used for simulation a in the legend/titles')
    parser.add_argument('-B', '--label-b', nargs=1, help='short label used for simulation b in the legend/titles')
    parser.add_argument('--colour-a', nargs=1, help='override the overlay colour used for a (default %s)' % COLOUR_A)
    parser.add_argument('--colour-b', nargs=1, help='override the overlay colour used for b (default %s)' % COLOUR_B)
    parser.add_argument('-t', '--test', action='store_true', default=False, help='print the matched monitor pairs before plotting')
    parser.add_argument('--invcanvas', action='store_true', help='invert canvas background from black to white')
    args = parser.parse_args()

    mccode_config.load_config("user")

    main(args)
