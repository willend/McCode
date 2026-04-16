# The `Undulator` Component

*McXtrace: Model of an undulator source*

## Identification

- **Site:** 
- **Author:** Erik B. Knudsen
- **Origin:** DTU Physics
- **Date:** May, 2013.

## Description

```text
A undulator source model based on the derivation by K.J. Kim, AIP, conf. proc., 184, 1989. doi:10.1063/1.38046.

SOLEIL_PX2a U24
Example: Undulator( E0=12.65, dE=1, Ee=2.75, dEe=0.001, Ie=0.5, K=1.788, Nper=80,
lu=24e-3, sigey=9.3e-6, sigex=215.7e-6, sigepx=29.3e-6, sigepy=4.2e-6,
dist=29.5, E1st=12.400 )
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| E0 | keV | Center of emitted energy spectrum. | 0 |
| dE | keV | Half-width of emitted energy spectrum. | 0 |
| phase | rad | Initial phase of radiation. | 0 |
| randomphase | 0/1 | If !=0 phase will be random (I.e. the emitted radiation is completely incoherent). | 1 |
| Ee | GeV | Storage ring electron energy [typically a few GeV). | 2.4 |
| dEe | percent | Relative electron energy beam spread (sigma/Ee). | 0 |
| Ie | A | Ring current. | 0.4 |
| B | T | Peak magnet field strength. Overrides K. | 0 |
| K | 1 | Dimensionless deflection undulator parameter. When K >> 1 (ie B*lu is large) you get a wiggler. | 0 |
| Nper | int | Number of magnetic periods in the undulator. | 1 |
| lu | m | Magnetic period length of the undulator aka lambda_u. | 16e-3 |
| sigey | m | Electron ring beam size in vertical plane (rms). | 0 |
| sigex | m | Electron ring beam size in horizontal plane (rms). | 0 |
| sigepx | rad | Electron ring beam horizontal divergence (rms). | 0 |
| sigepy | rad | Electron ring beam vertical divergence (rms). | 0 |
| focus_xw | m | Width of target window. | 0 |
| focus_yh | m | Height of target window. | 0 |
| dist | m | Distance from source plane to target window along the optical axis. | 1 |
| quick_integ | 0/1 | If nonzero, use faster (but less accurate) integration scheme. | 0 |
| E1st | keV | Energy of the fundmental (1st) undulator harmonic. | 0 |
| verbose | 0/1 | If nonzero, output extra information. | 0 |
| Br | T | Remanent field (1.35T for Nd2Fe14B) for gap estimate | 1.35 |

## Links

- [Source code](/Users/peterwillendrup/Projects/willend-McCode/mcxtrace-comps/sources/Undulator.comp) for `Undulator.comp`.

---

*Generated on mcxtrace 3.99.99.*