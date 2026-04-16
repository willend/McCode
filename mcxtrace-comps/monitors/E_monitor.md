# The `E_monitor` Component

*McXtrace: Release: McXtrace 0.1

Energy-sensitive monitor.*

## Identification

- **Site:** 
- **Author:** Erik Knudsen
- **Origin:** Risoe
- **Date:** June 22, 2009

## Description

```text
A square single monitor that measures the energy of the incoming x-rays.

Example: E_monitor(xwidth=0.1, yheight=0.1,
Emin=1, Emax=50, nE=20, filename="Output.nrj")
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| nE | m | Number of energy channels. | 20 |
| filename | str | Name of file in which to store the detector image. | 0 |
| xwidth | m | Width of detector. | 0.1 |
| yheight | m | Height of detector. | 0.1 |
| **Emin** | keV | Minimum energy to detect. |  |
| **Emax** | keV | Maximum energy to detect. |  |
| restore_xray | 0/1 | If set, the monitor does not influence the x-ray state. | 0 |

## Links

- [Source code](/Users/peterwillendrup/Projects/willend-McCode/mcxtrace-comps/monitors/E_monitor.comp) for `E_monitor.comp`.

---

*Generated on mcxtrace 3.99.99.*