# The `SasView_polymer_micelle` Component

*McStas: SasView polymer_micelle model component as sample description.*

## Identification

- **Site:** 
- **Author:** Jose Robledo
- **Origin:** FZJ / DTU / ESS DMSC
- **Date:** 

## Description

```text
SasView_polymer_micelle component, generated from polymer_micelle.c in sasmodels.

Example:
SasView_polymer_micelle(ndensity, v_core, v_corona, sld_solvent, sld_core, sld_corona, radius_core, rg, d_penetration, n_aggreg,
model_scale=1.0, model_abs=0.0, xwidth=0.01, yheight=0.01, zdepth=0.005, R=0,
int target_index=1, target_x=0, target_y=0, target_z=1,
focus_xw=0.5, focus_yh=0.5, focus_aw=0, focus_ah=0, focus_r=0,
pd_radius_core=0.0, pd_rg=0.0)
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| ndensity | 1e15/cm^3 | ([0.0, inf]) Number density of micelles. | 8.94 |
| v_core | Ang^3 | ([0.0, inf]) Core volume . | 62624.0 |
| v_corona | Ang^3 | ([0.0, inf]) Corona volume. | 61940.0 |
| sld_solvent | 1e-6/Ang^2 | ([0.0, inf]) Solvent scattering length density. | 6.4 |
| sld_core | 1e-6/Ang^2 | ([0.0, inf]) Core scattering length density. | 0.34 |
| sld_corona | 1e-6/Ang^2 | ([0.0, inf]) Corona scattering length density. | 0.8 |
| radius_core | Ang | ([0.0, inf]) Radius of core ( must be >> rg ). | 45.0 |
| rg | Ang | ([0.0, inf]) Radius of gyration of chains in corona. | 20.0 |
| d_penetration |  | ([-inf, inf]) Factor to mimic non-penetration of Gaussian chains. | 1.0 |
| n_aggreg |  | ([-inf, inf]) Aggregation number of the micelle. | 6.0 |
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
| pd_radius_core |  | (0,inf) defined as (dx/x), where x is de mean value and dx the standard devition of the variable. | 0.0 |
| pd_rg |  | (0,inf) defined as (dx/x), where x is de mean value and dx the standard devition of the variable | 0.0 |

## Links

- [Source code](SasView_polymer_micelle.comp) for `SasView_polymer_micelle.comp`.

---

*Generated on mcstas 3.99.99.*