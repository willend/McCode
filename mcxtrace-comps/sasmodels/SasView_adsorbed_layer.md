# The `SasView_adsorbed_layer` Component

*McXtrace: SasView adsorbed_layer model component as sample description.*

## Identification

- **Site:** 
- **Author:** Jose Robledo
- **Origin:** FZJ / DTU / ESS DMSC
- **Date:** 

## Description

```text
SasView_adsorbed_layer component, generated from adsorbed_layer.c in sasmodels.

Example:
SasView_adsorbed_layer(second_moment, adsorbed_amount, density_shell, radius, volfraction, sld_shell, sld_solvent,
model_scale=1.0, model_abs=0.0, xwidth=0.01, yheight=0.01, zdepth=0.005, R=0,
int target_index=1, target_x=0, target_y=0, target_z=1,
focus_xw=0.5, focus_yh=0.5, focus_aw=0, focus_ah=0, focus_r=0,
pd_radius=0.0)
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| second_moment | Ang | ([0.0, inf]) Second moment of polymer distribution. | 23.0 |
| adsorbed_amount | mg/m^2 | ([0.0, inf]) Adsorbed amount of polymer. | 1.9 |
| density_shell | g/cm^3 | ([0.0, inf]) Bulk density of polymer in the shell. | 0.7 |
| radius | Ang | ([0.0, inf]) Core particle radius. | 500.0 |
| volfraction | None | ([0.0, inf]) Core particle volume fraction. | 0.14 |
| sld_shell | 1e-6/Ang^2 | ([-inf, inf]) Polymer shell SLD. | 1.5 |
| sld_solvent | 1e-6/Ang^2 | ([-inf, inf]) Solvent SLD. | 6.3 |
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
| pd_radius |  | (0,inf) defined as (dx/x), where x is de mean value and dx the standard devition of the variable | 0.0 |

## Links

- [Source code](/Users/peterwillendrup/Projects/willend-McCode/mcxtrace-comps/sasmodels/SasView_adsorbed_layer.comp) for `SasView_adsorbed_layer.comp`.

---

*Generated on mcxtrace 3.99.99.*