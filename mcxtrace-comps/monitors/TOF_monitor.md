# The `TOF_monitor` Component

*McXtrace: Release: 1.2

Rectangular Time-of-flight monitor.*

## Identification

- **Site:** 
- **Author:** Erik B Knudsen
- **Origin:** British Airways
- **Date:** Aug. 2014

## Description

```text
Rectangular Time-of-flight monitor. You may either give the time-step or the
time range.
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| nt | 1 | Number of time bins | 20 |
| filename | str | Name of file in which to store the detector image | 0 |
| xwidth | m | Width of detector. | 0.1 |
| yheight | m | Height of detector. | 0.1 |
| tmin | mu-s | Lower time limit | 0 |
| tmax | mu-s | Upper time limit. When left as 0, use dt to compute tmax. | 0 |
| dt | mu-s | Length of each time bin | 1.0 |
| restore_xray | 1 | If set, the monitor does not influence the xray state | 0 |

## Links

- [Source code](/Users/peterwillendrup/Projects/willend-McCode/mcxtrace-comps/monitors/TOF_monitor.comp) for `TOF_monitor.comp`.

---

*Generated on mcxtrace 3.99.99.*