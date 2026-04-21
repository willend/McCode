# The `FermiChopper_ILL` Component

*McStas: Fermi Chopper with rotating frame.*

## Identification

- **Site:** 
- **Author:** M. Poehlmann, C. Carbogno, H. Schober, E. Farhi
- **Origin:** ILL Grenoble / TU Muenchen
- **Date:** May 2002

## Description

```text
Models a Fermi chopper with optional supermirror coated blades
supermirror facilities may be disabled by setting m = 0, R0=0
Slit packages are straight. Chopper slits are separated by an infinitely
thin absorbing material. The effective transmission (resulting from fraction
of the transparent material and its transmission) may be specified.
The chopper slit package width may be specified through the total width 'xwidth'
of the full package or the width 'w' of each single slit. The other parameter
is calculated by: xwidth = nslit*w.

Example:
FermiChopper_ILL(phase=-50.0, radius=0.04, nu=100,
yheight=0.08, w=0.00022475, nslit=200.0, R0=0.0,
Qc=0.02176, alpha=2.33, m=0.0, length=0.012, eff=0.95,
zero_time=0)

Markus Poehlmann     <Markus.Poehlmann@ph.tum.de>
Christian Carbogno   <carbogno@ph.tum.de>
and Helmut Schober   <schober@ill.fr>

%VALIDATION
Apr 2005: extensive external test, most problems solved (cf. 'Bugs')
Validated by: K. Lieutenant

limitations:
no blade width used

%BUGS
- overestimates peak width for long wavelengths
- does not give the right pulse position, shape and width for slit widths below 0.1 mm
- fails sometimes when using MPI
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| phase | deg | chopper phase at t=0 | 0 |
| radius | m | chopper cylinder radius | 0.04 |
| nu | Hz | chopper frequency | 100 |
| yheight | m | Height of chopper | 0.08 |
| w | m | width of one chopper slit | 0.00022475 |
| nslit | 1 | number of chopper slits | 200.0 |
| R0 | 1 | low-angle reflectivity | 0.0 |
| Qc | AA-1 | critical scattering vector | 0.02176 |
| alpha | AA | slope of reflectivity | 2.33 |
| m | 1 | m-value of material. Zero means completely absorbing. | 0.0 |
| W | AA-1 | width of supermirror cut-off | 2e-3 |
| length | m | channel length of the Fermi chopper | 0.012 |
| eff | 1 | efficiency = transmission x fraction of transparent material | 0.95 |
| zero_time | 1 | set time to zero: 0: no  1: once per half cycle | 0 |
| xwidth | m | optional total width of slit package | 0 |
| verbose | 1 | optional flag to display component statistics, use 1 or 3 (debuging) | 0 |

## Links

- [Source code](FermiChopper_ILL.comp) for `FermiChopper_ILL.comp`.

---

*Generated on mcstas 3.99.99.*