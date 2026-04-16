# The `SasView_stacked_disks_aniso` Component

*McStas: SasView stacked_disks model component as sample description.*

## Identification

- **Site:** 
- **Author:** Jose Robledo
- **Origin:** FZJ / DTU / ESS DMSC
- **Date:** 

## Description

```text
SasView_stacked_disks component, generated from stacked_disks.c in sasmodels.

Example:
SasView_stacked_disks_aniso(thick_core, thick_layer, radius, n_stacking, sigma_d, sld_core, sld_layer, sld_solvent, theta, phi,
model_scale=1.0, model_abs=0.0, xwidth=0.01, yheight=0.01, zdepth=0.005, R=0,
int target_index=1, target_x=0, target_y=0, target_z=1,
focus_xw=0.5, focus_yh=0.5, focus_aw=0, focus_ah=0, focus_r=0,
pd_thick_core=0.0, pd_thick_layer=0.0, pd_radius=0.0, pd_theta=0.0, pd_phi=0.0)
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| thick_core | Ang | ([0, inf]) Thickness of the core disk. | 10.0 |
| thick_layer | Ang | ([0, inf]) Thickness of layer each side of core. | 10.0 |
| radius | Ang | ([0, inf]) Radius of the stacked disk. | 15.0 |
| n_stacking |  | ([1, inf]) Number of stacked layer/core/layer disks. | 1.0 |
| sigma_d | Ang | ([0, inf]) Sigma of nearest neighbor spacing. | 0 |
| sld_core | 1e-6/Ang^2 | ([-inf, inf]) Core scattering length density. | 4 |
| sld_layer | 1e-6/Ang^2 | ([-inf, inf]) Layer scattering length density. | 0.0 |
| sld_solvent | 1e-6/Ang^2 | ([-inf, inf]) Solvent scattering length density. | 5.0 |
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
| pd_thick_core |  | (0,inf) defined as (dx/x), where x is de mean value and dx the standard devition of the variable. | 0.0 |
| pd_thick_layer |  | (0,inf) defined as (dx/x), where x is de mean value and dx the standard devition of the variable. | 0.0 |
| pd_radius |  | (0,inf) defined as (dx/x), where x is de mean value and dx the standard devition of the variable. | 0.0 |
| pd_theta |  | (0,360) defined as (dx/x), where x is de mean value and dx the standard devition of the variable. | 0.0 |
| pd_phi |  | (0,360) defined as (dx/x), where x is de mean value and dx the standard devition of the variable | 0.0 |

## Links

- [Source code](/Users/peterwillendrup/Projects/willend-McCode/mcstas-comps/sasmodels/SasView_stacked_disks_aniso.comp) for `SasView_stacked_disks_aniso.comp`.

---

*Generated on mcstas 3.99.99.*