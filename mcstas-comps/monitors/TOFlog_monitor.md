# The `TOFlog_monitor` Component

*McStas: Rectangular Time-of-flight monitor with logarithmic time binning.*

## Identification

- **Site:** 
- **Author:** Kim Lefmann
- **Origin:** Risoe
- **Date:** October 2000

## Description

```text
A rectangular time-of-flight monitor with logarithmic time binning.
(The neutron intensity is NOT given logarithmically)
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| **tmin** | mus | Lower bound for time bins |  |
| **tmax** | mus | Higher bound for time bins |  |
| ndec | 1 | Number of time bins per decade | 10 |
| nowritefile | 1 | If set, monitor will skip writing to disk | 0 |
| filename | string | Name of file in which to store the detector image | 0 |
| xmin | m | Lower x bound of detector opening | -0.05 |
| xmax | m | Upper x bound of detector opening | 0.05 |
| ymin | m | Lower y bound of detector opening | -0.05 |
| ymax | m | Upper y bound of detector opening | 0.05 |
| xwidth | m | Width of detector. Overrides xmin, xmax | 0 |
| yheight | m | Height of detector. Overrides ymin, ymax | 0 |
| restore_neutron | 1 | If set, the monitor does not influence the neutron state | 0 |

## Links

- [Source code](/Users/peterwillendrup/Projects/willend-McCode/mcstas-comps/monitors/TOFlog_monitor.comp) for `TOFlog_monitor.comp`.

---

*Generated on mcstas 3.99.99.*