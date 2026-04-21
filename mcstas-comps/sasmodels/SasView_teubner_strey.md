# The `SasView_teubner_strey` Component

*McStas: SasView teubner_strey model component as sample description.*

## Identification

- **Site:** 
- **Author:** Jose Robledo
- **Origin:** FZJ / DTU / ESS DMSC
- **Date:** 

## Description

```text
SasView_teubner_strey component, generated from teubner_strey.c in sasmodels.

Example:
SasView_teubner_strey(volfraction_a, sld_a, sld_b, d, xi,
model_scale=1.0, model_abs=0.0, xwidth=0.01, yheight=0.01, zdepth=0.005, R=0,
int target_index=1, target_x=0, target_y=0, target_z=1,
focus_xw=0.5, focus_yh=0.5, focus_aw=0, focus_ah=0, focus_r=0,
)
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| volfraction_a |  | ([0, 1.0]) Volume fraction of phase a. | 0.5 |
| sld_a | 1e-6/Ang^2 | ([-inf, inf]) SLD of phase a. | 0.3 |
| sld_b | 1e-6/Ang^2 | ([-inf, inf]) SLD of phase b. | 6.3 |
| d | Ang | ([0, inf]) Domain size (periodicity). | 100.0 |
| xi | Ang | ([0, inf]) Correlation length. | 30.0 |
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

## Links

- [Source code](SasView_teubner_strey.comp) for `SasView_teubner_strey.comp`.

---

*Generated on mcstas 3.99.99.*