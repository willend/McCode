# The `Monitor_nD` Component

*McXtrace: Release: McXtrace 1.2

This component is a general Monitor that can output 0/1/2D signals
(Intensity or signal vs. [something] and vs. [something] ...)*

## Identification

- **Site:** 
- **Author:** <a href="mailto:farhi@ill.fr">Emmanuel Farhi</a>
- **Origin:** <a href="http://www.ill.fr">ILL</a>
- **Date:** 14th Feb 2000.

## Description

```text
This component is a general Monitor that can output 0/1/2D signals
It can produce many 1D signals (one for any variable specified in
option list), or a single 2D output (two variables correlation).
Also, an additional 'list' of photon events can be produced.
By default, monitor is square (in x/y plane). A disk shape is also possible
The 'cylinder' and 'banana' option will change that for a banana shape
The 'sphere' option simulates spherical detector. The 'box' is a box.
The cylinder, sphere and banana should be centered on the scattering point.
In normal configuration, the Monitor_nD measures the current parameters
of the photon that is beeing detected. But a PreMonitor_nD component can
be used in order to study correlations between a photon being detected in
a Monitor_nD place, and given parameters that are monitored elsewhere
(at <b>PreMonitor_nD</b>).
The monitor can also act as a 3He gas detector, taking into account the
detection efficiency.

The 'bins' and 'limits' modifiers are to be used after each variable,
and 'auto','log' and 'abs' come before it. (eg: auto abs log hdiv bins=10
limits=[-5 5]) When placed after all variables,  these two latter modifiers
apply to the signal (e.g. intensity). Unknown keywords are ignored.
If no limits are specified for a given observable, reasonable defaults will be
applied. Note that these implicit limits are <b>even</b> applied in list mode.

<b>Implicit limits for typical variables:</b>
(consult monitor_nd-lib.c if you don't find your variable here)
x, y, z: Derived from detection-object geometry
k: [0 10] Angs-1
v: [0 1e6] m/s
t: [0 1] s
p: [0 FLT_MAX] in intensity-units
vx, vy: [-1000 1000] m/s
vz: [0 10000] m/s
kx, ky: [-1 1] Angs-1
kz: [-10 10] Angs-1
energy, omega: [0 100] meV
lambda,wavelength: [0 100] Angs
sx, sy, sz: [-1 1] in polarisation-units
angle: [-50 50] deg
divergence, vdiv, hdiv, xdiv, ydiv: [-5 5] deg
longitude, lattitude: [-180 180] deg
photon: [0 simulaton_ncount]
id, pixel id: [0 FLT_MAX]
uservars u1,u2,u3: [-1e10 1e10]

In the case of multiple components at the same position, the 'parallel'
keyword must be used in each instance instead of defining a GROUP.

<b>Possible options are</b>
Variables to record:
kx ky kz k wavevector [Angs-1] Wavevector on x,y,z and norm
vx vy vz v            [m/s]    Velocity on x,y,z and norm
x y z radius          [m]      Distance, Position and norm
xy, yz, xz            [m]      Radial position in xy, yz and xz plane
kxy kyz kxz           [Angs-1] Radial wavevector in xy, yz and xz plane
vxy vyz vxz           [m/s]    Radial velocity in xy, yz and xz plane
t time                [s]      Time of Flight
energy omega          [keV]    energy of photon
lambda wavelength     [Angs]   wavelength of photon
sx sy sz              [1]      Spin
vdiv ydiv dy          [deg]    vertical divergence (y)
hdiv divergence xdiv  [deg]    horizontal divergence (x)
angle                 [deg]    divergence from <z> direction
theta longitude       [deg]    longitude (x/z) for sphere and cylinder
phi   lattitude       [deg]    lattitude (y/z) for sphere and cylinder

user user1            will monitor the [Mon_Name]_Vars.UserVariable{1|2|3}
user2 user3           to be assigned in an other component (see below)

p intensity flux      [phts/s  or  phts/cm^2/s]
ncounts n photon      [1]      photon ID, i.e current event index
pixel id              [1]      pixelID in histogram made of preceeding vars, e.g. 'theta y'. To set an offset PixelID use the 'min=value' keyword. Sets event mode.

<b>Other options keywords are:</b>
abs                       Will monitor the abs of the following variable or of the signal (if used after all variables)
auto                      Automatically set detector limits for one/all
all  {limits|bins|auto}   To set all limits or bins values or auto mode
binary {float|double}     with 'source' option, saves in compact files
bins=[bins=20]            Number of bins in the detector along dimension
borders                   To also count off-limits photons (X < min or X > max)
capture                   weight by capture flux (not validated)
exclusive                 absorb photon out of monitor limits
file=string               Detector image file name. default is component name, plus date and variable extension.
incoming                  Monitor incoming beam in non flat det
limits=[min max]          Lower/Upper limits for axes (see up for the variable unit)
list=[counts=1000] or all For a long file of photon characteristics with [counts] or all events
log                       Will monitor the log of the following variable or of the signal (if used after all variables)
min=[min_value]           Same as limits, but only sets the min or max
max=[max_value]
multiple                  Create multiple independant 1D monitors files
no or not                 Revert next option
outgoing                  Monitor outgoing beam (default)
parallel                  Use this option when the next component is at the same position (parallel components)
per cm2                   Intensity will be per cm^2 (detector area). Displays beam section.
per steradian             Intensity will be per steradian (requires auto)
premonitor                Will monitor photon parameters stored previously with <b>PreMonitor_nD</b>.
signal=[var]              Will monitor [var] instead of usual intensity
slit or absorb            Absorb photons that are out detector
source                    The monitor will save photon states
inactivate                To inactivate detector (0D detector)
verbose                   To display additional informations

Detector shape options (specified as xwidth,yheight,zdepth or x/y/z/min/max)
box                       Box of size xwidth, yheight, zdepth.
cylinder                  To get a cylindrical monitor (diameter is xwidth or set radius, height is yheight).
banana                    Same as cylinder, without top/bottom, on restricted angular area; use theta variable with limits to define arc. (diameter is xwidth or set radius, height is yheight).
disk                      Disk flat xy monitor. diameter is xwidth.
sphere                    To get a spherical monitor (e.g. a 4PI) (diameter is xwidth or set radius).
square                    Square flat xy monitor (xwidth, yheight).
previous                  The monitor uses PREVIOUS component as detector surface.

<b>EXAMPLES:</b>
MyMon = Monitor_nD(
xwidth = 0.1, yheight = 0.1, zdepth = 0,
options = "intensity per cm2 angle,limits=[-5 5] bins=10,with
borders, file = mon1");
will monitor photon angle from [z] axis, between -5
and 5 degrees, in 10 bins, into "mon1.A" output 1D file
options = "sphere theta phi outgoing"  for a sphere PSD detector (out
beam)  and saves into file "MyMon_[Date_ID].th_ph"
options = "banana, theta limits=[10,130], bins=120, y" a theta/height banana detector
options = "angle radius all auto"   is a 2D monitor with automatic limits
options = "list=1000 kx ky kz energy" records 1000 photon event in a file
options = "multiple kx ky kz, auto abs log t, and list all photons"
makes 4 output 1D files and produces a complete list for all photons
and monitor log(abs(tof)) within automatic limits (for t)
options = "theta y, sphere, pixel min=100"
a 4pi detector which outputs an event list with pixelID from the actual
detector surface, starting from index 100.

To dynamically define a number of bins, or limits:
Use in DECLARE:    char op[256];
Use in INITIALIZE: sprintf(op, "lambda limits=[%g %g], bins=%i", lmin, lmax, lbin);
Use in TRACE:      Monitor_nD(... options=op ...)

<b>How to monitor any instrument/component variable into a Monitor_nD</b>
Suppose you want to monitor a variable 'age' which you assign somwhere in
the instrument:
COMPONENT MyMonitor = Monitor_nD(
xwidth = 0.1, yheight = 0.1,
user1="age", username1="Age of the Captain [years]",
options="user1, auto")
AT ...

See also the example in <a href="PreMonitor_nD.html">PreMonitor_nD</a> to
monitor photon parameters cross-correlations.

%BUGS
The 'auto' option for guessing optimal variable bounds should NOT be used with MPI
as each process may use different limits.
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| user1 | str | Variable name of USERVAR to be monitored by user1. | "" |
| user2 | str | Variable name of USERVAR to be monitored by user2. | "" |
| user3 | str | Variable name of USERVAR to be monitored by user3. | "" |
| xwidth | m | Width of detector. | 0 |
| yheight | m | Height of detector. | 0 |
| zdepth | m | Thickness of detector (z). | 0 |
| bins | 1 | Number of bins to force for all variables. Use 'bins' keyword in 'options' for heterogeneous bins | 0 |
| min | u | Minimum range value to force for all variables. Use 'min' or 'limits' keyword in 'options' for other limits | -1e40 |
| max | u | Maximum range value to force for all variables. Use 'max' or 'limits' keyword in 'options' for other limits | 1e40 |
| restore_xray | 0\|1 | If set, the monitor does not influence the photon state. Equivalent to setting the 'parallel' option. | 0 |
| radius | m | Radius of sphere/banana shape monitor | 0 |
| options | str | String that specifies the configuration of the monitor. The general syntax is "[x] options..." (see <b>Descr.</b>). | "NULL" |
| filename | str | Output file name (overrides file=XX option). | "NULL" |
| geometry | str | Name of an OFF file to specify a complex geometry detector | "NULL" |
| nowritefile | 1 | If set, monitor will skip writing to disk | 0 |
| username1 | str | Name assigned to User1 | "NULL" |
| username2 | str | Name assigned to User2 | "NULL" |
| username3 | str | Name assigned to User3 | "NULL" |

## Links

- [Source code](/Users/peterwillendrup/Projects/willend-McCode/mcxtrace-comps/monitors/Monitor_nD.comp) for `Monitor_nD.comp`.
- <a href="PreMonitor_nD.html">PreMonitor_nD</a>

---

*Generated on mcxtrace 3.99.99.*