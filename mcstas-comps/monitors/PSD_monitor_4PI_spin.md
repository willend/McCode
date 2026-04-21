# The `PSD_monitor_4PI_spin` Component

*McStas: Spherical position-sensitive detector with spin weighting*

## Identification

- **Site:** 
- **Author:** Erik B Knudsen
- **Origin:** DTU
- **Date:** April 17, 2010

## Description

```text
An (n times m) pixel spherical PSD monitor using a cylindrical projection.
Mostly for test and debugging purposes.

Example: PSD_monitor_4PI(radius=0.1,
nx=90, ny=90, filename="Output.psd")
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| nx | 1 | Number of pixel columns | 90 |
| ny | 1 | Number of pixel rows | 90 |
| **radius** | m | Radius of detector |  |
| filename | str | Name of file in which to store the detector image | 0 |
| restore_neutron | 1 | If set, the monitor does not influence the neutron state x | 0 |
| mx | 1 | x-component of spin reference-vector | 0 |
| my | 1 | y-component of spin reference-vector | 1 |
| mz | 1 | z-component of spin reference-vector | 0 |

## Links

- [Source code](PSD_monitor_4PI_spin.comp) for `PSD_monitor_4PI_spin.comp`.

---

*Generated on mcstas 3.99.99.*