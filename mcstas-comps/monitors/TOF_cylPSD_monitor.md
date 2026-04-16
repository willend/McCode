# The `TOF_cylPSD_monitor` Component

*McStas: Cylindrical (2pi) PSD Time-of-flight monitor.*

## Identification

- **Site:** 
- **Author:** Kim Lefmann
- **Origin:** Risoe
- **Date:** October 2000

## Description

```text

```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| nt | 1 | Number of time bins | 128 |
| nphi | deg | Number of angular bins | 90 |
| filename | string | Name of file in which to store the detector image | 0 |
| nowritefile | 1 | If set, monitor will skip writing to disk | 0 |
| radius | m | Cylinder radius | 1 |
| yheight | m | Cylinder height | 0.3 |
| **tmin** | mu-s | Beginning of time window |  |
| **tmax** | mu-s | End of time window |  |
| restore_neutron | 1 | If set, the monitor does not influence the neutron state | 0 |

## Links

- [Source code](/Users/peterwillendrup/Projects/willend-McCode/mcstas-comps/monitors/TOF_cylPSD_monitor.comp) for `TOF_cylPSD_monitor.comp`.

---

*Generated on mcstas 3.99.99.*