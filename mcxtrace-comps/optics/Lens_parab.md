# The `Lens_parab` Component

*McXtrace: X-ray compound refractive lens (CRL) with a profile of the parabola*

## Identification

- **Site:** 
- **Author:** Jana Baltser and Erik Knudsen
- **Origin:** NBI
- **Date:** August 2010, modified July 2011

## Description

```text
A simple X-ray compound refractive lens (CRL) with a profile of the parabola in rotation simulates the photons' movement on passing through it. The CRL focuses in 2D

Example: Lens_parab(material_datafile = "Be.txt", r=200e-6, r_ap=0.5e-3, d=50e-6, N=16)
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| material_datafile | str | Datafile containing f1 constants | "Be.txt" |
| r | m | Radius of curvature (circular approximation at the tip of the profile). | 0.5e-3 |
| r_ap | m | Radius of circular aperture, which also defines the depth of the lens profile. | 1.4e-3 |
| d | m | Distance between two surfaces of the lens along the propagation axis. | .1e-3 |
| N | m | Number of single lenses in a stack. | 1 |
| rough_z | rad | RMS value of random slope error along z. | 0 |
| rough_xy | rad | RMS value of random slope error along x and y. | 0 |

## Links

- [Source code](/Users/peterwillendrup/Projects/willend-McCode/mcxtrace-comps/optics/Lens_parab.comp) for `Lens_parab.comp`.

---

*Generated on mcxtrace 3.99.99.*