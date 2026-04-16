# The `Union_abs_logger_nD` Component

*McStas: A logger of absorption as events with Monitor_nD options*

## Identification

- **Site:** 
- **Author:** Mads Bertelsen
- **Origin:** ESS DMSC
- **Date:** 19.06.20

## Description

```text
Part of the Union components, a set of components that work together and thus
separates geometry and physics within McStas.
The use of this component requires other components to be used.

1) One specifies a number of processes using process components
2) These are gathered into material definitions using Union_make_material
3) Geometries are placed using Union_box/cylinder/sphere, assigned a material
4) Logger and conditional components can be placed which will record what happens
5) A Union_master component placed after all of the above

Only in step 5 will any simulation happen, and per default all geometries
defined before this master, but after the previous will be simulated here.

There is a dedicated manual available for the Union_components

This component is an absorption logger, and thus placed in point 4) above.

An absorption logger will log something for each absorption event happening
in the geometry or geometries on which it is attached. These are specified
in the target_geometry string. By leaving it blank, all geometries are
logged, even the ones not defined at this point in the instrument file.
Multiple geometries are specified as a comma separated list.

This absorption logger stores absorption as events, with position, velocity,
time and weight. The Monitor_nD libraries are used to write the event files.
This version is a close copy of Monitor_nD, having the same interface, though
the user must be aware that no propagation happens for rays to hit the
detector pixels, instead it uses the position of absorbed. Use the previous
keyword to tell Monitor_nD that this is going on. It still needs values set
for xwidth and yheight, even though these will not be used.

This absorption logger needs to be placed in space, the position and velocity
is recorded in the coordinate system of the logger component.

It is possible to attach one or more conditional components to this absorption
logger. Such a conditional component would impose a condition on the state of
the neutron after the Union_master component that executes the simulation,
and the absorption logger will only record the event if this condition is true.

To use the logger_conditional_extend function, set it to some integer value n
and make and extend section to the master component that runs the geometry.
In this extend function, logger_conditional_extend[n] is 1 if the conditional
stack evaluated to true, 0 if not. This way one can check what rays is logged
using regular McStas monitors. Only works if a conditional is applied to this
logger.
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| target_geometry | string | Comma separated list of geometry names that will be logged, leave empty for all volumes (even not defined yet) | "NULL" |
| order_total | 1 | Only log rays that have scattered n times, -1 for all orders | -1 |
| order_volume | 1 | Only log rays that have scattered n times in the same geometry, -1 for all orders | -1 |
| logger_conditional_extend_index | 1 | If a conditional is used with this logger, the result of each conditional calculation can be made available in extend as a array called "logger_conditional_extend", and one would then access logger_conditional_extend[n] if logger_conditional_extend_index is set to n | -1 |
| init | string | Name of Union_init component (typically "init", default) | "init" |
| user1 | str | Variable name of USERVAR to be monitored by user1. | "" |
| user2 | str | Variable name of USERVAR to be monitored by user2. | "" |
| user3 | str | Variable name of USERVAR to be monitored by user3. | "" |
| xwidth | m | Width of detector. | 0 |
| yheight | m | Height of detector. | 0 |
| zdepth | m | Thickness of detector (z). | 0 |
| xmin | m | Lower x bound of opening | 0 |
| xmax | m | Upper x bound of opening | 0 |
| ymin | m | Lower y bound of opening | 0 |
| ymax | m | Upper y bound of opening | 0 |
| zmin | m | Lower z bound of opening | 0 |
| zmax | m | Upper z bound of opening | 0 |
| bins | 1 | Number of bins to force for all variables. Use 'bins' keyword in 'options' for heterogeneous bins | 0 |
| min | u | Minimum range value to force for all variables. Use 'min' or 'limits' keyword in 'options' for other limits | -1e40 |
| max | u | Maximum range value to force for all variables. Use 'max' or 'limits' keyword in 'options' for other limits | 1e40 |
| restore_neutron | 0\|1 | Not functional for Union version | 0 |
| radius | m | Radius of sphere/banana shape monitor | 0 |
| options | str | String that specifies the configuration of the monitor. The general syntax is "[x] options..." (see <b>Descr.</b>). | "NULL" |
| filename | str | Output file name (overrides file=XX option). | "NULL" |
| geometry | str | Name of an OFF file to specify a complex geometry detector | "NULL" |
| nowritefile | 1 | Not functional for Union version | 0 |
| nexus_bins | 1 | NeXus mode only: store component BIN information <br>(-1 disable, 0 enable for list mode monitor, 1 enable for any montor) | 0 |
| username1 | str | Name assigned to User1 | "NULL" |
| username2 | str | Name assigned to User2 | "NULL" |
| username3 | str | Name assigned to User3 | "NULL" |

## Links

- [Source code](/Users/peterwillendrup/Projects/willend-McCode/mcstas-comps/union/Union_abs_logger_nD.comp) for `Union_abs_logger_nD.comp`.
- See also <a href="../monitors/Monitor_nD.html">the Monitor_nD mcdoc page"</a>

---

*Generated on mcstas 3.99.99.*