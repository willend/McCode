# The `TOF2Q_cyl_monitor` Component

*McStas: Release: McStas 2.0

Cylindrical (2pi) 2theta v. q Time-of-flight monitor.*

## Identification

- **Site:** 
- **Author:** Kim Lefmann
- **Origin:** Risoe
- **Date:** October 2000

## Description

```text
Cylindrical (2pi) 2theta v. q Time-of-flight monitor.
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| nq | 1 | Number of q bins | 100 |
| nphi | 1 | Number of angular bins | 100 |
| nh | 1 | Number of bins in detector height | 10 |
| restore_neutron | 1 | If set, the monitor does not influence the neutron state | 0 |
| filename | str | Name of file in which to store the detector image | 0 |
| radius | m | Cylinder radius | 1.0 |
| height | m | Cylinder height | 0.1 |
| q_min | 1/AA | Minimum q value | 0 |
| q_max | 1/AA | Maximum q value | 20 |
| L_chop2samp | m | Distance from resolution chopper to sample position | 144.0 |
| t_chop | ms | Flight time of mean wave length from source to resolution chopper | 0.004 |
| pixel | 1 | Flag, 0: no pixelation and perfect time. 1: make pixels from nphi and nh and time resolution limitation. | 1 |

## Links

- [Source code](/Users/peterwillendrup/Projects/willend-McCode/mcstas-comps/contrib/TOF2Q_cyl_monitor.comp) for `TOF2Q_cyl_monitor.comp`.

---

*Generated on mcstas 3.99.99.*