# The `Guide_m` Component

*McStas: Release: McStas 1.12c

Neutron guide.*

## Identification

- **Site:** 
- **Author:** Kristian Nielsen
- **Origin:** Risoe
- **Date:** September 2 1998, Modified 2013

## Description

```text
Models a rectangular guide tube centered on the Z axis. The entrance lies
in the X-Y plane.
For details on the geometry calculation see the description in the McStas
reference manual.
The reflectivity profile may either use an analytical mode (see Component
Manual) or a 2-columns reflectivity free text file with format
[q(Angs-1) R(0-1)].

Example: Guide(w1=0.1, h1=0.1, w2=0.1, h2=0.1, l=2.0,
R0=0.99, Qc=0.021, alpha=6.07, m=2, W=0.003

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
| reflect | str | Reflectivity file name. Format [q(Angs-1) R(0-1)] | 0 |
| **w1** | m | Width at the guide entry |  |
| **h1** | m | Height at the guide entry |  |
| **w2** | m | Width at the guide exit |  |
| **h2** | m | Height at the guide exit |  |
| **l** | m | Length of guide |  |
| R0_left | 1 | Low-angle reflectivity, left mirrror. | 0.99 |
| R0_right | 1 | Low-angle reflectivity, right mirror. | 0.99 |
| R0_top | 1 | Low-angle reflectivity, top mirror. | 0.99 |
| R0_bottom | 1 | Low-angle reflectivity, bottom mirror. | 0.99 |
| Qc_left | AA-1 | Critical scattering vector, left mirrror. | 0.0219 |
| Qc_right | AA-1 | Critical scattering vector, right mirror. | 0.0219 |
| Qc_top | AA-1 | Critical scattering vector, top mirror. | 0.0219 |
| Qc_bottom | AA-1 | Critical scattering vector, bottom mirror. | 0.0219 |
| aleft | AA | Slope of reflectivity, left mirrror. | 6.07 |
| aright | AA | Slope of reflectivity, right mirror. | 6.07 |
| atop | AA | Slope of reflectivity, top mirror. | 6.07 |
| abottom | AA | Slope of reflectivity, bottom mirror. | 6.07 |
| mleft | 1 | m-value of material. Zero means completely absorbing, left mirrror. | 2 |
| mright | 1 | m-value of material. Zero means completely absorbing, right mirror. | 2 |
| mtop | 1 | m-value of material. Zero means completely absorbing, top mirror. | 2 |
| mbottom | 1 | m-value of material. Zero means completely absorbing, bottom mirror. | 2 |
| W_left | AA-1 | Width of supermirror cut-off, left mirrror. | 0.003 |
| W_right | AA-1 | Width of supermirror cut-off, right mirror. | 0.003 |
| W_top | AA-1 | Width of supermirror cut-off, top mirror. | 0.003 |
| W_bottom | AA-1 | Width of supermirror cut-off, bottom mirror. | 0.003 |
| W | AA-1 | Overall width of supermirror cut-off, overwrites values from individual mirrors | 0 |
| m | 1 | Overall m-value of supermirrors, overwrites values from individual mirrors | 0 |
| alpha | AA | Overall slope of reflectivity, overwrites values from individual mirrors | 0 |
| R0 | 1 | Overall, low-angle reflectivity, overwrites values from individual mirrors | 0 |
| Qc | AA-1 | Overall, critical scattering vector, overwrites values from individual mirrors | 0 |

## Links

- [Source code](Guide_m.comp) for `Guide_m.comp`.

---

*Generated on mcstas 3.99.99.*