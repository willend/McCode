# The `Radial_div` Component

*McStas: A radial divergence sensitive monitor with wavelength restrictions.*

## Identification

- **Site:** 
- **Author:** Kaspar Hewitt Klen&oslash;, modified from Hdiv_monitor
- **Origin:** NBI
- **Date:** Jan 2011

## Description

```text
A radial divergence sensitive monitor with wavelength restrictions. The counts are distributed in
n pixels.

Example:
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| ndiv | 1 | Number of pixel rows | 20 |
| restore_neutron | 1 | If set, the monitor does not influence the neutron state | 0 |
| **filename** | str | Name of file in which to store the detector image |  |
| xmin | m | Lower x bound of detector opening | 0 |
| xmax | m | Upper x bound of detector opening | 0 |
| ymin | m | Lower y bound of detector opening | 0 |
| ymax | m | Upper y bound of detector opening | 0 |
| xwidth | m | Width/diameter of detector (x). Overrides xmin,xmax. | 0 |
| yheight | m | Height of detector (y). Overrides ymin,ymax. | 0 |
| maxdiv_r | deg | Maximal radial divergence detected | 2 |
| **Lmin** | AA | Minimum wavelength detected |  |
| **Lmax** | AA | Maximum wavelength detected |  |

## Links

- [Source code](Radial_div.comp) for `Radial_div.comp`.

---

*Generated on mcstas 3.99.99.*