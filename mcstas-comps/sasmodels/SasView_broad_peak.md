# The `SasView_broad_peak` Component

*McStas: SasView broad_peak model component as sample description.*

## Identification

- **Site:** 
- **Author:** Jose Robledo
- **Origin:** FZJ / DTU / ESS DMSC
- **Date:** 

## Description

```text
SasView_broad_peak component, generated from broad_peak.c in sasmodels.

Example:
SasView_broad_peak(porod_scale, porod_exp, peak_scale, correlation_length, peak_pos, width_exp, shape_exp,
model_scale=1.0, model_abs=0.0, xwidth=0.01, yheight=0.01, zdepth=0.005, R=0,
int target_index=1, target_x=0, target_y=0, target_z=1,
focus_xw=0.5, focus_yh=0.5, focus_aw=0, focus_ah=0, focus_r=0,
pd_correlation_length=0.0)
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| porod_scale |  | ([-inf, inf]) Power law scale factor. | 1e-05 |
| porod_exp |  | ([-inf, inf]) Exponent of power law. | 3.0 |
| peak_scale |  | ([-inf, inf]) Scale factor for broad peak. | 10.0 |
| correlation_length | Ang | ([-inf, inf]) screening length. | 50.0 |
| peak_pos | 1/Ang | ([-inf, inf]) Peak position in q. | 0.1 |
| width_exp |  | ([-inf, inf]) Exponent of peak width. | 2.0 |
| shape_exp |  | ([-inf, inf]) Exponent of peak shape. | 1.0 |
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
| pd_correlation_length |  | (0,inf) defined as (dx/x), where x is de mean value and dx the standard devition of the variable | 0.0 |

## Links

- [Source code](SasView_broad_peak.comp) for `SasView_broad_peak.comp`.

---

*Generated on mcstas 3.99.99.*