# The `Source_Maxwell_3` Component

*McStas: Source with up to three Maxwellian distributions*

## Identification

- **Site:** 
- **Author:** Kim Lefmann
- **Origin:** Risoe
- **Date:** March 2001

## Description

```text
A parametrised continuous source for modelling a (cubic) source
with (up to) 3 Maxwellian distributions.
The source produces a continuous spectrum.
The sampling of the neutrons is uniform in wavelength.

Units of flux: neutrons/cm^2/second/ster
(McStas units are in general neutrons/second)

Example:  PSI cold source T1=150.42 K / 2.51 AA     I1 = 3.67 E11
T2=38.74 K / 4.95 AA      I2 = 3.64 E11
T3=14.84 K / 9.5 AA       I3 = 0.95 E11
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| size | m | Edge of cube shaped source (for backward compatibility) | 0 |
| yheight | m | Height of rectangular source | 0 |
| xwidth | m | Width of rectangular source | 0 |
| **Lmin** | AA | Lower edge of lambda distribution |  |
| **Lmax** | AA | Upper edge of lambda distribution |  |
| **dist** | m | Distance from source to focusing rectangle; at (0,0,dist) |  |
| **focus_xw** | m | Width of focusing rectangle |  |
| **focus_yh** | m | Height of focusing rectangle |  |
| **T1** | K | 1st temperature of thermal distribution |  |
| T2 | K | 2nd temperature of thermal distribution | 300 |
| T3 | K | 3nd temperature of  - - - | 300 |
| **I1** | 1/(cm**2*st) | flux, 1 (in flux units, see above) |  |
| I2 | 1/(cm**2*st) | flux, 2 (in flux units, see above) | 0 |
| I3 | 1/(cm**2*st) | flux, 3  - - - | 0 |
| target_index | 1 | relative index of component to focus at, e.g. next is +1 this is used to compute 'dist' automatically. | 1 |
| lambda0 | AA | Mean wavelength of neutrons. | 0 |
| dlambda | AA | Wavelength spread of neutrons. | 0 |

## Links

- [Source code](/Users/peterwillendrup/Projects/willend-McCode/mcstas-comps/sources/Source_Maxwell_3.comp) for `Source_Maxwell_3.comp`.

---

*Generated on mcstas 3.99.99.*