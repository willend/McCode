# The `Mirror_toroid_pothole` Component

*McXtrace: Toroidal shape mirror (in XZ)*

## Identification

- **Site:** 
- **Author:** Erik B Knudsen
- **Origin:** DTU Physics
- **Date:** Jul 2016

## Description

```text
This is an implementation of a toroidal mirror which may be curved in two dimensions.
To avoid solving quartic equations, the intersection is computed as a combination of
two intersections. First, the ray is intersected with a cylinder to catch (almost) the small
radius curvature. Secondly, the ray is the intersected with an ellipsoid, with the curvatures
matching that of the torus.

The first incarnation (Mirror_toroid.comp) the mirror curves outwards (a bump), but this incarnation (Mirror_toroid_pothole) curves inwards (a pothole).

Example: Mirror_toroid_pothole( radius=0.1, radius_o=1000, xwidth=5e-2, zdepth=2e-1,R0=1, coating="")
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| zdepth | m | Length of mirror. | 0.1 |
| xwidth | m | Width of mirror. | 0.01 |
| **radius** | m | Curvature radius |  |
| **radius_o** | m | Curvature radius, outwards |  |
| R0 | 1 | Reflectivity of mirror. | 0 |
| coating | str | Datafile containing either mirror material constants or reflectivity  numbers. | "" |

## Links

- [Source code](/Users/peterwillendrup/Projects/willend-McCode/mcxtrace-comps/contrib/Mirror_toroid_pothole.comp) for `Mirror_toroid_pothole.comp`.

---

*Generated on mcxtrace 3.99.99.*