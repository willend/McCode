# The `Bragg_crystal_simple` Component

*McXtrace: Perfect Bragg reflecting slab*

## Identification

- **Site:** 
- **Author:** Jose I. Robledo
- **Origin:** FaMAF - UNC, Argentina
- **Date:** February 2016

## Description

```text
Rectangle of matter perfectly reflecting the incident X-ray beam
that fulfills Bragg's law for a set of scattering vectors in the
vicinity of the theoretical Q given a d-spacing.
The rectangle is in the x-y plane.

Example: Bragg_crystal_simple( yheight=0.05, xwidth=0.02, DM=3.1356, err_Q= 0.000075, r0=1.0)
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| xmin |  |  | 1.0 |
| xmax |  |  | 1.0 |
| ymin |  |  | 1.0 |
| ymax |  |  | 1.0 |
| xwidth | m | Width in the x direction | 0.0 |
| yheight | m | Height in the y direction | 0.0 |
| r0 |  | Maximum reflectivity | 1 |
| DM |  | [AA⁻1]     d-spacing of the crystal | 0 |
| err_Q |  | dQ/Q relative error of the modulus of Q vector. Approximates the Darwin width of the crystal. | 0.0001 |

## Links

- [Source code](/Users/peterwillendrup/Projects/willend-McCode/mcxtrace-comps/contrib/Bragg_crystal_simple.comp) for `Bragg_crystal_simple.comp`.

---

*Generated on mcxtrace 3.99.99.*