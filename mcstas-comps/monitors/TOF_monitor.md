# The `TOF_monitor` Component

*McStas: Rectangular Time-of-flight monitor.*

## Identification

- **Site:** 
- **Author:** KN, M. Hagen
- **Origin:** Risoe
- **Date:** August 1998

## Description

```text

```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| nt | 1 | Number of time bins | 20 |
| filename | string | Name of file in which to store the detector image | 0 |
| xmin | m | Lower x bound of detector opening | -0.05 |
| xmax | m | Upper x bound of detector opening | 0.05 |
| ymin | m | Lower y bound of detector opening | -0.05 |
| ymax | m | Upper y bound of detector opening | 0.05 |
| xwidth | m | Width of detector. Overrides xmin, xmax | 0 |
| yheight | m | Height of detector. Overrides ymin, ymax | 0 |
| tmin | mu-s | Lower time limit | 0 |
| tmax | mu-s | Upper time limit | 0 |
| dt | mu-s | Length of each time bin | 1.0 |
| restore_neutron | 1 | If set, the monitor does not influence the neutron state | 0 |
| nowritefile | 1 | If set, monitor will skip writing to disk | 0 |

## Links

- [Source code](TOF_monitor.comp) for `TOF_monitor.comp`.

---

*Generated on mcstas 3.99.99.*