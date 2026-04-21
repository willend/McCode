# The `Guide_wavy` Component

*McStas: Neutron guide with gaussian waviness.*

## Identification

- **Site:** 
- **Author:** Kim Lefmann
- **Origin:** Risoe
- **Date:** 

## Description

```text
Models a rectangular guide tube centered on the Z axis. The entrance lies
in the X-Y plane.
For details on the geometry calculation see the description in the McStas
reference manual.

Example: m=2 Qc=0.0218 (nat. Ni) W=1/300 alpha=4.38 R0=0.995 (given by Daniel Clemens, PSI)

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
| R0 | 1 | Low-angle reflectivity | 0.995 |
| Qc | AA-1 | Critical scattering vector | 0.0218 |
| alpha | AA | Slope of reflectivity | 0 |
| m | 1 | m-value of material. Zero means completely absorbing. | 0 |
| W | AA-1 | Width of supermirror cut-off for all mirrors | 0 |
| alpha1 | AA | Slope of reflectivity left | 4.38 |
| m1 | 1 | m-value of material, left | 2 |
| W1 | AA-1 | Width of supermirror cut-off left | 0.003 |
| alpha2 | AA | Slope of reflectivity right | 4.38 |
| m2 | 1 | m-value of material, right. | 2 |
| W2 | AA-1 | Width of supermirror cut-off right | 0.003 |
| alpha3 | AA | Slope of reflectivity top | 4.38 |
| m3 | 1 | m-value of material, top. | 2 |
| W3 | AA-1 | Width of supermirror cut-off top | 0.003 |
| alpha4 | AA | Slope of reflectivity bottom | 4.38 |
| m4 | 1 | m-value of material, bottom. | 2 |
| W4 | AA-1 | Width of supermirror cut-off bottom | 0.003 |
| wavy_z | deg | Waviness in the z-(flight-)direction | 0 |
| wavy_xy | deg | Waviness in the transverse direction | 0 |

## Links

- [Source code](Guide_wavy.comp) for `Guide_wavy.comp`.

---

*Generated on mcstas 3.99.99.*