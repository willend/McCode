# The `Lens_parab_rough` Component

*McXtrace: Lens_parab_rough component*

## Identification

- **Site:** 
- **Author:** Jana Baltser and Erik Knudsen
- **Origin:** 
- **Date:** August 2010, modified July 2011

## Description

```text
A simple X-ray compound refractive lens (CRL) with a profile of the parabola in
rotation simulates the photons' movement on passing through it. The CRL focuses in 2D.
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| material_datafile | Be.txt | File where the material parameters for the filter may be found. Format is similar to what may be found off the NIST website. | "Be.txt" |
| r | m | radius of curvature (circular approximation at the tip of the profile) | 0.5e-3 |
| yheight | m | the CRL's dimensions along Y, aka aperture | 1.4e-3 |
| xwidth | m | the CRL's dimensions along X | 1.4e-3 |
| d | m | distance between two surfaces of the lens along the propagation axis; | .1e-3 |
| T | 1 | transmission of the lens | .99 |
| N | 1 | amount of single lenses in a stack. | 1 |
| rough_z | rms | waviness along z | 0 |
| rough_xy | rms | waviness along x and y | 0 |

## Links

- [Source code](/Users/peterwillendrup/Projects/willend-McCode/mcxtrace-comps/obsolete/Lens_parab_rough.comp) for `Lens_parab_rough.comp`.
- material datafile obtained from http://physics.nist.gov/cgi-bin/ffast/ffast.pl

---

*Generated on mcxtrace 3.99.99.*