# The `SasView_core_shell_ellipsoid_aniso` Component

*McStas: SasView core_shell_ellipsoid model component as sample description.*

## Identification

- **Site:** 
- **Author:** Jose Robledo
- **Origin:** FZJ / DTU / ESS DMSC
- **Date:** 

## Description

```text
SasView_core_shell_ellipsoid component, generated from core_shell_ellipsoid.c in sasmodels.

Example:
SasView_core_shell_ellipsoid_aniso(radius_equat_core, x_core, thick_shell, x_polar_shell, sld_core, sld_shell, sld_solvent, theta, phi,
model_scale=1.0, model_abs=0.0, xwidth=0.01, yheight=0.01, zdepth=0.005, R=0,
int target_index=1, target_x=0, target_y=0, target_z=1,
focus_xw=0.5, focus_yh=0.5, focus_aw=0, focus_ah=0, focus_r=0,
pd_radius_equat_core=0.0, pd_thick_shell=0.0, pd_theta=0.0, pd_phi=0.0)
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| radius_equat_core | Ang | ([0, inf]) Equatorial radius of core. | 20 |
| x_core | None | ([0, inf]) axial ratio of core, X = r_polar/r_equatorial. | 3 |
| thick_shell | Ang | ([0, inf]) thickness of shell at equator. | 30 |
| x_polar_shell |  | ([0, inf]) ratio of thickness of shell at pole to that at equator. | 1 |
| sld_core | 1e-6/Ang^2 | ([-inf, inf]) Core scattering length density. | 2 |
| sld_shell | 1e-6/Ang^2 | ([-inf, inf]) Shell scattering length density. | 1 |
| sld_solvent | 1e-6/Ang^2 | ([-inf, inf]) Solvent scattering length density. | 6.3 |
| theta |  |  | 0 |
| phi |  |  | 0 |
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
| pd_radius_equat_core |  | (0,inf) defined as (dx/x), where x is de mean value and dx the standard devition of the variable. | 0.0 |
| pd_thick_shell |  | (0,inf) defined as (dx/x), where x is de mean value and dx the standard devition of the variable. | 0.0 |
| pd_theta |  | (0,360) defined as (dx/x), where x is de mean value and dx the standard devition of the variable. | 0.0 |
| pd_phi |  | (0,360) defined as (dx/x), where x is de mean value and dx the standard devition of the variable | 0.0 |

## Links

- [Source code](SasView_core_shell_ellipsoid_aniso.comp) for `SasView_core_shell_ellipsoid_aniso.comp`.

---

*Generated on mcstas 3.99.99.*