# The `FZP_simple` Component

*McStas: Fresnel zone-plate as a thin object approximation.*

## Identification

- **Site:** 
- **Author:** A Komar Ravn, and Erik B Knudsen
- **Origin:** NBI/DTU
- **Date:** Aug, 2015

## Description

```text
A simple phenomenological thin-object approximation of a Fresnel Zone Plate.
This component was adapted for neutrons from the original component
written for helium scattering.
The focal length of the Zone Plate is determined by the formula:
\[f = 2*r*dr/(lambda)\]
If a diffraction order other than 1 is wanted the focal distance is scaled accordingly.
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| **rad** | m | Radius of  the zone-plate. |  |
| **dr** | m | Width of the outermost ring-slit. |  |
| bs0rad | m | Radius of the central blocking zone. | 0 |
| order | m | Use this diffaction order. | 1 |
| eta |  | Efficiency of the FZP. For neutrons and (order==1) typically {5...30}%. Overrides the sigma_x cross sections. | 0.1 |
| sigma_abs | barn | 2200 m/s absorption cross section. | 0 |
| sigma_inc | barn | Incoherent scattering cross section. | 0 |
| sigma_coh | barn | Coherent scattering cross section. | 0 |
| rho | g/cm3 | Density of Zone plate material - used merely for absorption estimation. | 1 |
| thickness | m | Thickness of the FZP. Note that the FZP still is modelled as a thin object. The thickness is used in conjunction with the sigma_x cross sections. | 0 |
| gamma |  | Duty cycle of the Zone plate - used merely for absorption estimation. | 0.5 |

## Links

- [Source code](/Users/peterwillendrup/Projects/willend-McCode/mcstas-comps/optics/FZP_simple.comp) for `FZP_simple.comp`.

---

*Generated on mcstas 3.99.99.*