# The `Lens_parab_Cyl_rough` Component

*McXtrace: Lens_parab_Cyl_rough component*

## Identification

- **Site:** 
- **Author:** Jana Baltser and Erik Knudsen
- **Origin:** 
- **Date:** April 2011

## Description

```text
A simple X-ray compound refractive lens (CRL) with a parabolic cylinder profile,
it focuses in 1D.
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| material_datafile |  |  | "Be.txt" |
| r | m | radius of curvature (circular approximation at the tip of the profile) | .5e-3 |
| yheight | m | the CRL's dimensions along Y, aka aperture | 1.2e-3 |
| xwidth |  |  | 1.2e-3 |
| d |  |  | .1e-3 |
| T |  |  | .99 |
| N |  |  | 1 |
| rough_z |  |  | 0 |
| rough_xy |  |  | 0 |

## Links

- [Source code](/Users/peterwillendrup/Projects/willend-McCode/mcxtrace-comps/obsolete/Lens_parab_Cyl_rough.comp) for `Lens_parab_Cyl_rough.comp`.

---

*Generated on mcxtrace 3.99.99.*