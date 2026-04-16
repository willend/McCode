# The `L_monitor` Component

*McXtrace: Release: McXtrace 0.1

Wavelength-sensitive monitor.*

## Identification

- **Site:** 
- **Author:** Kristian Nielsen and Kim Lefmann
- **Origin:** Risoe
- **Date:** June 22, 2009

## Description

```text
A square single monitor that measures the wavelength of the incoming
xray.

Example: L_monitor(xmin=-0.1, xwidth=0.1, yheight=0.1,
nL=20, filename="Output.L", Lmin=0.1, Lmax=1)
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| nL | m | Number of wavelength channels. | 20 |
| filename | str | Name of file in which to store the detector image. | 0 |
| xwidth | m | Width of detector. | 0.1 |
| yheight | m | Height of detector. | 0.1 |
| **Lmin** | AA | Minimum wavelength to detect. |  |
| **Lmax** | AA | Maximum wavelength to detect. |  |
| restore_xray |  | If set, the monitor does not influence the x-ray state. | 0 |

## Links

- [Source code](/Users/peterwillendrup/Projects/willend-McCode/mcxtrace-comps/monitors/L_monitor.comp) for `L_monitor.comp`.

---

*Generated on mcxtrace 3.99.99.*