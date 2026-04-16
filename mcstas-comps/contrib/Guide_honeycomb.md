# The `Guide_honeycomb` Component

*McStas: Neutron guide with gravity and honeycomb geometry. Can be channeled and focusing.*

## Identification

- **Site:** 
- **Author:** G. Venturi
- **Origin:** <a href="http://www.ill.fr">ILL (France)</a>.
- **Date:** Apr 2003

## Description

```text
Models a honeycomb guide tube centered on the Z axis. The entrance lies
in the X-Y plane. Gravitation applies also when reaching the guide input
window. The guide can be channeled (hexagonal channel section; nslit,d parameters).
The guide coating specifications may be entered via different ways (global,
or for each wall m-value).
For details on the geometry calculation see the description in the McStas
reference manual.

Example: Guide_honeycomb(w1=0.1, w2=0.1, l=12,
R0=0.99, Qc=0.0219, alpha=6.07, m=1.0, W=0.003, nslit=1, d=0.0005)
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| **w1** | m | Width at the guide entry |  |
| w2 | m | Width at the guide exit. If zero, sets w2=w1. | 0 |
| **l** | m | length of guide |  |
| R0 | 1 | Low-angle reflectivity | 0.995 |
| Qc | AA-1 | Critical scattering vector | 0.0218 |
| alpha | AA | Slope of reflectivity | 4.38 |
| m | 1 | m-value of material. Zero means completely absorbing. | 1.0 |
| W | AA-1 | Width of supermirror cut-off | 0.003 |
| nslit | 1 | Number of horizontal channels in the guide (>= 1) [1] | 1 |
| d | m | Thickness of subdividing walls [0] | 0.0005 |
| mleftup | 1 | m-value of material for leftup.    oblique mirror | -1 |
| mrightup | 1 | m-value of material for rightdown. oblique mirror | -1 |
| mleftdown | 1 | m-value of material for rightdown. oblique mirror | -1 |
| mrightdown | 1 | m-value of material for leftup.    oblique mirror | -1 |
| mleft | 1 | m-value of material for left.      vertical mirror | -1 |
| mright | 1 | m-value of material for right.     vertical mirror | -1 |
| G | m/s2 | Gravitation norm. 0 value disables G effects. | 0 |

## Links

- [Source code](/Users/peterwillendrup/Projects/willend-McCode/mcstas-comps/contrib/Guide_honeycomb.comp) for `Guide_honeycomb.comp`.

---

*Generated on mcstas 3.99.99.*