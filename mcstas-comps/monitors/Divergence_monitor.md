# The `Divergence_monitor` Component

*McStas: Horizontal+vertical divergence monitor.*

## Identification

- **Site:** 
- **Author:** Kim Lefmann
- **Origin:** Risoe
- **Date:** Nov. 11, 1998

## Description

```text
A divergence sensitive monitor. The counts are distributed in
(n times m) pixels.

Example: Divergence_monitor(nh=20, nv=20, filename="Output.pos",
xmin=-0.1, xmax=0.1, ymin=-0.1, ymax=0.1,
maxdiv_h=2, maxdiv_v=2)
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| nh | 1 | Number of pixel rows | 20 |
| nv | 1 | Number of pixel columns | 20 |
| filename | str | Name of file in which to store the detector image text | 0 |
| xmin | m | Lower x bound of detector opening | -0.05 |
| xmax | m | Upper x bound of detector opening | 0.05 |
| ymin | m | Lower y bound of detector opening | -0.05 |
| ymax | m | Upper y bound of detector opening | 0.05 |
| nowritefile | 1 | If set, monitor will skip writing to disk | 0 |
| xwidth | m | Width of detector. Overrides xmin, xmax | 0 |
| yheight | m | Height of detector. Overrides ymin, ymax | 0 |
| maxdiv_h | degrees | Maximal vertical divergence detected | 2 |
| maxdiv_v | degrees | Maximal vertical divergence detected | 2 |
| restore_neutron | 1 | If set, the monitor does not influence the neutron state | 0 |
| nx | 1 |  | 0 |
| ny | 1 | Vector definition of "forward" direction wrt. divergence, to be used e.g. when the monitor is rotated into the horizontal plane | 0 |
| nz | 1 |  | 1 |

## Links

- [Source code](Divergence_monitor.comp) for `Divergence_monitor.comp`.

---

*Generated on mcstas 3.99.99.*