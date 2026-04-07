'''
Plugable pyqtgraph mcplot frontend.
'''
import os
import sys
import math
import subprocess
import numpy as np

import qtpy
import pyqtgraph as pg
from pyqtgraph.Qt import QtCore, QtGui, QtWidgets

from . import utils
from . import mccode_config
from .mcplotloader import McCodeDataLoader, test_decfuncs, PlotGraphPrint
from .plotgraph import PNSingle, PNMultiple
from .mcplotloader import Data2D


def get_help_string():
    if sys.platform == 'darwin':
        modifier = 'Meta'
    elif sys.platform == 'win32':
        modifier = 'alt'
    else:
        modifier = 'ctrl'

    helplines = []
    helplines.append('')
    helplines.append('q              - quit')
    helplines.append('p              - save png')
    helplines.append('s              - save svg')
    helplines.append('l              - log toggle (disables plot from zero)')
    helplines.append('0              - plot 1D-curves from zero (disables log)')
    helplines.append('t              - textinfo toggle')
    helplines.append('c              - cycle colormap')
    helplines.append('F1/h           - help')
    helplines.append('F5             - replot')
    helplines.append('click          - display subplot')
    helplines.append('right-click/b  - back')
    helplines.append('%s + click   - sweep monitors' % modifier)
    helplines.append('x              - expand subplots')
    return '\n'.join(helplines)


class ViewModel():
    '''
    It is a kind of viewmodel, originally a log logstate housekeeping object,
    extended by various other logstate variables as well.
    '''
    def __init__(self, log=False, fromzero=False, legend=True, sourcedir=None):
        self.log = log
        self.fromzero = fromzero
        self.icolormap = 0
        self.legend = legend
        self.sourcedir = sourcedir
    def flip_log(self):
        self.log = not self.log
        if self.log:
            self.fromzero=False
        return self.log
    def flip_fromzero(self):
        self.fromzero = not self.fromzero
        if self.fromzero:
            self.log=False
        return self.fromzero
    def inc_colormap(self):
        self.icolormap += 1
    def flip_legend(self):
        self.legend = not self.legend
        return self.legend
    def logstate(self):
        return self.log
    def fromzerostate(self):
        return self.fromzero
    def legendstate(self):
        return self.legend
    def cmapindex(self):
        return self.icolormap
    def get_sourcedir(self):
        return self.sourcedir

# Various helper-functions for PyQt6/PySide6/PyQt5 support
# of event modifier handling...

# Single modifer -> int
def _to_int(x):
    try:
        return int(x)
    except Exception:
        try:
            return int(getattr(x, "value", x))
        except Exception:
            return 0

# Convert a set of modifiers to int
def mods_to_int(m):
    try:
        return int(m)
    except Exception:
        try:
            return int(getattr(m, "value", m))
        except Exception:
            try:
                v = 0
                for part in m:
                    v |= int(part)
                return v
            except Exception:
                return 0

# Look up int constant corresponding to given modifier
def qt_mod_constant(name):
    # Try Qt6 nested enum first, then Qt5 attributes
    try:
        return int(getattr(QtCore.Qt.KeyboardModifier, name))
    except Exception:
        try:
            return int(getattr(QtCore.Qt, name))
        except Exception:
            return 0

# Create a dict of "all intersting" modifiers
def _discover_qt_mod_masks():
    """Return dict with integer masks for Control, Meta, Alt, Shift and ALL_MODS."""
    # Try to read constants in standard locations first
    def try_get(name):
        try:
            # Qt6: nested enum
            return int(getattr(QtCore.Qt.KeyboardModifier, name))
        except Exception:
            try:
                return int(getattr(QtCore.Qt, name))
            except Exception:
                return None

    CTRL = try_get("ControlModifier")
    META = try_get("MetaModifier")
    ALT = try_get("AltModifier")
    SHIFT = try_get("ShiftModifier")

    # If any are None or zero, try to infer by probing event-generated values:
    # We will build a fallback mapping using common Qt6 flag values if available.
    # Known Qt6 modifier flag raw values on some builds (fallback):
    # (AI-assisted hack for macOS...)
    FALLBACK = {
        "ControlModifier": 0x10000000,   # 268435456
        "AltModifier":     0x04000000,   # 67108864
        "ShiftModifier":   0x08000000,   # 134217728
        "MetaModifier":    0x20000000,   # 536870912  (some builds use other values; we'll use detected below)
    }

    # Replace None or 0 with fallback if event flags appear to match those
    if not CTRL:
        CTRL = FALLBACK.get("ControlModifier")
    if not ALT:
        ALT = FALLBACK.get("AltModifier")
    if not SHIFT:
        SHIFT = FALLBACK.get("ShiftModifier")
    if not META:
        # On macOS Command may map to different Meta value; try the common one
        META = FALLBACK.get("MetaModifier")

    ALL = (CTRL or 0) | (META or 0) | (ALT or 0) | (SHIFT or 0)
    return {"CTRL": int(CTRL or 0), "META": int(META or 0),
            "ALT": int(ALT or 0), "SHIFT": int(SHIFT or 0), "ALL": int(ALL)}

class McPyqtgraphPlotter():
    '''
    PyQtGraph-based plotter class.
    '''
    def __init__(self, plotgraph, sourcedir, plot_func, invcanvas):
        '''
        plotgraph: plotgraph root node
        sourcedir: data files source directory
        plot_funct: the user-specified matching user data.
            Signature:
                node     - plotgraph node
                i        - int
                plt      - pqtg plot object
                opts     - (dict, see code)))

            returns:
                view_box - the click-able view box of the constructed plot object
                plt      - the plot object to be added to the pqtg window
        inv_canvas: inverts background from black to white
        '''
        self.graph = plotgraph
        self.sourcedir = sourcedir
        self.plot_func = plot_func
        self.isQt6 = True

        try:
            import PyQt6 as _pyqt6  # prefer PyQt6 if installed
            BINDING = "PyQt6"
        except Exception:
            try:
                import PySide6 as _pyside6
                BINDING = "PySide6"
            except Exception:
                try:
                    import PyQt5 as _pyqt5
                    BINDING = "PyQt5"
                except Exception:
                    BINDING = None
                    self.isQt6 = (BINDING in ("PyQt6", "PySide6"))

        print("Plotter activated Qt with binding: " + BINDING)
        self.app = QtWidgets.QApplication(sys.argv)
        self.QT_MASKS = _discover_qt_mod_masks()

        if invcanvas:
            # switch to using white background and black foreground
            pg.setConfigOption('background', 'w')
            pg.setConfigOption('foreground', 'k')


    def runplot(self):
        node = self.graph

        self.create_plotwindow(title=self.sourcedir)

        # create the logflipper
        self.viewmodel = ViewModel(sourcedir=self.sourcedir)

        # initiate event driven plot recursion
        self.plot_node(node)
        self.update_statusbar(None, node, None)

        # start
        if (not self.isQt6):
            sys.exit(self.app.exec_())  # Qt5
        else:
            sys.exit(self.app.exec())   # Qt6


    def create_plotwindow(self, title):
        ''' set up and return a plotlayout "window" '''

        helpmessage = QtWidgets.QLabel()
        helpmessage.setText("Press 'h' for app shortcuts.")

        self.statusmessage = QtWidgets.QLabel()

        statusbar = QtWidgets.QStatusBar()
        statusbar.addWidget(helpmessage)
        statusbar.addPermanentWidget(self.statusmessage)

        self.main_window = QtWidgets.QMainWindow()
        self.graphics_view = pg.GraphicsView(self.main_window)
        self.main_window.setCentralWidget(self.graphics_view)
        self.main_window.setStatusBar(statusbar)
        self.main_window.setWindowTitle(title)
        self.main_window.setMouseTracking(True)

        # window size
        if hasattr(QtWidgets.QApplication,"primaryScreen"):	# Qt6 and late Qt5
            rect = QtWidgets.QApplication.primaryScreen().size()
        else:               # earlier Qt5
            rect = QtWidgets.QApplication.desktop().screenGeometry()
        	

        # 
        w = int(0.7 * rect.width())
        h = int(0.7 * rect.height())
        self.main_window.resize(w, h)

        self.plot_layout = pg.GraphicsLayout(border=None)
        self.graphics_view.setCentralItem(self.plot_layout)
        self.plot_layout.setContentsMargins(2, 2, 2, 2) # outermost margin

        self.main_window.show()
        self.main_window.raise_()
        self.main_window.activateWindow()


    def plot_node(self, node, sync_zoom_obj_ids=[]):
        '''
        Event driven recursive plot function. Click events are registered with each recursion.
        '''
        # First check if we have been called with a meaningful node
        if node == None:
            return

        def get_modifiers(modname):
            ''' Get int codes for keyboardmodifiers. WARNING: String codes may be used directly in code. '''
            name = (modname or "").lower()
            CTRL = self.QT_MASKS["CTRL"]
            META = self.QT_MASKS["META"]
            ALT = self.QT_MASKS["ALT"]
            SHIFT = self.QT_MASKS["SHIFT"]
            if sys.platform == "darwin":
                CTRL_MASK = CTRL | META
            else:
                CTRL_MASK = CTRL
            return {
                "none": 0,
                "ctrl": CTRL_MASK,
                "meta": META,
                "shft": SHIFT,
                "ctrl-shft": CTRL_MASK | SHIFT,
                "alt": ALT,
                }.get(name, 0)

        # init
        self.clear_window_and_handlers()

        # get references from node
        parent = node.parent
        prim_lst = node.primaries
        sec_lst = node.secondaries

        # add plot instances and record viewbox results
        n = node.getnumdata()
        self.viewbox_list = []
        self.plot_list = []
        for i in range(n):
            viewbox, plt = self.add_plot(node, i, n)
            self.viewbox_list.append(viewbox)
            self.plot_list.append(plt)
        if id(node) in sync_zoom_obj_ids:
            self.sync_views_zooming()

        # set up viewbox - node correspondences for each action (click, right-click, ctrl-click, ...)
        node_list_click = []
        node_list_rclick = []
        node_list_ctrlclick = []

        # tag sync-zoom node id's (secondaries)
        sync_zoom_obj_ids = sync_zoom_obj_ids + [id(n) for n in sec_lst]

        # for each primary node, a click is registered to it
        node_list_click = prim_lst

        # if parent exists, all right-clicks are registered to it
        if parent:
            for i in range(n):
                node_list_rclick.append(parent)

        # for each secondary node, a ctrl-click is registered to it
        node_list_ctrlclick = sec_lst

        # set mouse click handlers on the window
        plot_node_cb = lambda node: self.plot_node(
            node, sync_zoom_obj_ids=sync_zoom_obj_ids)
        self.set_handler(node_list_click, plot_node_cb, "click", get_modifiers("none"))
        self.set_handler(node_list_rclick, plot_node_cb, "rclick", get_modifiers("none"))

        # set modifiers "alt" and "ctrl" for all platforms, since some may not work on win, darwin etc.
        self.set_handler(node_list_ctrlclick, plot_node_cb, "click", get_modifiers("alt"))
        self.set_handler(node_list_ctrlclick, plot_node_cb, "click", get_modifiers("ctrl"))

        # set keypress handlers
        replot_cb = lambda: self.plot_node(node)
        back_cb = lambda: self.plot_node(parent)
        self.set_keyhandler(replot_cb, back_cb, 'l', get_modifiers("none"))


    def show_help(self):
        if mccode_config.configuration["MCCODE"] == "mcstas":
            prefix = "mc"
        else:
            prefix = "mx"
        QtWidgets.QMessageBox.about(self.main_window, prefix+'plot-pyqtgraph', get_help_string())


    def set_keyhandler(self, replot_cb, back_cb, key, modifier):
        ''' sets a clickhadler according to input '''

        def key_handler(ev, replot_cb, back_cb, savefile_cb, flip_log, flip_fromzero, flip_legend, inc_cmap, expand_sp, debug=False):
            ''' global keypress handler, replot_cb is a function of log '''
            
            if hasattr(QtCore.Qt, "Key"):
              k = QtCore.Qt.Key
            else:
              k = QtCore.Qt
            
            if ev.key() == k.Key_Q:                 # q
                QtWidgets.QApplication.quit()
            elif ev.key() == k.Key_L:               # l
                flip_log()
                replot_cb()
            elif ev.key() == k.Key_0:               # 0
                flip_fromzero()
                replot_cb()
            elif ev.key() == k.Key_P:               # p
                savefile_cb(format='png')
            elif ev.key() == 83:                    # s
                savefile_cb(format='svg')
            elif ev.key() == k.Key_T:               # t
                print("Toggle legend visibility")
                flip_legend()
                replot_cb()
            elif ev.key() == k.Key_C:               # c
                inc_cmap()
                replot_cb()
            elif ev.key() == k.Key_F5:              # F5
                replot_cb()
            elif ev.key() == k.Key_X:               # x
                expand_sp()
            elif ev.key() == k.Key_F1 or ev.key() == k.Key_H:   # F1 or h
                self.show_help()
            elif ev.key() == k.Key_B:               # b
                back_cb()
            # print debug info
            if debug:
                print("key code: %s" % str(ev.key()))

        savefile_cb = lambda format: utils.dumpfile_pqtg(scene=self.plot_layout.scene(), format=format)
        expand_sp = lambda : self.expand_subplots(sourcedir=self.viewmodel.get_sourcedir())

        self.plot_layout.scene().keyPressEvent = \
            lambda ev: key_handler(ev = ev,
                                   replot_cb = replot_cb,
                                   savefile_cb = savefile_cb,
                                   back_cb = back_cb,
                                   flip_log = self.viewmodel.flip_log,
                                   flip_fromzero = self.viewmodel.flip_fromzero,
                                   flip_legend = self.viewmodel.flip_legend,
                                   inc_cmap = self.viewmodel.inc_colormap,
                                   expand_sp = expand_sp)


    def expand_subplots(self, sourcedir):
        ''' opens a new process of mcplot-pyqtgraph on each subdir '''
        # stolen from stack overflow:
        def get_immediate_subdirectories(a_dir):
            return [name for name in os.listdir(a_dir)
                    if os.path.isdir(os.path.join(a_dir, name))]
        def sortalpha(data):
            return sorted(data, key =
                lambda item: (
                    int(item.partition(' ')[0])
                    if item[0].isdigit() else float('inf'), item))

        subdirs = sortalpha(get_immediate_subdirectories(sourcedir))

        if len(subdirs) == 0:
            print("no subdirs to plot")
            return

        for s in subdirs:
            if mccode_config.configuration["MCCODE"] == "mcstas":
                prefix = "mc"
            else:
                prefix = "mx"
            subprocess.Popen(prefix+'plot-pyqtgraph %s' %
                os.path.join(sourcedir, s), shell=True, cwd=os.getcwd())


    def clear_window_and_handlers(self):
        ''' clears all click handlers on "rootui" '''
        self.plot_layout.clear()
        try:
            self.plot_layout.scene().sigMouseClicked.disconnect()
            self.plot_layout.scene().sigMouseMoved.disconnect()
        except TypeError:
            pass


    def set_handler(self, node_list, node_cb, click, modifier):
        ''' sets a clickhandler according to input '''
        if len(list(node_list)) == 0:
            return

        mod_mask = _to_int(modifier)
        CTRL = qt_mod_constant("ControlModifier")
        META = qt_mod_constant("MetaModifier")
        ALT = qt_mod_constant("AltModifier")
        SHIFT = qt_mod_constant("ShiftModifier")
        ALL_MODS = self.QT_MASKS["ALL"]

        is_qt6 = hasattr(QtCore.Qt, "KeyboardModifier")
        ButtonEnum = QtCore.Qt.MouseButton if is_qt6 else None

        def click_handler(event, node_list, node_cb, click, mod_mask, debug=False):
            posItem = None
            posScene = None
            plotIdx = -1
            try:
                posItem = event.pos()
                posScene = event.scenePos()
                plotIdx = self.get_plot_index(posScene)
            except Exception:
                pass
            if debug:
                print("raw event.modifiers():", event.modifiers())
            ev_mods = mods_to_int(event.modifiers())

            print("ev_mods:", ev_mods, "CTRL:", self.QT_MASKS['CTRL'], "META:", self.QT_MASKS['META'], "ALT:", self.QT_MASKS['ALT'], "SHIFT:", self.QT_MASKS['SHIFT'], "mod_mask:", mod_mask)
            
            # prevent action for modifiers mismatch
            if mod_mask:
                if (ev_mods & mod_mask) != mod_mask:
                    return
            else:
                if (ev_mods & ALL_MODS) != 0:
                    return
            if is_qt6:
                # prevent action for mouse button mismatch
                if click == "rclick" and event.button() != ButtonEnum.RightButton:
                    return
                if click == "click" and event.button() != ButtonEnum.LeftButton:
                    return
            else:
                # prevent action for mouse button mismatch
                if click == "rclick" and event.button() != 2:
                    return
                if click == "click" and event.button() != 1:
                    return
            if 0 <= plotIdx < len(node_list):
                node = node_list[plotIdx]

                # replot
                node_cb(node)

                # update status message
                self.update_statusbar(None, node, posItem)

        self.plot_layout.scene().sigMouseClicked.connect(
            lambda event: click_handler(
                event, node_list=node_list, node_cb=node_cb, click=click, mod_mask=mod_mask))

    def get_plot_func_opts(self, fromzero, log, legend, icolormap, verbose, fontsize, cbmin=None, cbmax=None):
        ''' returns a dict for holding the plot options relevant for this plotting frontend '''
        d = {}
        d['log'] = log
        d['fromzero'] = fromzero
        d['legend'] = legend
        d['icolormap'] = icolormap
        d['verbose'] = verbose
        d['fontsize'] = fontsize
        if cbmin != None and cbmax != None:
            d['cbmin'] = cbmin
            d['cbmax'] = cbmax
        return d


    def get_sweep_multiplot_colorbar_limits(self, node):
        if type(node) == PNMultiple:
            cbmin = float("inf")
            cbmax = float("-inf")
            monname = None
            for data in node.getdata_lst():
                if type(data) != Data2D:
                    continue

                # make sure all nodes in the multiplot have the same component name
                # (indicating comparable (sweep) data)
                if monname == None:
                    monname = data.component
                else:
                    if data.component != monname:
                        return None, None

                # update min/max values
                if type(data) == Data2D:
                    localmin = np.min(np.array(data.zvals))
                    localmax = np.max(np.array(data.zvals))
                    cbmin = min(cbmin, localmin)
                    cbmax = max(cbmax, localmax)
            return cbmin, cbmax
        return None, None


    def add_plot(self, node, i, n):
        ''' constructs a plot from data and adds this to layout '''

        def get_golden_rowlen(n):
            ''' find rowlength by golden ratio '''
            return int(math.sqrt(n*1.61803398875))

        plt = pg.PlotItem()
        rowlen = get_golden_rowlen(n)

        verbose = n<=4
        fontsize = (4, 10, 14)[int(n<=2) + int(n<12)]

        if self.viewmodel.logstate():
            cbmin = cbmax = None
        else:
            cbmin, cbmax = self.get_sweep_multiplot_colorbar_limits(node)

        options = self.get_plot_func_opts(self.viewmodel.fromzerostate(),
            self.viewmodel.logstate(), self.viewmodel.legendstate(), self.viewmodel.cmapindex(),
            verbose, fontsize, cbmin, cbmax)
        view_box, plt_itm = self.plot_func(node, i, plt, options)
        if view_box:
            self.plot_layout.addItem(plt_itm, i // rowlen, i % rowlen)

        # disconnect any old mouse handlers
        try:
            self.plot_layout.scene().sigMouseMoved.disconnect()
        except TypeError:
            pass

        mouse_func = lambda pos: self.update_statusbar(plt, node, pos)
        self.plot_layout.scene().sigMouseMoved.connect(mouse_func)

        return view_box, plt


    def update_statusbar(self, plot, node, pos):
        # if a single plot is visible, show the coordinates
        if isinstance(node, PNSingle):
            if plot == None and len(self.plot_list) == 1:
                plot = self.plot_list[0]
            self.single_plot_mouse_moved(plot, node, pos)
        # else show infos about the plots
        elif isinstance(node, PNMultiple):
            self.multi_plot_mouse_moved(node, pos)


    def single_plot_mouse_moved(self, plot, node, pos):
        ''' shows the mouse coordinates for single plots '''
        if plot!=None and pos!=None:
            pos = plot.getViewBox().mapSceneToView(pos)

        # get axis labels
        xlabel = ""
        ylabel = ""
        if node != None:
            xlabel = node.getdata_idx(0).xlabel
            ylabel = node.getdata_idx(0).ylabel
        if xlabel == "":
            xlabel = "x"
        if ylabel == "":
            ylabel = "y"

        if pos != None:
            x = pos.x()
            y = pos.y()
            logstr = ""
            if self.viewmodel.log:
                # TODO: do this for non-colourplots:
                #y = np.power(10., y)
                logstr = " (log)"
            posstr = "%.24s=%g, %.24s=%g%s." % (xlabel, x, ylabel, y, logstr)
        else:
            posstr = ""
        self.statusmessage.setText(posstr)


    def multi_plot_mouse_moved(self, node, pos):
        ''' shows information on multi-plots '''
        prim = node.primaries
        num_plots = node.getnumdata()
        statustext = ""

        # find the plot under the cursor
        idx = self.get_plot_index(pos)
        if idx >= 0:
            # plot found?
            statustext = "Plot %d/%d" % (idx+1, num_plots)
            if prim != None:
                title = prim[idx].getdata_idx(0).title
                # truncate the tile string if it's too long
                if len(title) > 64:
                    title = title[0:64] + "..."
                statustext += ": " + title
            statustext += "."
        else:
            if num_plots == 1:
                statustext = "Showing 1 plot."
            else:
                statustext = "Showing %d plots." % num_plots

        if self.viewmodel.log:
            statustext = "Mode: log. " + statustext
        else:
            statustext = "Mode: lin. " + statustext

        self.statusmessage.setText(statustext)


    def get_plot_index(self, pos):
        ''' get the plot index at (cursor) position pos '''
        if self.viewbox_list == None or pos == None:
            return -1

        for idx in range(len(self.viewbox_list)):
            viewbox = self.viewbox_list[idx]
            topRight = viewbox.mapViewToScene(viewbox.viewRect().topRight())
            bottomLeft = viewbox.mapViewToScene(viewbox.viewRect().bottomLeft())

            rect = QtCore.QRectF()
            rect.setTopRight(topRight)
            rect.setBottomLeft(bottomLeft)

            # plot found?
            if rect.contains(pos):
                return idx

        # plot not found
        return -1


    def sync_views_zooming(self):
        ''' replace individual viewbox wheel events with a new, global wheel event which calls all of them '''
        org_wheel_events = [vb.wheelEvent for vb in self.viewbox_list]
        def modded_wheel_event(ev, axis = None):
            for vb in self.viewbox_list:
                org_wheel_events[self.viewbox_list.index(vb)](ev, axis=axis)
        for vb in self.viewbox_list:
            vb.wheelEvent = modded_wheel_event
