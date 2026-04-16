# The `PSD_monitor_psf` Component

*McStas: Position-sensitive monitor.*

## Identification

- **Site:** 
- **Author:** Kim Lefmann, Linda Udby
- **Origin:** Risoe
- **Date:** Feb 3, 1998

## Description

```text
An (n times m) pixel PSD monitor. This component may also be used as a beam
detector.

Example: PSD_monitor(xmin=-0.1, xmax=0.1, ymin=-0.1, ymax=0.1, nx=90, ny=90, filename="Output.psd")
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| nx | 1 | Number of pixel columns | 90 |
| ny | 1 | Number of pixel rows | 90 |
| restore_neutron | 1 | If set, the monitor does not influence the neutron state | 0 |
| filename | string | Name of file in which to store the detector image | 0 |
| nowritefile | 1 | If set, monitor will skip writing to disk | 0 |
| xmin | m | Lower x bound of detector opening | 0 |
| xmax | m | Upper x bound of detector opening | 0 |
| ymin | m | Lower y bound of detector opening | 0 |
| ymax | m | Upper y bound of detector opening | 0 |
| xwidth | m | Width/diameter of detector (x). Overrides xmin, xmax | 0 |
| yheight | m | Height of detector (y). Overrides ymin, ymax | 0 |
| psf | m | Point spread function, ray (x,y) coordinate randomized by gaussion of sigma psf | 0 |

## Links

- [Source code](/Users/peterwillendrup/Projects/willend-McCode/mcstas-comps/monitors/PSD_monitor_psf.comp) for `PSD_monitor_psf.comp`.

---

*Generated on mcstas 3.99.99.*