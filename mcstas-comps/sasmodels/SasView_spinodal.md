# The `SasView_spinodal` Component

*McStas: SasView spinodal model component as sample description.*

## Identification

- **Site:** 
- **Author:** Jose Robledo
- **Origin:** FZJ / DTU / ESS DMSC
- **Date:** 

## Description

```text
SasView_spinodal component, generated from spinodal.c in sasmodels.

Example:
SasView_spinodal(gamma, q_0,
model_scale=1.0, model_abs=0.0, xwidth=0.01, yheight=0.01, zdepth=0.005, R=0,
int target_index=1, target_x=0, target_y=0, target_z=1,
focus_xw=0.5, focus_yh=0.5, focus_aw=0, focus_ah=0, focus_r=0,
)
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| gamma |  | ([-inf, inf]) Exponent. | 3.0 |
| q_0 | 1/Ang | ([-inf, inf]) Correlation peak position. | 0.1 |
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

- [Source code](SasView_spinodal.comp) for `SasView_spinodal.comp`.

---

*Generated on mcstas 3.99.99.*