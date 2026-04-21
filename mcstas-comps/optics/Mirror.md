# The `Mirror` Component

*McStas: Single mirror plate.*

## Identification

- **Site:** 
- **Author:** Kristian Nielsen
- **Origin:** Risoe
- **Date:** August 1998

## Description

```text
Single mirror plate (used to build guides in compound components).
The component Mirror models a single rectangular neutron mirror plate.
It can be used as a sample component or to e.g. assemble a complete neutron
guide by putting multiple mirror components at appropriate locations and
orientations in the instrument definition, much like a real guide is build
from individual mirrors.
Additionally, it may be centered in order to be used as a sample or
monochromator plate, else it starts from AT position.
Reflectivity is either defined by an analytical model (see Component Manual)
or from a two-columns file with q [Angs-1] as first and R [0-1] as second.
In the local coordinate system, the mirror lies in the first quadrant of the
x-y plane, with one corner at (0, 0, 0). Plane is thus perpendicular to the
incoming beam, and should usually be rotated.

Example: Mirror(xwidth=.1, yheight=.1,R0=0.99,Qc=0.021,alpha=6.1,m=2,W=0.003)
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| reflect | str | Name of reflectivity file. Format q(Angs-1) R(0-1) | 0 |
| **xwidth** | m | width of mirror plate |  |
| **yheight** | m | height of mirror plate |  |
| R0 | 1 | Low-angle reflectivity | 0.99 |
| Qc | AA-1 | Critical scattering vector | 0.021 |
| alpha | AA | Slope of reflectivity | 6.07 |
| m | 1 | m-value of material. Zero means completely absorbing. | 2 |
| W | AA-1 | Width of supermirror cut-off | 0.003 |
| center | 1 | if true (1), the Mirror is centered arount AT position. | 0 |
| transmit | 1 | When true, non reflected neutrons are transmitted through the mirror, instead of being absorbed. | 0 |

## Links

- [Source code](Mirror.comp) for `Mirror.comp`.

---

*Generated on mcstas 3.99.99.*