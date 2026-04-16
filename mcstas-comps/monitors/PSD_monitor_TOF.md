# The `PSD_monitor_TOF` Component

*McStas: Position-sensitive monitor with a TOF signal pr. bin.*

## Identification

- **Site:** 
- **Author:** Peter Willendrup, derived from PSD_monitor by Kim Lefmann
- **Origin:** Risoe
- **Date:** Feb 3, 1998

## Description

```text
An (nx times ny) pixel PSD monitor with nt time bins pr pixel.

Will output 1 integrated PSD images plus an nt time bin TOF signal pr pixel.

Example: PSD_monitor_TOF(xmin=-0.1, xmax=0.1, ymin=-0.1, ymax=0.1, nx=90, ny=90, tmin=4000, tmax=7000, nt=1000, filename="Output")
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| nx | 1 | Number of pixel columns | 90 |
| ny | 1 | Number of pixel rows | 90 |
| nt | 1 | Number of TOF bins | 10 |
| restore_neutron | 1 | If set, the monitor does not influence the neutron state | 0 |
| filename | string | Name of file in which to store the detector image | 0 |
| nowritefile | 1 | If set, monitor will skip writing to disk | 0 |
| xmin | m | Lower x bound of detector opening | 0 |
| xmax | m | Upper x bound of detector opening | 0 |
| ymin | m | Lower y bound of detector opening | 0 |
| ymax | m | Upper y bound of detector opening | 0 |
| xwidth | m | Width/diameter of detector (x). Overrides xmin, xmax | 0 |
| yheight | m | Height of detector (y). Overrides ymin, ymax | 0 |
| tmin | mu-s | Lower time bound | 0 |
| tmax | mu-s | Upper time bound | 0 |

## Links

- [Source code](/Users/peterwillendrup/Projects/willend-McCode/mcstas-comps/monitors/PSD_monitor_TOF.comp) for `PSD_monitor_TOF.comp`.

---

*Generated on mcstas 3.99.99.*