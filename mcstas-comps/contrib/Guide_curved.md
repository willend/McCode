# The `Guide_curved` Component

*McStas: Non-focusing curved neutron guide.*

## Identification

- **Site:** 
- **Author:** Ross Stewart
- **Origin:** <a href="http://www.ill.fr">ILL (France)</a>.
- **Date:** November 18 2003

## Description

```text
Models a rectangular curved guide tube with entrance centered on the Z axis.
The entrance lies in the X-Y plane.  Draws a true depiction
of the guide, and trajectories.  Guide is not focusing.

Example: Guide_curved(w1=0.1, h1=0.1, l=2.0, R0=0.99, Qc=0.021,
alpha=6.07, m=2, W=0.003, curvature=2700)

%BUGS
This component does not work with gravitation on. Use component Guide_gravity then.
Systematic error on transmitted flux is found to be about 10%.
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| **w1** | m | Width at the guide entry |  |
| **h1** | m | Height at the guide entry |  |
| **l** | m | length of guide |  |
| R0 | 1 | Low-angle reflectivity | 0.995 |
| Qc | AA-1 | Critical scattering vector | 0.0218 |
| alpha | AA | Slope of reflectivity | 4.38 |
| m | 1 | m-value of material. Zero means completely absorbing. | 2 |
| W | AA-1 | Width of supermirror cut-off | 0.003 |
| curvature | m | Radius of curvature of the guide | 2700 |

## Links

- [Source code](/Users/peterwillendrup/Projects/willend-McCode/mcstas-comps/contrib/Guide_curved.comp) for `Guide_curved.comp`.
- <a href="../optics/Bender.comp.html">Bender</a>

---

*Generated on mcstas 3.99.99.*