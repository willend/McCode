# The `TOF2Q_cylPSD_monitor` Component

*McStas: Cylindrical (2pi) Time-of-flight to Q monitor.
Calculates Q from TOF and known nominal grazing angle theta:
E = VS2E*(L_flight/(t-T_zero))*(L_flight/(t-T_zero));
Q=2*sqrt(E/2.072)*sin(theta);*

## Identification

- **Site:** 
- **Author:** Anette Vickery, derived from Lefmann TOF_cylPSD
- **Origin:** Risoe
- **Date:** October 2000

## Description

```text

```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| **nQ** | 1 | Number of Q bins |  |
| **ny** | 1 | Number of y bins |  |
| filename | string | Name of file in which to store the detector image | 0 |
| nowritefile | 1 | If set, monitor will skip writing to disk | 0 |
| **radius** | m | Cylinder radius |  |
| **yheight** | m | Cylinder height |  |
| **Qmin** | AA^-1 | Beginning of Q-range |  |
| **Qmax** | AA^-1 | End of Q-range |  |
| ymin | m | Minimum value of y monitored | 0 |
| ymax | m | Maximum value of y monitored | 0 |
| **T_zero** | s | Beginning of time window |  |
| **L_flight** | m | Nominal flightpath moderator--detector |  |
| restore_neutron | 1 | If set, the monitor does not influence the neutron state | 0 |
| **theta** | rad | Nominal grazing angle |  |

## Links

- [Source code](TOF2Q_cylPSD_monitor.comp) for `TOF2Q_cylPSD_monitor.comp`.

---

*Generated on mcstas 3.99.99.*