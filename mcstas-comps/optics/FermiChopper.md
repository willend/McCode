# The `FermiChopper` Component

*McStas: Fermi Chopper with rotating frame.*

## Identification

- **Site:** 
- **Author:** M. Poehlmann, C. Carbogno, H. Schober, E. Farhi
- **Origin:** ILL Grenoble / TU Muenchen
- **Date:** May 2002

## Description

```text
Models a fermi chopper with optional supermirror coated blades
supermirror facilities may be disabled by setting m = 0, R0=0
Slit packages are straight. Chopper slits are separated by an infinitely
thin absorbing material. The effective transmission (resulting from fraction
of the transparent material and its transmission) may be specified.
The chopper slit package width may be specified through the total width 'xwidth'
of the full package or the width 'w' of each single slit. The other parameter
is calculated by: xwidth = nslit*w. The slit package may be made curved and use
super-mirror coating.

Example:
FermiChopper(phase=-50.0, radius=0.04, nu=100, yheight=0.08, w=0.00022475, nslit=200.0, R0=0.0, Qc=0.02176, alpha=2.33, m=0.0, length=0.012, eff=0.95)

%VALIDATION
Apr 2005: extensive external test, most problems solved (cf. 'Bugs')
Validated by: K. Lieutenant, E. Farhi

limitations:
no absorbing blade width used
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| phase | deg | chopper phase at t=0 | 0 |
| radius | m | chopper cylinder radius | 0.04 |
| nu | Hz | chopper frequency. Omega=2*PI*nu in rad/s, nu*60 in rpm. Positive value corresponds to a counter-clockwise rotation around y. | 100 |
| w | m | width of one chopper slit | 0.00022475 |
| nslit | 1 | number of chopper slits | 200 |
| R0 | 1 | low-angle reflectivity | 0.0 |
| Qc | AA-1 | critical scattering vector | 0.02176 |
| alpha | AA | slope of reflectivity | 2.33 |
| m | 1 | m-value of material. Zero means completely absorbing. | 0.0 |
| W | AA-1 | width of supermirror cut-off | 2e-3 |
| length | m | channel length of the Fermi chopper | 0.012 |
| eff | 1 | efficiency = transmission x fraction of transparent material | 0.95 |
| zero_time | 1 | set time to zero: 0=no, 1=once per half cycle, 2=auto adjust phase | 0 |
| xwidth | m | optional total width of slit package | 0 |
| verbose | 1 | set to 1,2 or 3 gives debugging information | 0 |
| yheight | m | height of slit package | 0.08 |
| curvature | m-1 | Curvature of slits (1/radius of curvature). | 0 |
| delay | s | sets phase so that transmision is centered on 'delay' | 0 |

## Links

- [Source code](/Users/peterwillendrup/Projects/willend-McCode/mcstas-comps/optics/FermiChopper.comp) for `FermiChopper.comp`.
- <a href="Vitess_ChopperFermi.html">Vitess_ChopperFermi</a> component by
- G. Zsigmond, imported from Vitess by K. Lieutenant.

---

*Generated on mcstas 3.99.99.*