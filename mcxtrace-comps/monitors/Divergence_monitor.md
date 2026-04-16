# The `Divergence_monitor` Component

*McXtrace: Horizontal+vertical divergence monitor.*

## Identification

- **Site:** 
- **Author:** Erik B Knudsen
- **Origin:** DTU Physics
- **Date:** Jun. '16

## Description

```text
A 2D divergence sensitive monitor. The counts are distributed in
(n times m) pixels.

Example: Divergence_monitor(nh=20, nv=20, filename="Output.pos",
xwidth=0.1, yheight=0.1,
maxdiv_h=2, maxdiv_v=2)
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| nh | 1 | Number of pixel rows | 20 |
| nv | 1 | Number of pixel columns | 20 |
| rad | 1 | If set - divergence will be measured in radians. | 0 |
| filename | str | Name of file in which to store the detector image text | 0 |
| xwidth | m | Width of detector. | 0.1 |
| yheight | m | Height of detector. | 0.1 |
| maxdiv_h | degrees | Maximal horizontal divergence detected | 1 |
| maxdiv_v | degrees | Maximal vertical divergence detected | 1 |
| restore_xray | 1 | If set, the monitor does not influence the photon state | 0 |
| nx | 1 | Vector definition of "forward" direction wrt. divergence, to be used e.g. when the monitor is rotated into the horizontal plane | 0 |
| ny | 1 | Vector definition of "forward" direction wrt. divergence, to be used e.g. when the monitor is rotated into the horizontal plane | 0 |
| nz | 1 | Vector definition of "forward" direction wrt. divergence, to be used e.g. when the monitor is rotated into the horizontal plane | 1 |
| nowritefile | 1 | If set, monitor will skip writing to disk | 0 |

## Links

- [Source code](/Users/peterwillendrup/Projects/willend-McCode/mcxtrace-comps/monitors/Divergence_monitor.comp) for `Divergence_monitor.comp`.

---

*Generated on mcxtrace 3.99.99.*