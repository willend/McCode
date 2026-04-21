# The `Union_abs_logger_1D_space_tof` Component

*McStas: Logger of absorption along 1D space and 1D time of flight*

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

A absorption logger will log something for each absorption event happening
in the geometry or geometries on which it is attached. These are specified
in the target_geometry string. By leaving it blank, all geometries are
logged, even the ones not defined at this point in the instrument file.
Multiple geometries are specified as a comma separated list.

This absorption logger records the absorbed intensity as a function of the
y position and time of flight. One common use could be to attach this
absorption logger to a cylindrical helium-3 volume, creating a model of
the detector volume. In such a detector, only the y position of the event
is known, and as such creates a similar dataset.

This absorption logger needs to be placed in space, the position is recorded in
the coordinate system of the logger component. Note the detection is along the
y axis of the component, so it is natural to place it relative to a cylinder.

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
| **yheight** | m | height of absorption logger |  |
| n | 1 | number of bins for spatial axis | 0.2 |
| time_min | s | Minimum time recorded | 0 |
| time_max | s | Maximum time recorded | 1 |
| time_bins | 1 | number of time bins | 100 |
| filename | string | Filename of produced data file | "NULL" |
| order_total | 1 | Only log rays that have scattered n times, -1 for all orders | -1 |
| order_volume | 1 | Only log rays that have scattered n times in the same geometry, -1 for all orders | -1 |
| logger_conditional_extend_index | 1 | If a conditional is used with this logger, the result of each conditional calculation can be made available in extend as a array called "logger_conditional_extend", and one would then access logger_conditional_extend[n] if logger_conditional_extend_index is set to n | -1 |
| init | string | name of Union_init component (typically "init", default) | "init" |

## Links

- [Source code](Union_abs_logger_1D_space_tof.comp) for `Union_abs_logger_1D_space_tof.comp`.

---

*Generated on mcstas 3.99.99.*