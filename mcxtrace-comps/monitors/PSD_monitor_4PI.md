# The `PSD_monitor_4PI` Component

*McXtrace: Release: McXtrace 0.1

Spherical position-sensitive detector.*

## Identification

- **Site:** 
- **Author:** Erik Knudsen
- **Origin:** Risoe
- **Date:** June 23rd, 2009

## Description

```text
Based on neutron component by Kim Lefmann and Kristian Nielsen
An (n times m) pixel spherical PSD monitor using a cylindrical projection.
Mostly for test and debugging purposes.

Example: PSD_monitor_4PI(radius=0.1,
nx=90, ny=90, filename="Output.psd")
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| radius | m | Radius of detector | 1 |
| restore_xray | 1 | If set, the monitor does not influence the xray state | 0 |
| nx | 1 | Number of pixel columns | 90 |
| ny | 1 | Number of pixel rows | 90 |
| filename | str | Name of file in which to store the detector image | 0 |

## Links

- [Source code](/Users/peterwillendrup/Projects/willend-McCode/mcxtrace-comps/monitors/PSD_monitor_4PI.comp) for `PSD_monitor_4PI.comp`.

---

*Generated on mcxtrace 3.99.99.*