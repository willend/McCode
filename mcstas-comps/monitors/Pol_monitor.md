# The `Pol_monitor` Component

*McStas: Polarisation sensitive monitor.*

## Identification

- **Site:** 
- **Author:** Peter Christiansen
- **Origin:** Risoe
- **Date:** July 2006

## Description

```text
A square single monitor that measures the projection of the
polarisation along a given normalized m-vector (mx, my, mz).
The measured quantity is: sx*mx+sy*my+mz*sz

Example: Pol_monitor(xwidth=0.1, yheight=0.1, nchan=11, mx=0, my=1, mz=0)
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| xwidth | m | Width of detector | 0.1 |
| yheight | m | Height of detector | 0.1 |
| restore_neutron | 1 | If set, the monitor does not influence the neutron state | 0 |
| mx | 1 | X-component of monitor vector (can be negative) | 0 |
| my | 1 | Y-component of monitor vector (can be negative) | 0 |
| mz | 1 | Z-component of monitor vector (can be negative) | 0 |
| nowritefile | 1 | If set, monitor will skip writing to disk | 0 |

## Links

- [Source code](Pol_monitor.comp) for `Pol_monitor.comp`.

---

*Generated on mcstas 3.99.99.*