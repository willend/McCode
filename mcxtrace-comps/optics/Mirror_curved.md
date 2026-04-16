# The `Mirror_curved` Component

*McXtrace: A cylindrically curved mirror (in YZ)*

## Identification

- **Site:** 
- **Author:** Erik Knudsen
- **Origin:** Risoe
- **Date:** September 25th, 2009

## Description

```text
mirror is in the YZ-plane curved towards positive X if radius is positive

Example: Mirror_curved( radius=2, length=20e-3, width=40e-3, coating="AlMgF2_disco.dat")
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| radius | m | Radius of curvature, along Z. | 1 |
| R0 | 1 | Constant reflectivity value (mostly relevant for debugging, when coating=""). | 1 |
| coating | str | Name of file containing the material data (i.e. f1 and f2) for the coating | "Be.txt" |
| zdepth | m | Length of the unbent mirror along Z. | 0.2 |
| yheight | m | Width of the mirror along Y. | 0.2 |
| length | m | Length of the unbent mirror along Z = zdepth | 0 |
| width | m | Width of the mirror along Y = yheight | 0 |

## Links

- [Source code](/Users/peterwillendrup/Projects/willend-McCode/mcxtrace-comps/optics/Mirror_curved.comp) for `Mirror_curved.comp`.

---

*Generated on mcxtrace 3.99.99.*