# The `SasView_hayter_msa` Component

*McStas: SasView hayter_msa model component as sample description.*

## Identification

- **Site:** 
- **Author:** Jose Robledo
- **Origin:** FZJ / DTU / ESS DMSC
- **Date:** 

## Description

```text
SasView_hayter_msa component, generated from hayter_msa.c in sasmodels.

Example:
SasView_hayter_msa(radius_effective, volfraction, charge, temperature, concentration_salt, dielectconst,
model_scale=1.0, model_abs=0.0, xwidth=0.01, yheight=0.01, zdepth=0.005, R=0,
int target_index=1, target_x=0, target_y=0, target_z=1,
focus_xw=0.5, focus_yh=0.5, focus_aw=0, focus_ah=0, focus_r=0,
pd_radius_effective=0.0, pd_charge=0.0)
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| radius_effective | Ang | ([0, inf]) effective radius of charged sphere. | 20.75 |
| volfraction | None | ([0, 0.74]) volume fraction of spheres. | 0.0192 |
| charge | e | ([1e-06, 200]) charge on sphere (in electrons). | 19.0 |
| temperature | K | ([0, 450]) temperature, in Kelvin, for Debye length calculation. | 318.16 |
| concentration_salt | M | ([0, inf]) conc of salt, moles/litre, 1:1 electolyte, for Debye length. | 0.0 |
| dielectconst | None | ([-inf, inf]) dielectric constant (relative permittivity) of solvent, kappa, default water, for Debye length. | 71.08 |
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
| pd_radius_effective |  | (0,inf) defined as (dx/x), where x is de mean value and dx the standard devition of the variable. | 0.0 |
| pd_charge |  | (0,inf) defined as (dx/x), where x is de mean value and dx the standard devition of the variable | 0.0 |

## Links

- [Source code](SasView_hayter_msa.comp) for `SasView_hayter_msa.comp`.

---

*Generated on mcstas 3.99.99.*