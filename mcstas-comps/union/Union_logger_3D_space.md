# The `Union_logger_3D_space` Component

*McStas: Three dimensional logger for spatial dimensions*

## Identification

- **Site:** 
- **Author:** Mads Bertelsen
- **Origin:** University of Copenhagen
- **Date:** 20.08.15

## Description

```text
Part of the Union components, a set of components that work together and thus
sperates geometry and physics within McStas.
The use of this component requires other components to be used.

1) One specifies a number of processes using process components
2) These are gathered into material definitions using Union_make_material
3) Geometries are placed using Union_box/cylinder/sphere, assigned a material
4) A Union_master component placed after all of the above

Only in step 4 will any simulation happen, and per default all geometries
defined before this master, but after the previous will be simulated here.

There is a dedicated manual available for the Union_components

This logger logs a 2D projection of the position of each scattering in the lab
frame. It does this in n3 space slices, so one can get a full 3D histogram of
scattering positions.

A logger will log something for scattering events happening to certain volumes,
which are specified in the target_geometry string. By leaving it blank, all
geometries are logged, even the ones not defined at this point in the
instrument file. If a list og target_geometries is selected, one can further
narrow the events logged by providing a list of process names in target_process
which need to correspond with names of defined Union_process components.

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
| target_geometry | string | Comma seperated list of geometry names that will be logged, leave empty for all volumes (even not defined yet) | "NULL" |
| target_process | string | Comma seperated names of physical processes, if volumes are selected, one can select Union_process names | "NULL" |
| D1_min | m | histogram boundery, min position value for first axis | -1 |
| D1_max | m | histogram boundery, max position value for first axis | 1 |
| D2_min | m | histogram boundery, min position value for second axis | -1 |
| D2_max | m | histogram boundery, max position value for second axis | 1 |
| D3_min | m | histogram boundery, min position value for third axis | -1 |
| D3_max | m | histogram boundery, max position value for third axis | 1 |
| D_direction_1 | string | Direction for first axis ("x", "y" or "z") | "x" |
| D_direction_2 | string | Direction for second axis ("x", "y" or "z") | "z" |
| D_direction_3 | string | Direction for second axis ("x", "y" or "z") | "z" |
| filename | string | Filename of produced data file | "NULL" |
| n1 | 1 | number of bins for first axis | 90 |
| n2 | 1 | number of bins for second axis | 90 |
| n3 | 1 | number of bins for third axis | 10 |
| order_total | 1 | Only log rays that scatter for the n'th time, 0 for all orders | 0 |
| order_volume | 1 | Only log rays that scatter for the n'th time in the same geometry | 0 |
| order_volume_process | 1 | Only log rays that scatter for the n'th time in the same geometry, using the same process | 0 |
| logger_conditional_extend_index | 1 | If a conditional is used with this logger, the result of each conditional calculation can be made available in extend as a array called "logger_conditional_extend", and one would then acces logger_conditional_extend[n] if logger_conditional_extend_index is set to n | -1 |
| init | string | name of Union_init component (typically "init", default) | "init" |

## Links

- [Source code](/Users/peterwillendrup/Projects/willend-McCode/mcstas-comps/union/Union_logger_3D_space.comp) for `Union_logger_3D_space.comp`.

---

*Generated on mcstas 3.99.99.*