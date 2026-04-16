# The `PSD_monitor_coh` Component

*McXtrace: Position-sensitive monitor with phase integration.*

## Identification

- **Site:** 
- **Author:** Erik Knudsen
- **Origin:** Risoe
- **Date:** March 13, 2010

## Description

```text
An (n times m) pixel PSD monitor taking phase into account.
As the i:th ray hits a pixel (j,k) in the monitor the intensity in that
pixel will be updated as a complex sum, i.e. <math>P_i = P_{i-1} + p_i exp{-\phi_i}</math>.

By setting ratio<1 the effective pixel area becomes a
fraction of the ideal (which is to divide the xwidth and yheight intervals into nx and ny abutting
subintervals). This reduces the monitor effective area by ratio^2.
If the centering flag is set - the monitor will treat all rays as if they hit a pixel
center. This behaves as if ratio -> 0, but at no cost in statistics.

Example: PSD_monitor_coh(xwidth=0.1, yheight=0.1,
nx=90, ny=90, filename="Output.psd")
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| nx |  | Number of pixel columns. | 90 |
| ny |  | Number of pixel rows. | 90 |
| filename | m | Name of file in which to store the detector images - the suffixes .abs and .arg will be added. | 0 |
| restore_xray |  | If set, the monitor does not influence the xray state. | 0 |
| xwidth | m | Width of detector. | 0.05 |
| yheight | m | Height of detector. | 0.05 |
| ratio |  | ratio between pixel area and effective pixel area. | 1 |
| centering |  | Treat all rays as if they hit the center of the pixel. | 1 |
| nowritefile | 1 | If set, monitor will skip writing to disk | 0 |

## Links

- [Source code](/Users/peterwillendrup/Projects/willend-McCode/mcxtrace-comps/monitors/PSD_monitor_coh.comp) for `PSD_monitor_coh.comp`.

---

*Generated on mcxtrace 3.99.99.*