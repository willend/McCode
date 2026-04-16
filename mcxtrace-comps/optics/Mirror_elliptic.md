# The `Mirror_elliptic` Component

*McXtrace: Idealized elliptic mirror.*

## Identification

- **Site:** 
- **Author:** Erik Knudsen
- **Origin:** Risoe
- **Date:** Feb 11, 2010

## Description

```text
Takes a reflectivity as input and reflects rays in a ideal geometry
elliptic mirror.
The mirror is positioned such that the a-axis of the mirror ellipsoid is on the
x-axis, the b-axis is along the y-axis and the c is along the z-axis.
The reference point of the mirror is the ellipsoid centre, offset by one
half-axis along the y-axis (See the component manual for a drawing).
This means that to position the mirror correctly,
the user positions the ellipsoid governing the mirror shape, not the mirror itself.

Example: Mirror_elliptic( length=150e-3, width=150e-3, x_a=1.025, y_b=1.025, z_c=1.025)
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| x_a | m | 1st short half axis (along x). Commonly set to zero, which really implies infinite value, so crystal is an elliptic cylinder. | 0 |
| y_b | m | 2nd short half axis (along y), which is also the presumed near-normal direction, reflection near the y-z plane. | 1.0 |
| z_c | m | long  half axis (along z). Commonly a=0. b=c, which creates a circular cylindrical surface. | 1.0 |
| zdepth | m | Depth (length) of the mirror along Z. | 0.2 |
| xwidth | m | Width of the mirror along X. | 0.2 |
| R0 | 1 | Reflectivity of mirror (mostly relevant for debugging, when coating="") | 1 |
| coating | str | Datafile containing either mirror material constants or reflectivity  numbers. | "Be.txt" |
| length | m | alternate name for zdepth (obsolete) | 0 |
| width | m | alternate name for xwidth (obsolete) | 0 |
| radius | m | Spherical radius, Sets x_a=y_b=z_c=radius | 0 |

## Links

- [Source code](/Users/peterwillendrup/Projects/willend-McCode/mcxtrace-comps/optics/Mirror_elliptic.comp) for `Mirror_elliptic.comp`.

---

*Generated on mcxtrace 3.99.99.*