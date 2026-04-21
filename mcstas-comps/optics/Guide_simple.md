# The `Guide_simple` Component

*McStas: Neutron guide.*

## Identification

- **Site:** 
- **Author:** Kristian Nielsen
- **Origin:** Risoe
- **Date:** September 2 1998

## Description

```text
Models a rectangular guide tube centered on the Z axis. The entrance lies
in the X-Y plane.
For details on the geometry calculation see the description in the McStas
reference manual.
The reflectivity profile may either use an analytical mode (see Component
Manual) or a 2-columns reflectivity free text file with format
[q(Angs-1) R(0-1)].

Example: Guide(w1=0.1, h1=0.1, w2=0.1, h2=0.1, l=2.0, R0=0.99, Qc=0.021, alpha=6.07, m=2, W=0.003

%VALIDATION
May 2005: extensive internal test, no bugs found
Validated by: K. Lieutenant

%BUGS
This component does not work with gravitation on. Use component Guide_gravity then.
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| **w1** | m | Width at the guide entry |  |
| **h1** | m | Height at the guide entry |  |
| w2 | m | Width at the guide exit | 0 |
| h2 | m | Height at the guide exit | 0 |
| **l** | m | length of guide |  |
| R0 | 1 | Low-angle reflectivity | 0.99 |
| Qc | AA-1 | Critical scattering vector | 0.0219 |
| alpha | AA | Slope of reflectivity | 6.07 |
| m | 1 | m-value of material. Zero means completely absorbing. glass/SiO2 Si Ni Ni58 supermirror Be Diamond m=  0.65 0.47 1 1.18 2-6 1.01 1.12 | 2 |
| W | AA-1 | Width of supermirror cut-off | 0.003 |

## Links

- [Source code](Guide_simple.comp) for `Guide_simple.comp`.

---

*Generated on mcstas 3.99.99.*