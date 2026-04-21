# The `PSD_spinUmon` Component

*McStas: Position-sensitive monitor, measuring the spin-up component of the neutron beam.*

## Identification

- **Site:** 
- **Author:** Michael Schneider (SNAG)
- **Origin:** SNAG
- **Date:** 2024

## Description

```text
An (n times m) pixel PSD monitor, measuring the spin-up component of the neutron beam.

Example: PSD_monitor(xmin=-0.1, xmax=0.1, ymin=-0.1, ymax=0.1, nx=90, ny=90, filename="Output.psd")
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| nx | 1 | Number of pixel columns | 90 |
| ny | 1 | Number of pixel rows | 90 |
| filename | string | Name of file in which to store the detector image | 0 |
| xmin | m | Lower x bound of detector opening | -0.05 |
| xmax | m | Upper x bound of detector opening | 0.05 |
| ymin | m | Lower y bound of detector opening | -0.05 |
| ymax | m | Upper y bound of detector opening | 0.05 |
| xwidth | m | Width of detector. Overrides xmin, xmax | 0 |
| yheight | m | Height of detector. Overrides ymin, ymax | 0 |
| restore_neutron | 1 | If set, the monitor does not influence the neutron state | 0 |
| nowritefile | 1 | If set, monitor will skip writing to disk | 0 |

## Links

- [Source code](PSD_spinUmon.comp) for `PSD_spinUmon.comp`.

---

*Generated on mcstas 3.99.99.*