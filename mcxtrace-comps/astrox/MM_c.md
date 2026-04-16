# The `MM_c` Component

*McXtrace: Single Pore as part of the Silicon Pore Optics (SPO) as envisioned for the ATHENA+ space telescope.*

## Identification

- **Site:** 
- **Author:** Erik B Knudsen and Desiree D. M. Ferreira
- **Origin:** DTU Physics, DTU Space
- **Date:** Feb. 2016, Feb. 2017

## Description

```text
A single pore is simulated, which may have thick walls. The top and bottom are curved cylindrically
azimuthally, and according to the Wolter I optic lengthwise (sagitally). A parameter specifies
whether this is hyperbolic or parabolic.
The azimuthal curvature is defined by the parameter radius. This refers to the center of the pore. I.e the top
and bottom plates have radius of curvature <radius+yheight/2> and <radius-yheight/2> respectively.

To intersect the Wolter I plates we take advatage of the azimuthal symmetry and only consider the radial component
of the photon's wavevector.
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| **pore_th** |  |  |  |
| **pore_width** |  |  |  |
| **ring_nr** |  |  |  |
| **radius_m** | m | Ring radius of the upper (reflecting) plate of the pore at the optic centre. |  |
| **Z0** | m | Distance between optics centre plane and focal spot (essentially focal length). |  |
| **xwidth** | m | Width of the pore. |  |
| **pore_height** |  |  |  |
| gap | m | Gap between the plate and the intersection plane with the hyperbolic section. (currently ignored) | 0 |
| chamfer_width |  |  | 0 |
| length |  |  | 0 |
| mirror_reflec |  | Data file containing reflectivities of the reflector surface (TOP). | "" |
| bottom_reflec |  | Data file containing reflectivities of the bottom surface (BOTTOM). | "" |
| side_reflec |  | Data file containing reflectivities of the side walls (LEFT and RIGHT). | "" |
| size_file |  |  | "" |
| non_specular_file |  |  | "" |
| R_d |  | Default reflectivity value to use if no reflectivity file is given. Useful f.i. is one surface is reflecting and the others absorbing. | 1 |
| primary |  | If non-zero, the pore is considered a primary reflector, and extends towards negative z. I.e. the entry plane is behind the z=0-plane. If zero, the pore is considered secondary and extends from the z=0-plane and towards positive z. | 1 |
| dalpha | deg | Offset to the alpha angle computed from the focal length. Useful for targeting the modified conical geometry (currently ignored). | 0 |
| waviness | rad | Waviness of the reflecting surface. The slope error is assumed to be uniformly distributed in the interval [-waviness:waviness]. | 0 |
| longw |  | If non-zero, waviness is 1D and along the pore axis. | 0 |

## Links

- [Source code](/Users/peterwillendrup/Projects/willend-McCode/mcxtrace-comps/astrox/MM_c.comp) for `MM_c.comp`.

---

*Generated on mcxtrace 3.99.99.*