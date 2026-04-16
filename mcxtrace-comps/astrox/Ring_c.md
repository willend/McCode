# The `Ring_c` Component

*McXtrace: Date: Feb. 2017
Version: 1.1
Release: McXtrace 1.2
Origin: DTU Physics, DTU Space

Stack of conical shells as part of a Wolter optic.*

## Identification

- **Site:** 
- **Author:** Erik B Knudsen and Desiree D. M. Ferreira
- **Origin:** DTU Physics, DTU Space
- **Date:** Feb. 2016

## Description

```text
A stack of conical shells is simulated.
To intersect the Wolter I plates we take advatage of the azimuthal symmetry and only consider the radial component
of the photon's wavevector.
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| **ring_nr** |  |  |  |
| **radius_m** | m | Ring radius of the upper (reflecting) plate of the shell at the optic centre. |  |
| **Z0** | m | Distance between optics centre plane and focal spot (essentially focal length). |  |
| **xwidth** |  |  |  |
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

- [Source code](/Users/peterwillendrup/Projects/willend-McCode/mcxtrace-comps/astrox/Ring_c.comp) for `Ring_c.comp`.

---

*Generated on mcxtrace 3.99.99.*