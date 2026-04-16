# The `Mirror_Parabolic` Component

*McStas: Parabolic mirror.*

## Identification

- **Site:** 
- **Author:** <a href="mailto:desert@drecam.cea.fr">Sylvain Desert</a>
- **Origin:** <a href="http://www-llb.cea.fr/">LLB</a>
- **Date:** 2007

## Description

```text
Models a parabolic mirror. The reflectivity profile is given by a 2-column reflectivity free
text file with format [q(Angs-1) R(0-1)].

Example:  Mirror_Parabolic(reflect="supermirror_m3.rfl", xwidth = 0.05, xshift=0.05,
yheight = 2e-4, focus = 6.6e-4)
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| reflect | q(Angs-1) R(0-1) | (str) Reflectivity file name. Format | 0 |
| xwidth | m | width of the illuminated parabola | 0.05 |
| xshift | m | distance between the beam centre and the symetric axis of the parabolla | 0.019 |
| yheight | m | height of the mirror | 2e-4 |
| focus | m | focal length | 6.6e-4 |
| R0 | 1 | Low-angle reflectivity | 0.99 |
| Qc | AA-1 | Critical scattering vector | 0.0219 |
| alpha | AA | Slope of reflectivity | 6.07 |
| m | 1 | m-value of material. Zero means completely absorbing. | 1.0 |
| W | AA-1 | Width of supermirror cut-off | 0.003 |

## Links

- [Source code](/Users/peterwillendrup/Projects/willend-McCode/mcstas-comps/contrib/Mirror_Parabolic.comp) for `Mirror_Parabolic.comp`.

---

*Generated on mcstas 3.99.99.*