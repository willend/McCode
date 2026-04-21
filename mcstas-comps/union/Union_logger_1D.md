# The `Union_logger_1D` Component

*McStas: One dimensional Union logger for several possible variables*

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

This logger in particular is not finished. It is supposed to allow several
different variables to be histogrammed, but currently only time is supported

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
| **min_value** | 1 | Histogram boundery for logged value |  |
| **max_value** | 1 | Histogram boundery for logged value |  |
| n1 | 1 | Number of bins in histogram | 90 |
| variable | string | Time for time in seconds, q for magnitude of scattering vector in 1/AA. | "time" |
| filename | string | Filename of produced data file | "NULL" |
| order_total | 1 | Only log rays that scatter for the n'th time, 0 for all orders | 0 |
| order_volume | 1 | Only log rays that scatter for the n'th time in the same geometry | 0 |
| order_volume_process | 1 | Only log rays that scatter for the n'th time in the same geometry, using the same process | 0 |
| logger_conditional_extend_index | 1 | If a conditional is used with this logger, the result of each conditional calculation can be made available in extend as a array called "logger_conditional_extend", and one would then acces logger_conditional_extend[n] if logger_conditional_extend_index is set to n | -1 |
| init | string | Name of Union_init component (typically "init", default) | "init" |

## Links

- [Source code](Union_logger_1D.comp) for `Union_logger_1D.comp`.

---

*Generated on mcstas 3.99.99.*