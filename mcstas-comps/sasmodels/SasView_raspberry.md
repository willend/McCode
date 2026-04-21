# The `SasView_raspberry` Component

*McStas: SasView raspberry model component as sample description.*

## Identification

- **Site:** 
- **Author:** Jose Robledo
- **Origin:** FZJ / DTU / ESS DMSC
- **Date:** 

## Description

```text
SasView_raspberry component, generated from raspberry.c in sasmodels.

Example:
SasView_raspberry(sld_lg, sld_sm, sld_solvent, volfraction_lg, volfraction_sm, surface_fraction, radius_lg, radius_sm, penetration,
model_scale=1.0, model_abs=0.0, xwidth=0.01, yheight=0.01, zdepth=0.005, R=0,
int target_index=1, target_x=0, target_y=0, target_z=1,
focus_xw=0.5, focus_yh=0.5, focus_aw=0, focus_ah=0, focus_r=0,
pd_radius_lg=0.0, pd_radius_sm=0.0)
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| sld_lg | 1e-6/Ang^2 | ([-inf, inf]) large particle scattering length density. | -0.4 |
| sld_sm | 1e-6/Ang^2 | ([-inf, inf]) small particle scattering length density. | 3.5 |
| sld_solvent | 1e-6/Ang^2 | ([-inf, inf]) solvent scattering length density. | 6.36 |
| volfraction_lg |  | ([-inf, inf]) volume fraction of large spheres. | 0.05 |
| volfraction_sm |  | ([-inf, inf]) volume fraction of small spheres. | 0.005 |
| surface_fraction |  | ([-inf, inf]) fraction of small spheres at surface. | 0.4 |
| radius_lg | Ang | ([0, inf]) radius of large spheres. | 5000 |
| radius_sm | Ang | ([0, inf]) radius of small spheres. | 100 |
| penetration | Ang | ([-1, 1]) fractional penetration depth of small spheres into large sphere. | 0 |
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
| pd_radius_lg |  | (0,inf) defined as (dx/x), where x is de mean value and dx the standard devition of the variable. | 0.0 |
| pd_radius_sm |  | (0,inf) defined as (dx/x), where x is de mean value and dx the standard devition of the variable | 0.0 |

## Links

- [Source code](SasView_raspberry.comp) for `SasView_raspberry.comp`.

---

*Generated on mcstas 3.99.99.*