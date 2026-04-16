# The `Flex_monitor_2D` Component

*McStas: Flexible monitor.*

## Identification

- **Site:** 
- **Author:** Erik B Knudsen & Peter Willendrup
- **Origin:** DTU Physics
- **Date:** Oct '20

## Description

```text
A square 2D single monitor that measures intensity (or something else) as a function of two selectable variables or parameters.

Example: Flex_monitor_2D(nU1=20, nU2=20, filename="Output", ustring1="x", ustring2="y", Umin1=-.1, Umax1=.1, Umin2=-.1, Umax2=.1)
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| nU1 | 1 | Number of U1 channels | 20 |
| nU2 | 1 | Number of U1 channels | 20 |
| filename | string | Name of file in which to store the detector image | 0 |
| **Umin1** |  | Minimum U1 to detect |  |
| **Umax1** |  | Maximum U1 to detect |  |
| uid1 | 1 | Integer index of uservar to be monitored. Overrides ustring1. | -1 |
| ustring1 | string | Name of variable U1 (user or neutron state parameter as a string) to be monitored. | "" |
| **Umin2** |  | Minimum U1 to detect |  |
| **Umax2** |  | Maximum U1 to detect |  |
| uid2 | 1 | Integer index of uservar to be monitored. Overrides ustring2. | -1 |
| ustring2 | string | Name of variable U2 (user or neutron state parameter as a string) to be monitored. | "" |
| restore_neutron | 1 | If set, the monitor does not influence the neutron state | 0 |
| signal | string | Name of variable to be used as an additive signal to be monitored. Default is intensity. | "p" |
| nowritefile | 1 | Flag to indicate if monitor should not save any data. | 0 |

## Links

- [Source code](/Users/peterwillendrup/Projects/willend-McCode/mcstas-comps/monitors/Flex_monitor_2D.comp) for `Flex_monitor_2D.comp`.

---

*Generated on mcstas 3.99.99.*