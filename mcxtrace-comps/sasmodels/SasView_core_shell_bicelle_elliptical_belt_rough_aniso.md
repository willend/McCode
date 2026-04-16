# The `SasView_core_shell_bicelle_elliptical_belt_rough_aniso` Component

*McXtrace: SasView core_shell_bicelle_elliptical_belt_rough model component as sample description.*

## Identification

- **Site:** 
- **Author:** Jose Robledo
- **Origin:** FZJ / DTU / ESS DMSC
- **Date:** 

## Description

```text
SasView_core_shell_bicelle_elliptical_belt_rough component, generated from core_shell_bicelle_elliptical_belt_rough.c in sasmodels.

Example:
SasView_core_shell_bicelle_elliptical_belt_rough_aniso(radius, x_core, thick_rim, thick_face, length, sld_core, sld_face, sld_rim, sld_solvent, sigma, theta, Phi, Psi,
model_scale=1.0, model_abs=0.0, xwidth=0.01, yheight=0.01, zdepth=0.005, R=0,
int target_index=1, target_x=0, target_y=0, target_z=1,
focus_xw=0.5, focus_yh=0.5, focus_aw=0, focus_ah=0, focus_r=0,
pd_radius=0.0, pd_thick_rim=0.0, pd_thick_face=0.0, pd_length=0.0, pd_theta=0.0, pd_Phi=0.0, pd_Psi=0.0)
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| radius | Ang | ([0, inf]) Cylinder core radius r_minor. | 30 |
| x_core | None | ([0, inf]) Axial ratio of core, X = r_major/r_minor. | 3 |
| thick_rim | Ang | ([0, inf]) Rim or belt shell thickness. | 8 |
| thick_face | Ang | ([0, inf]) Cylinder face thickness. | 14 |
| length | Ang | ([0, inf]) Cylinder length. | 50 |
| sld_core | 1e-6/Ang^2 | ([-inf, inf]) Cylinder core scattering length density. | 4 |
| sld_face | 1e-6/Ang^2 | ([-inf, inf]) Cylinder face scattering length density. | 7 |
| sld_rim | 1e-6/Ang^2 | ([-inf, inf]) Cylinder rim scattering length density. | 1 |
| sld_solvent | 1e-6/Ang^2 | ([-inf, inf]) Solvent scattering length density. | 6 |
| sigma | Ang | ([0, inf]) Interfacial roughness. | 0 |
| theta |  |  | 90.0 |
| Phi |  |  | 0 |
| Psi |  |  | 0 |
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
| pd_radius |  | (0,inf) defined as (dx/x), where x is de mean value and dx the standard devition of the variable. | 0.0 |
| pd_thick_rim |  | (0,inf) defined as (dx/x), where x is de mean value and dx the standard devition of the variable. | 0.0 |
| pd_thick_face |  | (0,inf) defined as (dx/x), where x is de mean value and dx the standard devition of the variable. | 0.0 |
| pd_length |  | (0,inf) defined as (dx/x), where x is de mean value and dx the standard devition of the variable. | 0.0 |
| pd_theta |  | (0,360) defined as (dx/x), where x is de mean value and dx the standard devition of the variable. | 0.0 |
| pd_Phi |  | (0,360) defined as (dx/x), where x is de mean value and dx the standard devition of the variable. | 0.0 |
| pd_Psi |  | (0,360) defined as (dx/x), where x is de mean value and dx the standard devition of the variable | 0.0 |

## Links

- [Source code](/Users/peterwillendrup/Projects/willend-McCode/mcxtrace-comps/sasmodels/SasView_core_shell_bicelle_elliptical_belt_rough_aniso.comp) for `SasView_core_shell_bicelle_elliptical_belt_rough_aniso.comp`.

---

*Generated on mcxtrace 3.99.99.*