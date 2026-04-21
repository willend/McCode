# The `DivPos_monitor` Component

*McStas: Divergence/position monitor (acceptance diagram).*

## Identification

- **Site:** 
- **Author:** Kristian Nielsen
- **Origin:** Risoe
- **Date:** 1999

## Description

```text
2D detector for intensity as a function of position
and divergence, either horizontally or vertically (depending on the flag vertical).
This gives information similar to an aceptance diagram used
eg. to investigate beam profiles in neutron guides.

Example: DivPos_monitor(nh=20, ndiv=20, filename="Output.dip",
xmin=-0.1, xmax=0.1, ymin=-0.1, ymax=0.1, maxdiv_h=2)
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| nb | 1 | Number of bins in position. | 20 |
| ndiv | 1 | Number of bins in divergence. | 20 |
| filename | string | Name of file in which to store the detector image. | 0 |
| xmin | m | Lower x bound of detector opening | -0.05 |
| xmax | m | Upper x bound of detector opening | 0.05 |
| ymin | m | Lower y bound of detector opening | -0.05 |
| ymax | m | Upper y bound of detector opening | 0.05 |
| xwidth | m | Width of detector. Overrides xmin,xmax. | 0 |
| yheight | m | Height of detector. Overrides ymin,ymax. | 0 |
| maxdiv | degrees | Maximal divergence detected. | 2 |
| restore_neutron | 1 | If set, the monitor does not influence the neutron state. | 0 |
| nx | 1 |  | 0 |
| ny | 1 | Vector definition of "forward" direction wrt. divergence, to be used e.g. when the monitor is rotated into the horizontal plane | 0 |
| nz | 1 |  | 1 |
| vertical | 1 | Monitor intensity as a function of vertical divergence and position. | 0 |
| nowritefile | 1 | If set, monitor will skip writing to disk | 0 |

## Links

- [Source code](DivPos_monitor.comp) for `DivPos_monitor.comp`.

---

*Generated on mcstas 3.99.99.*