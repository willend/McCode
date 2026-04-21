# The `NPI_tof_theta_monitor` Component

*McStas: Release: McStas 1.6

Cylindrical (2pi) PSD Time-of-flight monitor.*

## Identification

- **Site:** 
- **Author:** Kim Lefmann
- **Origin:** Risoe
- **Date:** October 2000

## Description

```text
Derived from TOF_cylPSD_monitor.
Code is extended by the option allowing to define range of scattering angles, therefore creating only a part of the cylinder surface.
The plot is transposed when compared to TOF_cylPSD_monitor: scattering angles are on the horizontal axis.


Example:	TOF_cylPSD_monitor_NPI(nt = 1024, nphi = 960, filename = "Output.dat",
radius = 2, yheight = 1.0, tmin = 3e4, tmax = 12e4, amin = 75, amax = 105, restore_neutron = 1)
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| filename | str | Name of file in which to store the detector image | 0 |
| radius | m | Cylinder radius | 1 |
| yheight | m | Cylinder height | 0.3 |
| **tmin** | mu-s | Beginning of time window |  |
| **tmax** | mu-s | End of time window |  |
| **amin** | deg | minimum angle to detect |  |
| **amax** | deg | maximum angle to detect |  |
| restore_neutron | 1 | If set, the monitor does not influence the neutron state | 1 |
| verbose |  |  | 0 |
| nt | 1 | Number of time bins | 128 |
| na |  |  | 90 |

## Links

- [Source code](NPI_tof_theta_monitor.comp) for `NPI_tof_theta_monitor.comp`.

---

*Generated on mcstas 3.99.99.*