# The `PolLambda_monitor` Component

*McStas: Polarisation and wavelength sensitive monitor.*

## Identification

- **Site:** 
- **Author:** Peter Christiansen
- **Origin:** Risoe
- **Date:** July 2006

## Description

```text
A square single monitor that measures the projection of the
polarisation along a given normalized m-vector (mx, my, mz) as a
function of wavelength.

Example: Pollambda_monitor(Lmin=1, Lmax=20, nL=20, xwidth=0.1, yheight=0.1, npol=11, mx=0, my=1, mz=0, filename="pollambdaMon.data")
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| xwidth | m | Width of detector | 0.1 |
| yheight | m | Height of detector | 0.1 |
| nL | 1 | Number of bins in wavelength | 20 |
| npol | 1 | Number of bins in Pol | 21 |
| restore_neutron | 1 | If set, the monitor does not influence the neutron state | 0 |
| filename | string | Name of file in which to store the data | 0 |
| nowritefile | 1 | If set, monitor will skip writing to disk | 0 |
| mx | 1 | X-component of monitor vector (can be negative) | 0 |
| my | 1 | Y-component of monitor vector (can be negative) | 0 |
| mz | 1 | Z-component of monitor vector (can be negative) | 0 |
| **Lmin** | AA | Minimum wavelength detected |  |
| **Lmax** | AA | Maximum wavelength detected |  |

## Links

- [Source code](/Users/peterwillendrup/Projects/willend-McCode/mcstas-comps/monitors/PolLambda_monitor.comp) for `PolLambda_monitor.comp`.

---

*Generated on mcstas 3.99.99.*