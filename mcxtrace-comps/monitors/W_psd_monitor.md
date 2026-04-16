# The `W_psd_monitor` Component

*McXtrace: Release: McXtrace 0.1

Position-sensitive wattage monitor.*

## Identification

- **Site:** 
- **Author:** Erik Knudsen
- **Origin:** Risoe
- **Date:** June 22, 2009

## Description

```text
Based on neutron PSD component written by Kim Lefmann
An n times m pixel PSD wattage monitor. This component may also be used as a beam
detector.

Example: W_psd_monitor(xwidth=0.1, yheight=0.1,
nx=90, ny=90, filename="Output.psd")
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| nx | 1 | Number of pixel columns | 90 |
| ny | 1 | Number of pixel rows | 90 |
| filename | str | Name of file in which to store the detector image | 0 |
| restore_xray | 1 | If set, the monitor does not influence the xray state | 0 |
| xwidth | m | Width of detector. | 0.1 |
| yheight | m | Height of detector. | 0.1 |

## Links

- [Source code](/Users/peterwillendrup/Projects/willend-McCode/mcxtrace-comps/monitors/W_psd_monitor.comp) for `W_psd_monitor.comp`.

---

*Generated on mcxtrace 3.99.99.*