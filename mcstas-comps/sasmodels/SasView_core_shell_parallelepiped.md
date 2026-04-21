# The `SasView_core_shell_parallelepiped` Component

*McStas: SasView core_shell_parallelepiped model component as sample description.*

## Identification

- **Site:** 
- **Author:** Jose Robledo
- **Origin:** FZJ / DTU / ESS DMSC
- **Date:** 

## Description

```text
SasView_core_shell_parallelepiped component, generated from core_shell_parallelepiped.c in sasmodels.

Example:
SasView_core_shell_parallelepiped(sld_core, sld_a, sld_b, sld_c, sld_solvent, length_a, length_b, length_c, thick_rim_a, thick_rim_b, thick_rim_c,
model_scale=1.0, model_abs=0.0, xwidth=0.01, yheight=0.01, zdepth=0.005, R=0,
int target_index=1, target_x=0, target_y=0, target_z=1,
focus_xw=0.5, focus_yh=0.5, focus_aw=0, focus_ah=0, focus_r=0,
pd_length_a=0.0, pd_length_b=0.0, pd_length_c=0.0, pd_thick_rim_a=0.0, pd_thick_rim_b=0.0, pd_thick_rim_c=0.0)
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| sld_core | 1e-6/Ang^2 | ([-inf, inf]) Parallelepiped core scattering length density. | 1 |
| sld_a | 1e-6/Ang^2 | ([-inf, inf]) Parallelepiped A rim scattering length density. | 2 |
| sld_b | 1e-6/Ang^2 | ([-inf, inf]) Parallelepiped B rim scattering length density. | 4 |
| sld_c | 1e-6/Ang^2 | ([-inf, inf]) Parallelepiped C rim scattering length density. | 2 |
| sld_solvent | 1e-6/Ang^2 | ([-inf, inf]) Solvent scattering length density. | 6 |
| length_a | Ang | ([0, inf]) Shorter side of the parallelepiped. | 35 |
| length_b | Ang | ([0, inf]) Second side of the parallelepiped. | 75 |
| length_c | Ang | ([0, inf]) Larger side of the parallelepiped. | 400 |
| thick_rim_a | Ang | ([0, inf]) Thickness of A rim. | 10 |
| thick_rim_b | Ang | ([0, inf]) Thickness of B rim. | 10 |
| thick_rim_c | Ang | ([0, inf]) Thickness of C rim. | 10 |
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
| pd_length_a |  | (0,inf) defined as (dx/x), where x is de mean value and dx the standard devition of the variable. | 0.0 |
| pd_length_b |  | (0,inf) defined as (dx/x), where x is de mean value and dx the standard devition of the variable. | 0.0 |
| pd_length_c |  | (0,inf) defined as (dx/x), where x is de mean value and dx the standard devition of the variable. | 0.0 |
| pd_thick_rim_a |  | (0,inf) defined as (dx/x), where x is de mean value and dx the standard devition of the variable. | 0.0 |
| pd_thick_rim_b |  | (0,inf) defined as (dx/x), where x is de mean value and dx the standard devition of the variable. | 0.0 |
| pd_thick_rim_c |  | (0,inf) defined as (dx/x), where x is de mean value and dx the standard devition of the variable | 0.0 |

## Links

- [Source code](SasView_core_shell_parallelepiped.comp) for `SasView_core_shell_parallelepiped.comp`.

---

*Generated on mcstas 3.99.99.*