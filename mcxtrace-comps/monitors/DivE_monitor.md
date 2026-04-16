# The `DivE_monitor` Component

*McXtrace: Divergence/Energy monitor.*

## Identification

- **Site:** 
- **Author:** Erik B Knudsen
- **Origin:** DTU Physics
- **Date:** Jun. 2016

## Description

```text
2D detector for intensity as a function of both horizontal divergence
and Energy.

Example: DivE_monitor(nE=20, nh=20, filename="Output.div",
xwidth=0.1, yheight=0.1,
maxdiv_h=2, Emin=2, Emax=10)
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| nE | 1 | Number of bins in energy | 20 |
| nh | 1 | Number of bins in divergence | 20 |
| filename | str | Name of file in which to store the detector image | 0 |
| xwidth | m | Width of detector. | 0.1 |
| yheight | m | Height of detector. | 0.1 |
| maxdiv_h | deg | Maximal horizontal divergence detected | 2 |
| **Emin** | keV | Minimum energy detected |  |
| **Emax** | keV | Maximum energy detected |  |
| restore_xray | 1 | If set, the monitor does not influence the photon state | 0 |
| nx | 1 | Vector definition of "forward" direction wrt. divergence, to be used e.g. when the monitor is rotated into the horizontal plane. | 0 |
| ny | 1 | Vector definition of "forward" direction wrt. divergence, to be used e.g. when the monitor is rotated into the horizontal plane. | 0 |
| nz | 1 | Vector definition of "forward" direction wrt. divergence, to be used e.g. when the monitor is rotated into the horizontal plane. | 1 |
| nowritefile | 1 | If set, monitor will skip writing to disk. | 0 |

## Links

- [Source code](/Users/peterwillendrup/Projects/willend-McCode/mcxtrace-comps/monitors/DivE_monitor.comp) for `DivE_monitor.comp`.

---

*Generated on mcxtrace 3.99.99.*