# The `Collimator_ROC` Component

*McStas: Radial Oscillationg Collimator (ROC)*

## Identification

- **Site:** 
- **Author:** <a href="mailto:hansen@ill.fr">Thomas C Hansen</a>
- **Origin:** <a href="http://www.ill.fr">ILL</a> (Dif/<a href="http://www.ill.fr/YellowBook/D20">D20</a>)
- **Date:** 15 May 2000

## Description

```text
ESCRIPTION

This is an implementation of an Ideal radial oscillating collimator,
which is usually placed between a polycrystalline sample and a linear
curved position sensitive detector on a 2-axis diffractometer like D20.
The transfer function has been implemented analytically, as this is
much more efficient than doing Monte-Caqrlo (MC) choices and to absorb
many neutrons on the absorbing blades. The function is basically triangular
(except for rather 'exotic' focuss apertures) and depends on the distance
from the projection of the focus centre to the plane perpendicular to the
collimator planes to the intersection of the same projection of the velocity
vector of the neutron with a line that is perpendicular to it and containing
the same projection of the focus centre. The oscillation is assumed to be
absolutely regular and so shading each angle the same way. All neutrons not
hitting the collimator core will be absorbed.

Example: Collimator_ROC(
ROC_pitch=5, ROC_ri=0.15, ROC_ro=0.3, ROC_h=0.15,
ROC_ttmin=-25, ROC_ttmax=135, ROC_sign=-1)
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| ROC_pitch | deg | Angular pitch between the absorbing blades | 1 |
| ROC_ri | m | Inner radius of the collimator | 0.4 |
| ROC_ro | m | Outer radius of the collimator | 1.2 |
| ROC_h | m | Height of the collimator | 0.153 |
| ROC_ttmin | deg | Lower scattering angle limit | 0 |
| ROC_ttmax | deg | Higher scattering angle limit | 100 |
| ROC_sign | 1 | Chirality/takeoff sign | 1 |

## Links

- [Source code](/Users/peterwillendrup/Projects/willend-McCode/mcstas-comps/contrib/Collimator_ROC.comp) for `Collimator_ROC.comp`.
- <a href="http://www.ill.fr/d20/">D20 diffractometer at the ILL</a>

---

*Generated on mcstas 3.99.99.*