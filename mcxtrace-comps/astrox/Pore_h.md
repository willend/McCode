# The `Pore_h` Component

*McXtrace: Single Pore as part of the Silicon Pore Optics (SPO) as envisioned for the ATHENA+ space telescope.*

## Identification

- **Site:** 
- **Author:** Erik B Knudsen and Desiree D. M. Ferreira
- **Origin:** DTU Physics, DTU Space
- **Date:** Feb. 2016

## Description

```text
A single pore is simulated, which may have thick walls. The top and bottom are curved cylindrically
azimuthally, and according to the Wolter I optic lengthwise (sagitally). This is the hyperbolic part.
The azimuthal curvature is defined by the radius parameters. This refers to the center of the pore. I.e the top
and bottom plates have radius of curvature <radius+yheight/2> and <radius-yheight/2> respectively.

To intersect the Wolter I plates we take advatage of the azimuthal symmetry and only consider the radial component
of the photon's wavevector.

Example: Pore_h( radius_m=0.286148, radius_h=0.284333, zdepth=0.101504, Z0=12, xwidth=0.83e-3, yheight=0.605e-3, mirror_reflec="mirror_coating_unity.txt", R_d=0)
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| **radius_m** | m | Ring radius of the upper (reflecting) plate of the pore at the intersection with the parabolic section. |  |
| **radius_h** | m | Ring radius of the upper (reflecting) plate of the pore at the edge closest to the focal point. |  |
| **Z0** | m | distance between intersection plane and the focal spot( essentially the focal length). |  |
| **xwidth** | m | Width of the pore. |  |
| **yheight** | m | Height of the pore. (Thus the inner radius is radius_{m,h}-yehight. |  |
| chamferwidth | m | Width of side walls. | 0 |
| gap | m | gap between intersection with parabolic section and actual plate. | 0 |
| zdepth |  |  | 0 |
| mirror_reflec |  | Data file containing reflectivities of the reflector surface (TOP). | "" |
| bottom_reflec |  | Data file containing reflectivities of the bottom surface (BOTTOM). | "" |
| side_reflec |  | Data file containing reflectivities of the side walls (LEFT and RIGHT). | "" |
| R_d |  | Default reflectivity value to use if no reflectivity file is given. Useful f.i. is one surface is reflecting and the others absorbing. | 1 |
| waviness |  |  | 0 |
| longw |  |  | 0 |

## Links

- [Source code](/Users/peterwillendrup/Projects/willend-McCode/mcxtrace-comps/astrox/Pore_h.comp) for `Pore_h.comp`.

---

*Generated on mcxtrace 3.99.99.*