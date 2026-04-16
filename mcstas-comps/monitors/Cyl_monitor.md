# The `Cyl_monitor` Component

*McStas: A 2D Position-sensitive monitor. The shape is cylindrical with
the axis vertical. The monitor covers the whole cylinder (360 degrees).*

## Identification

- **Site:** 
- **Author:** Kim Lefmann
- **Origin:** Risoe
- **Date:** October 26, 2000

## Description

```text
An (n times m) pixel PSD monitor with cylinder shape,
vertical axis, centered at (0,0,0).

Example: PSDcyl_monitor(nr=20, ny=20, filename="Output.cyl", yheight=0.2, radius=0.1)
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| nr | 1 | Number of pixel (radial) columns | 20 |
| filename | string | Name of file in which to store the detector image | 0 |
| yheight | m | Height of detector | 10 |
| radius | m | Radius of detector | 1 |
| restore_neutron | 1 | If set, the monitor does not influence the neutron state | 0 |
| thmin | deg | Minimum angle covered/measured | -180 |
| thmax | deg | Maximum angle covered/measured | 180 |
| nowritefile | 1 | If set, monitor will skip writing to disk | 0 |

## Links

- [Source code](/Users/peterwillendrup/Projects/willend-McCode/mcstas-comps/monitors/Cyl_monitor.comp) for `Cyl_monitor.comp`.

---

*Generated on mcstas 3.99.99.*