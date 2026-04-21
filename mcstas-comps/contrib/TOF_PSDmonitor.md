# The `TOF_PSDmonitor` Component

*McStas: Position-sensitive TOF vs. (height) linear monitor.*

## Identification

- **Site:** 
- **Author:** Robert Dalgliesh
- **Origin:** ISIS
- **Date:** September 2021

## Description

```text
Adapted from Kim Lefmann's TOF_cylPSDmonitor and PSD_monitors
An n pixel (vertical, linear) PSD monitor with Time of Flight detection.
This component may also be used as a beam
detector.

Example: TOF_PSDmonitor(xmin=-0.1, xmax=0.1, ymin=-0.1, ymax=0.1,
ny=90, nchan=100, TOFmin=0.0, TOFmax=20000.0, filename="Output.psd")
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| ny | 1 | Number of pixel rows | 90 |
| nchan | 1 | Number of TOF channels | 100 |
| xwidth | m | width of detector opening | 0.1 |
| xmin | m | Lower x bound of detector opening | 0 |
| xmax | m | Upper x bound of detector opening | 0 |
| yheight | m | height of detector opening | 0.1 |
| ymin | m | Lower y bound of detector opening | 0 |
| ymax | m | Upper y bound of detector opening | 0 |
| TOFmin | mu-s | Beginning TOF window | 0 |
| TOFmax | mu-s | End TO window | 1e6 |
| nowritefile | 1 | If set, detector will skip writing to disk | 0 |
| filename | str | Name of file in which to store the detector image | 0 |

## Links

- [Source code](TOF_PSDmonitor.comp) for `TOF_PSDmonitor.comp`.

---

*Generated on mcstas 3.99.99.*