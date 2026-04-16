# The `Mirror_parabolic` Component

*McXtrace: Idealized parabolic mirror (in XZ)*

## Identification

- **Site:** 
- **Author:** Erik Knudsen
- **Origin:** Risoe
- **Date:** Feb 11, 2010

## Description

```text
Takes a reflectivity as input and reflects rays in a ideal geometry
parabolic mirror. The mirror is positioned in the zx-plane curving towards positive y.
I.e. the focal point is (0,0,f(a,b))
The geometry of the paraboloid is governed by the equation: y = x^2 / a^2 + z^2 / b^2
Hence, the focal length for the 'x' curve is f=a^2 / 4, and analogous for z.

Example: Mirror_parabolic(R0=1, a=1, b=0, xwidth=0.02, yheight=0, zdepth=0.05)
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| R0 | 1 | Reflectivity of mirror. | 1 |
| a | sqrt(m) | Transverse curvature scale, if zero - the mirror is flat along x. | 1 |
| b | sqrt(m) | Longitudinal curvature scale, if zero, flat along z. | 1 |
| xwidth | m | Width of mirror. | 0.1 |
| zdepth | m | Length of mirror. | 0.1 |
| yheight | m | Thickness of mirror. If 0 (the default) the mirror is mathemticlly thin. Only has an effect for hitting the mirror from the side. | 0 |
| focusx | m | Transverse focal length along X. Sets a. | 0 |
| focusz | m | Longitudinal focal length along Z. Sets b. | 0 |
| radius | m | Focal length. Sets focusx and focusz. | 0 |

## Links

- [Source code](/Users/peterwillendrup/Projects/willend-McCode/mcxtrace-comps/optics/Mirror_parabolic.comp) for `Mirror_parabolic.comp`.

---

*Generated on mcxtrace 3.99.99.*