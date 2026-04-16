# The `SasView_triaxial_ellipsoid_aniso` Component

*McXtrace: SasView triaxial_ellipsoid model component as sample description.*

## Identification

- **Site:** 
- **Author:** Jose Robledo
- **Origin:** FZJ / DTU / ESS DMSC
- **Date:** 

## Description

```text
SasView_triaxial_ellipsoid component, generated from triaxial_ellipsoid.c in sasmodels.

Example:
SasView_triaxial_ellipsoid_aniso(sld, sld_solvent, radius_equat_minor, radius_equat_major, radius_polar, theta, Phi, Psi,
model_scale=1.0, model_abs=0.0, xwidth=0.01, yheight=0.01, zdepth=0.005, R=0,
int target_index=1, target_x=0, target_y=0, target_z=1,
focus_xw=0.5, focus_yh=0.5, focus_aw=0, focus_ah=0, focus_r=0,
pd_radius_equat_minor=0.0, pd_radius_equat_major=0.0, pd_radius_polar=0.0, pd_theta=0.0, pd_Phi=0.0, pd_Psi=0.0)
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| sld | 1e-6/Ang^2 | ([-inf, inf]) Ellipsoid scattering length density. | 4 |
| sld_solvent | 1e-6/Ang^2 | ([-inf, inf]) Solvent scattering length density. | 1 |
| radius_equat_minor | Ang | ([0, inf]) Minor equatorial radius, Ra. | 20 |
| radius_equat_major | Ang | ([0, inf]) Major equatorial radius, Rb. | 400 |
| radius_polar | Ang | ([0, inf]) Polar radius, Rc. | 10 |
| theta |  |  | 60 |
| Phi |  |  | 60 |
| Psi |  |  | 60 |
| model_scale |  | Global scale factor for scattering kernel. For systems without inter-particle interference, the form factors can be related to the scattering intensity by the particle volume fraction. | 1.0 |
| model_abs |  | Absorption cross section density at 2200 m/s. | 0.0 |
| xwidth | m | ([-inf, inf]) Horiz. dimension of sample, as a width. | 0.01 |
| yheight | m | ([-inf, inf]) vert . dimension of sample, as a height for cylinder/box | 0.01 |
| zdepth | m | ([-inf, inf]) depth of sample | 0.005 |
| R | m | Outer radius of sample in (x,z) plane for cylinder/sphere. | 0 |
| target_x | m | relative focus target position. | 0 |
| target_y | m | relative focus target position. | 0 |
| target_z | m | relative focus target position. | 1 |
| target_index |  | Relative index of component to focus at, e.g. next is +1. | 1 |
| focus_xw | m | horiz. dimension of a rectangular area. | 0.5 |
| focus_yh | m | , vert. dimension of a rectangular area. | 0.5 |
| focus_aw | deg | , horiz. angular dimension of a rectangular area. | 0 |
| focus_ah | deg | , vert. angular dimension of a rectangular area. | 0 |
| focus_r | m | case of circular focusing, focusing radius. | 0 |
| pd_radius_equat_minor |  | (0,inf) defined as (dx/x), where x is de mean value and dx the standard devition of the variable. | 0.0 |
| pd_radius_equat_major |  | (0,inf) defined as (dx/x), where x is de mean value and dx the standard devition of the variable. | 0.0 |
| pd_radius_polar |  | (0,inf) defined as (dx/x), where x is de mean value and dx the standard devition of the variable. | 0.0 |
| pd_theta |  | (0,360) defined as (dx/x), where x is de mean value and dx the standard devition of the variable. | 0.0 |
| pd_Phi |  | (0,360) defined as (dx/x), where x is de mean value and dx the standard devition of the variable. | 0.0 |
| pd_Psi |  | (0,360) defined as (dx/x), where x is de mean value and dx the standard devition of the variable | 0.0 |

## Links

- [Source code](/Users/peterwillendrup/Projects/willend-McCode/mcxtrace-comps/sasmodels/SasView_triaxial_ellipsoid_aniso.comp) for `SasView_triaxial_ellipsoid_aniso.comp`.

---

*Generated on mcxtrace 3.99.99.*