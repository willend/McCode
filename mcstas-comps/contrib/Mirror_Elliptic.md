# The `Mirror_Elliptic` Component

*McStas: Elliptical mirror.*

## Identification

- **Site:** 
- **Author:** <a href="mailto:desert@drecam.cea.fr">Sylvain Desert</a>
- **Origin:** <a href="http://www-llb.cea.fr/">LLB</a>
- **Date:** 2007

## Description

```text
Models an elliptical mirror. The reflectivity profile is given by a 2-column reflectivity free
text file with format [q(Angs-1) R(0-1)]. The component is centered on the ellipse.

Example:  Mirror_Elliptic(reflect="supermirror_m3.rfl", focus=6.6e-4,
interfocus = 8.2, yheight = 0.0002, zmin=-3.24, zmax=-1.49)
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| reflect | q(Angs-1) R(0-1) | (str) Reflectivity file name. Format | 0 |
| focus | m | focal length (m) | 6.6e-4 |
| interfocus | m | Distance between the two elliptical focal points | 8.2 |
| yheight | m | height of the mirror | 2e-4 |
| zmin | m | z-axis coordinate of ellipse start | 0 |
| zmax | m | z-axis coordinate of ellipse end | 0 |
| R0 | 1 | Low-angle reflectivity | 0.99 |
| Qc | AA-1 | Critical scattering vector | 0.0219 |
| alpha | AA | Slope of reflectivity | 6.07 |
| m | 1 | m-value of material. Zero means completely absorbing. | 1.0 |
| W | AA-1 | Width of supermirror cut-off | 0.003 |

## Links

- [Source code](Mirror_Elliptic.comp) for `Mirror_Elliptic.comp`.

---

*Generated on mcstas 3.99.99.*