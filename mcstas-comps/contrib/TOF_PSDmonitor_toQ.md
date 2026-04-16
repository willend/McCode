# The `TOF_PSDmonitor_toQ` Component

*McStas: Position-sensitive, linear Q monitor.*

## Identification

- **Site:** 
- **Author:** Robert Dalgliesh
- **Origin:** ISIS
- **Date:** September 2021

## Description

```text
One-dimensional Q-monitor. Calculates Q from "measured" time-of-flight,
i.e. not from particle velocity parameters.

Adapted from Kim Lefmann's TOF_cylPSDmonitor and PSD_monitors
An n pixel Q-monitor based on measured Time of Flight detection.
This component may also be used as a beam
detector.

Example: TOF_PSDmonitor_toQ(xmin=-0.1, xmax=0.1, ymin=-0.1, ymax=0.1,
ny=90, nqbin=100, TOFmin=0.0, TOFmax=20000.0, filename="Output.psd")
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| ny | 1 | Number of y bins (for discretisation of vertical detector dimension into "bins") | 90 |
| nqbin | 1 | number of q bins | 500 |
| xwidth | m | width of detector opening | 0.1 |
| xmin | m | Lower x bound of detector opening | 0 |
| xmax | m | Upper x bound of detector opening | 0 |
| yheight | m | height of detector opening | 0.1 |
| ymin | m | Lower y bound of detector opening | 0 |
| ymax | m | Upper y bound of detector opening | 0 |
| tmin | mu-s | Beginning TOF window | 0.0 |
| tmax | mu-s | End TO window | 100000.0 |
| qmin | AA^-1 | Start of q window | 0.005 |
| qmax | AA^-1 | End of q window | 0.5 |
| L1 | m | distance from source to sample (m) | 23.0 |
| L2 | m | distance from sample to detector (m) | 3.0 |
| detTheta | deg | Nominal detector theta | 0.91 |
| filename | str | Name of file in which to store the detector image | 0 |
| nowritefile | 1 | If set, detector will skip writing to disk | 0 |

## Links

- [Source code](/Users/peterwillendrup/Projects/willend-McCode/mcstas-comps/contrib/TOF_PSDmonitor_toQ.comp) for `TOF_PSDmonitor_toQ.comp`.

---

*Generated on mcstas 3.99.99.*