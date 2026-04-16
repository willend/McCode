# The `Mirror_toroid` Component

*McXtrace: Toroidal shape mirror (in XZ)*

## Identification

- **Site:** 
- **Author:** Erik B Knudsen
- **Origin:** DTU Physics
- **Date:** Jul 2016

## Description

```text
This is an implementation of a toroidal mirror which may be curved in two dimensions.
To avoid solving quartic equations, the intersection is compited as a combination of
two intersections. First, the ray is intersected with a cylinder to catch (almost) the small
radius curvature. Secondly, the ray is the intersected with an ellipsoid, with the curvatures
matching that of the torus.

In the first incarnation we assume the mirror to be curving outwards (a bump).

Example: Mirror_toroid(zdepth=0.340,xwidth=0.020,radius=246.9254,radius_o=246.9254,R0=1)
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| coating | str | Datafile containing either mirror material constants or reflectivity  numbers. | "" |
| zdepth | m | Length of mirror. | 0.1 |
| xwidth | m | Width of mirror. | 0.01 |
| **radius** | m | Curvature radius |  |
| **radius_o** | m | Curvature radius, outwards |  |
| R0 | 1 | Reflectivity of mirror. | 0 |

## Links

- [Source code](/Users/peterwillendrup/Projects/willend-McCode/mcxtrace-comps/optics/Mirror_toroid.comp) for `Mirror_toroid.comp`.

---

*Generated on mcxtrace 3.99.99.*