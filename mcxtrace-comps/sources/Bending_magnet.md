# The `Bending_magnet` Component

*McXtrace: Model of a bending magnet source*

## Identification

- **Site:** 
- **Author:** Erik B. Knudsen
- **Origin:** DTU Physics
- **Date:** May, 2013.

## Description

```text
A source model based on the derivation from B.D. Patterson, Am. J. Phys. 79, 1046 (2011); doi: 10.1119/1.3614033

Example: Bending_magnet(
E0 = 14, dE = 7, Ee = 2.75,
Ie = 0.5, B = 1.72, sigey=9.3e-6, sigex=215.7e-6)
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| E0 | keV | Center of emitted energy spectrum (overrides lambda0) | 0 |
| dE | keV | Half-width of emitted energy spectrum | 0 |
| lambda0 | AA | Center of emitted wavelength spectrum | 0 |
| dlambda | AA | Half-width of emitted wavelength spectrum | 0 |
| phase | rad | Initial phase of radiation. | 0 |
| randomphase | 0/1 | If !=0 phase will be random (I.e. the emitted radiation is completely incoherent) | 1 |
| Ee | GeV | Storage ring electron energy (typically a few GeV) | 2.4 |
| Ie | A | Ring current | 0.4 |
| B | T | Magnet field strength | 1.6 |
| sigey | m | Electron ring beam size in vertical plane (rms) | 0 |
| sigex | m | Electron ring beam size in horizontal plane (rms) | 0 |
| focus_xw | m | Width of target window | 0 |
| focus_yh | m | Height of traget window | 0 |
| dist | m | Distance from source plane to target window along the optical axis | 1 |
| gauss_t | 0/1 | If 0 the target window will be sampled uniformly and the weight adjusted accordingly, otherwise we will use a gaussian sampling scheme | 0 |

## Links

- [Source code](/Users/peterwillendrup/Projects/willend-McCode/mcxtrace-comps/sources/Bending_magnet.comp) for `Bending_magnet.comp`.

---

*Generated on mcxtrace 3.99.99.*