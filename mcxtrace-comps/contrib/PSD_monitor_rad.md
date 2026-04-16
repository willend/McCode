# The `PSD_monitor_rad` Component

*McXtrace: Position-sensitive monitor with radially averaging.*

## Identification

- **Site:** 
- **Author:** Henrich Frielinghaus
- **Origin:** FZ-Juelich/FRJ-2/IFF/KWS-2
- **Date:** Sept 2004

## Description

```text
Radial monitor that allows for radial averaging.
Comment: The intensity is given as two files:
1) a radial sum
2) a radial average (i.e. intensity per area)

Example: PSD_monitor_rad(rmax=0.2, nr=100, filename="Output.psd", filename_av="Output_av.psd")
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| nr | 1 | Number of concentric circles | 100 |
| filename | text | Name of file in which to store the detector image | 0 |
| filename_av | text | Name of file in which to store the averaged detector image | 0 |
| rmax | m | Outer radius of detector | 0.2 |

## Links

- [Source code](/Users/peterwillendrup/Projects/willend-McCode/mcxtrace-comps/contrib/PSD_monitor_rad.comp) for `PSD_monitor_rad.comp`.

---

*Generated on mcxtrace 3.99.99.*