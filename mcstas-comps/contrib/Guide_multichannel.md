# The `Guide_multichannel` Component

*McStas: Multichannel neutron guide with semi-transparent blades.
Derived from Guide_channeled by Christian Nielsen.
Allows to simulate bi-spectral extraction optics.*

## Identification

- **Site:** 
- **Author:** Jan Saroun (saroun@ujf.cas.cz)
- **Origin:** Nuclear Physics Institute, CAS, Rez
- **Date:** 17.3.2022

## Description

```text
Models a rectangular guide with equidistant vertical blades of finite thickness.
The blades material can be either fully absorbing or semi-transparent. The absorption
coefficient is wavelength dependent according to the semi-empirical model used
e.g. in J. Baker et al., J. Appl. Cryst. 41 (2008) 1003 or
A. Freund, Nucl. Instr. Meth. A 213 (1983) 495.
Data are provided for Si and Al2O3.

All walls are flat, curvature is not implemented (may be added as a future upgrade)
Tapering is possible by setting different entry ad exit dimensions.
Different guide coating can be set for vertical and horizontal mirrors.
For transparent walls, neutrons are alloed to migrate between channels and to
propagate through the blades.

The model is almost equivalent to the GUIDE component in SIMRES (http://neutron.ujf.cas.cz/restrax)
when used with zero curvature and type set to "guide or bender".
The features from SIMRES not included in this McSas model are:
- has a more conservative model for absorption in blades: events above r(m<mc) are automatically ABSORBED.
- defines waviness
- works with bent geometry
- works with gravity
- allows for 2D grid of blades

bug fix 24/3/2017: incorrect handling of transition into blades = no transmission
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| **w1** | m | Width at the guide entry |  |
| **h1** | m | Height at the guide entry |  |
| w2 | m | Width at the guide exit | 0 |
| h2 | m | Height at the guide exit | 0 |
| **l** | m | Length of guide |  |
| R0 | 1 | Low-angle reflectivity | 0.995 |
| Qc | AA-1 | Critical scattering vector | 0 |
| alpha | AA | Slope of reflectivity | 0 |
| m | 1 | m-value of material. Zero means completely absorbing. | 0 |
| nslit | 1 | Number of channels in the guide (>= 1) | 1 |
| dlam | m | Thickness of lamellae | 0.0005 |
| Qcx | AA-1 | Critical scattering vector for left and right vertical mirrors in each channel | 0.0218 |
| Qcy | AA-1 | Critical scattering vector for top and bottom mirrors | 0.0218 |
| alphax | AA | Slope of reflectivity for left and right vertical mirrors in each channel | 4.38 |
| alphay | AA | Slope of reflectivity for top and bottom mirrors | 4.38 |
| W | AA-1 | Width of supermirror cut-off for all mirrors | 0.003 |
| mx | 1 | m-value of material for left and right vertical mirrors in each channel. Zero means completely absorbing. | 1 |
| my | 1 | m-value of material for top and bottom mirrors. Zero means completely absorbing. | 1 |
| mater | string | "Si", "Al2O3", or "absorb" (default) | "absorb" |

## Links

- [Source code](Guide_multichannel.comp) for `Guide_multichannel.comp`.

---

*Generated on mcstas 3.99.99.*