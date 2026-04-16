# The `PSD_monitor` Component

*McXtrace: Position-sensitive monitor.*

## Identification

- **Site:** 
- **Author:** Erik B Knudsen
- **Origin:** Risoe
- **Date:** June 22, 2009

## Description

```text
Based on neutron component written by Kim Lefmann
An (nx times ny) pixel PSD monitor. This component may also be used as a beam
detector. If instead of xwidth, yheight a radius is given, the component has a circular footprint
and integrates circularly (caking).

Example: PSD_monitor(xwidth=0.1, yheight=0.1,
nx=90, ny=90, filename="Output.psd")
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| filename | str | Name of file in which to store the detector image. | 0 |
| xwidth | m | Width of detector. | 0.05 |
| yheight | m | Height of detector. | 0.05 |
| radius | m | Radius of circular detetor. | 0 |
| restore_xray | 1 | If set, the monitor does not influence the xray state. | 1 |
| nowritefile | 1 | If set, monitor will skip writing to disk | 0 |
| nx | 1 | Number of pixel columns. | 90 |
| ny | 1 | Number of pixel rows. | 90 |
| nr | 1 | Number of radial pixels. | 0 |

## Links

- [Source code](/Users/peterwillendrup/Projects/willend-McCode/mcxtrace-comps/monitors/PSD_monitor.comp) for `PSD_monitor.comp`.

---

*Generated on mcxtrace 3.99.99.*