# The `MeanPolLambda_monitor` Component

*McStas: Polarisation and wavelength sensitive monitor.*

## Identification

- **Site:** 
- **Author:** Peter Christiansen
- **Origin:** Risoe
- **Date:** July 2006

## Description

```text
A square single monitor that measures the MEAN projection of the
polarisation along a given normalized m-vector (mx, my, mz) as a
function of wavelength.

Example: MeanPollambda_monitor(xwidth=0.1, yheight=0.1, npol=11, my=1, filename="meanpollambdaMon.data")
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| xwidth | m | Width of detector | 0.1 |
| yheight | m | Height of detector | 0.1 |
| nL | 1 | Number of bins in wavelength | 20 |
| restore_neutron | 1 | If set, the monitor does not influence the neutron state | 0 |
| filename | string | Name of file in which to store the data | 0 |
| nowritefile | 1 | If set, monitor will skip writing to disk | 0 |
| mx | 1 | X-component of monitor vector (can be negative) | 0 |
| my | 1 | Y-component of monitor vector (can be negative) | 0 |
| mz | 1 | Z-component of monitor vector (can be negative) | 0 |
| **Lmin** | AA | Minimum wavelength detected |  |
| **Lmax** | AA | Maximum wavelength detected |  |

## Links

- [Source code](MeanPolLambda_monitor.comp) for `MeanPolLambda_monitor.comp`.

---

*Generated on mcstas 3.99.99.*