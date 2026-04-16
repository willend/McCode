# The `Flex_monitor_1D` Component

*McStas: Flexible monitor.*

## Identification

- **Site:** 
- **Author:** Erik B Knudsen & Peter Willendrup
- **Origin:** DTU Physics
- **Date:** Oct '20

## Description

```text
A square 1D single monitor that measures intensity (or something else) as a function of some variable or parameter.

Example: Flex_monitor_1D(nU=20, filename="Output", ustring="x", Umin=-.1, Umax=.1)
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| nU | 1 | Number of U channels | 20 |
| filename | string | Name of file in which to store the detector image | 0 |
| **Umin** |  | Minimum U to detect |  |
| **Umax** |  | Maximum U to detect |  |
| uid | 1 | Integer index of uservar to be monitored. Overrides ustring. | -1 |
| ustring | string | Name of variable (user or neutron state parameter as a string) to be monitored. | "" |
| restore_neutron | 1 | If set, the monitor does not influence the neutron state | 0 |
| signal | string | Name of variable to be used as an additive signal to be monitored. Default is intensity. | "p" |
| nowritefile | 1 | Flag to indicate if monitor should not save any data. | 0 |

## Links

- [Source code](/Users/peterwillendrup/Projects/willend-McCode/mcstas-comps/monitors/Flex_monitor_1D.comp) for `Flex_monitor_1D.comp`.

---

*Generated on mcstas 3.99.99.*