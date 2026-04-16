# The `Focus` Component

*McXtrace: Release: McXtrace 1.1

Turn a photon into a Huygens wavelet. To be used with the SPLIT keyword.*

## Identification

- **Site:** 
- **Author:** Carsten Detlefs, hacked from slit.comp
- **Origin:** ESRF
- **Date:** November 6, 2013

## Description

```text
Changes direction of the photon to a random direction
towards the specified target area.
To be used in coherent simulations, preferably with
the SPLIT keyword.
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| dist | m | distance to target | 0.0 |
| focus_xw | m | x-width of target | 0.0 |
| focus_yh | m | y-height of target | 0.0 |
| focus_x0 | m | x-center of target | 0.0 |
| focus_y0 | m | y-center of target | 0.0 |
| focus_absolute |  | Flag - if non-zero, focus_x0 and focus_y0 are in absolute (lab) coordinates. | 1 |

## Links

- [Source code](/Users/peterwillendrup/Projects/willend-McCode/mcxtrace-comps/misc/Focus.comp) for `Focus.comp`.

---

*Generated on mcxtrace 3.99.99.*