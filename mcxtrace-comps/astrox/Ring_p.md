# The `Ring_p` Component

*McXtrace: Date: Feb. 2017
Version: 1.1
Release: McXtrace 1.2
Origin: DTU Physics, DTU Space

Stack of conical shells as part of a Wolter optic. Parabolic version.*

## Identification

- **Site:** 
- **Author:** Erik B Knudsen and Desiree D. M. Ferreira
- **Origin:** DTU Physics, DTU Space
- **Date:** Feb. 2016

## Description

```text
A stack of conical shells is simulated. Parabolic version.
To intersect the Wolter I plates we take advatage of the azimuthal symmetry and only consider the radial component
of the photon's wavevector.

Example: Ring_p( pore_th=0, ring_nr=3, Z0=FL, yheight=0.605e-3, mirror_reflec="mirror_coating_unity.txt", R_d=0, size_file="ref_design_breaks.txt")
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| **ring_nr** |  |  |  |
| **pore_th** |  |  |  |
| **Z0** | m | Distance between optics centre plane and focal spot (essentially focal length). |  |
| **yheight** | m | Height of the pore. |  |
| chamferwidth | m | Width of side walls. | 0 |
| gap | m | Gap between the plate and the intersection plane with the hyperbolic section. | 0 |
| zdepth |  |  | 0 |
| mirror_reflec |  | Data file containing reflectivities of the reflector surface (TOP). | "" |
| bottom_reflec |  | Data file containing reflectivities of the bottom surface (BOTTOM). | "" |
| size_file |  |  | "" |
| R_d |  | Default reflectivity value to use if no reflectivity file is given. Useful f.i. is one surface is reflecting and the others absorbing. | 1 |
| waviness | rad | Waviness of the pore reflecting surface. The slope error is assumed to be uniformly distributed in the interval [-waviness:waviness]. | 0 |
| longw |  | If non-zero, waviness is 1D and along the pore axis. | 0 |

## Links

- [Source code](/Users/peterwillendrup/Projects/willend-McCode/mcxtrace-comps/astrox/Ring_p.comp) for `Ring_p.comp`.

---

*Generated on mcxtrace 3.99.99.*