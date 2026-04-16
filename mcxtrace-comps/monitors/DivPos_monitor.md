# The `DivPos_monitor` Component

*McXtrace: Release: McXtrace 1.3

Divergence/position monitor (acceptance diagram).*

## Identification

- **Site:** 
- **Author:** Erik B Knudsen
- **Origin:** DTU Physics
- **Date:** Jun. 16

## Description

```text
2D detector for intensity as a function of both horizontal position
and wavelength. This gives information similar to an aceptance diagram used
eg. to investigate beam profiles in neutron guides.

Example: DivPos_monitor(nh=20, ndiv=20, filename="Output.dip",
xwidth=0.1, yheight=0.1, maxdiv_h=2)
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| nh | 1 | Number of bins in position | 20 |
| ndiv | 1 | Number of bins in divergence | 20 |
| filename | str | Name of file in which to store the detector image | 0 |
| xwidth | m | Width of detector. | 0.1 |
| yheight | m | Height of detector. | 0.1 |
| maxdiv_h | deg | Maximal horizontal divergence detected | 2 |
| restore_xray | 1 | If set, the monitor does not influence the photon state | 0 |
| nx | 1 | Vector definition of "forward" direction wrt. divergence, to be used e.g. when the monitor is rotated into the horizontal plane | 0 |
| ny | 1 | Vector definition of "forward" direction wrt. divergence, to be used e.g. when the monitor is rotated into the horizontal plane | 0 |
| nz | 1 | Vector definition of "forward" direction wrt. divergence, to be used e.g. when the monitor is rotated into the horizontal plane | 1 |
| nowritefile | 1 | If set, monitor will skip writing to disk. | 0 |

## Links

- [Source code](/Users/peterwillendrup/Projects/willend-McCode/mcxtrace-comps/monitors/DivPos_monitor.comp) for `DivPos_monitor.comp`.

---

*Generated on mcxtrace 3.99.99.*