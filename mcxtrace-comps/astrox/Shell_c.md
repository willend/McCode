# The `Shell_c` Component

*McXtrace: Single conical shell as part of a Wolter optic.*

## Identification

- **Site:** 
- **Author:** Erik B Knudsen and Desiree D. M. Ferreira
- **Origin:** DTU Physics, DTU Space
- **Date:** Feb. 2016

## Description

```text
A single shell is simulated. The top and bottom are curved cylindrically
azimuthally, whereas they are straight sagitally. The primary parameter specifies whether this is a
primary or secondary mirror.
The azimuthal curvature is defined by the parameter radius. This refers to the top plate of the shell. I.e the top
and bottom plates have radius of curvature <radius> and <radius-yheight> respectively.

To intersect the Wolter I plates we take advatage of the azimuthal symmetry and only consider the radial component
of the photon's wavevector.

Example: Shell_c( radius_m=0.535532,Z0=12,yheight=1e-2,length=0.5,primary=0, R_d=1)
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| **radius_m** | m | Ring radius of the upper (reflecting) plate of the shell at the optic centre. |  |
| **Z0** | m | Distance between optics centre plane and focal spot (essentially focal length). |  |
| **yheight** | m | Height of the shell. |  |
| gap | m | Gap between the plate and the intersection plane with the hyperbolic section. (currently ignored) | 0 |
| chamferwidth | m | Width of side walls. | 0 |
| length |  |  | 0 |
| mirror_reflec |  | Data file containing reflectivities of the reflector surface (TOP). | "" |
| bottom_reflec |  | Data file containing reflectivities of the bottom surface (BOTTOM). | "" |
| R_d |  | Default reflectivity value to use if no reflectivity file is given. Useful f.i. is one surface is reflecting and the others absorbing. | 1 |
| primary |  | If non-zero, the shell is considered a primary reflector, and extends towards negative z. I.e. the entry plane is behind the z=0-plane. If zero, the shell is considered secondary | 1 |
| dalpha | deg | Offset to the alpha angle computed from the focal length. Useful for targeting the modified conical geometry (currently ignored). | 0 |
| waviness | rad | Waviness of the shell reflecting surface. The slope error is assumed to be uniformly distributed in the interval [-waviness:waviness]. | 0 |
| longw |  | If non-zero, waviness is 1D and along the shell axis. | 0 |

## Links

- [Source code](/Users/peterwillendrup/Projects/willend-McCode/mcxtrace-comps/astrox/Shell_c.comp) for `Shell_c.comp`.

---

*Generated on mcxtrace 3.99.99.*