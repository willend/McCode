# The `MM_p` Component

*McXtrace: Date: Feb. 2017
Version: 1.1
Release: McXtrace 1.2
Origin: DTU Physics, DTU Space

Single Pore as part of the Silicon Pore Optics (SPO) as envisioned for the ATHENA+ space telescope.*

## Identification

- **Site:** 
- **Author:** Erik B Knudsen and Desiree D. M. Ferreira
- **Origin:** DTU Physics, DTU Space
- **Date:** Feb. 2016

## Description

```text
A single pore is simulated, which may have thick walls. The top and bottom are curved cylindrically
azimuthally, and according to the Wolter I optic lengthwise (sagitally). A parameter specifies
whether this is hyperbolic or parabolic.
The azimuthal curvature is defined by the parameter radius. This refers to the center of the pore. I.e the top
and bottom plates have radius of curvature <radius+pore_height/2> and <radius-pore_height/2> respectively.

To intersect the Wolter I plates we take advatage of the azimuthal symmetry and only consider the radial component
of the photon's wavevector.

Example: MM_p( pore_th=0, ring_nr=1, Z0=12, pore_width=0.83e-3 , pore_height=0.605e-3, mirror_reflec="mirror_coating_unity.txt", R_d=0, size_file="ref_design_breaks.txt")
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| **pore_th** |  |  |  |
| **ring_nr** |  |  |  |
| **Z0** | m | Distance between optics centre plane and focal spot (essentially focal length). |  |
| **pore_height** | m | Height of the pore. |  |
| **pore_width** |  |  |  |
| chamfer_width | m | Width of side walls. | 0 |
| gap | m | Gap between the plate and the intersection plane with the hyperbolic section. | 0 |
| zdepth |  |  | 0 |
| mirror_reflec |  | Data file containing reflectivities of the reflector surface (TOP). | "" |
| bottom_reflec |  | Data file containing reflectivities of the bottom surface (BOTTOM). | "" |
| side_reflec |  | Data file containing reflectivities of the side walls (LEFT and RIGHT). | "" |
| size_file |  |  | "" |
| non_specular_file |  |  | "" |
| R_d |  | Default reflectivity value to use if no reflectivity file is given. Useful f.i. is one surface is reflecting and the others absorbing. | 1 |
| waviness |  |  | 0 |
| longw |  |  | 0 |

## Links

- [Source code](/Users/peterwillendrup/Projects/willend-McCode/mcxtrace-comps/astrox/MM_p.comp) for `MM_p.comp`.

---

*Generated on mcxtrace 3.99.99.*