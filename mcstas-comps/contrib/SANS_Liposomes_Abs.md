# The `SANS_Liposomes_Abs` Component

*McStas: Solid dilute monodisperse spheres sample with transmitted beam for Small Angle Neutron Scattering.*

## Identification

- **Site:** 
- **Author:** Wim Bouwman, Delft University of Technology
- **Origin:** TUDelft
- **Date:** Aug 2012

## Description

```text
Sample for Small Angle Neutron Scattering.
Modified from the Any Sample model.
Normalization of scattering is done in INITIALIZE.
Some elements of Sans_spheres have been re-used

Some remarks:
Scattering function should be a defined the same way in INITIALIZE and TRACE sections
There exist maybe better library functions for the integral.

Transmitted paths set to 50% of all paths to be optimised for SESANS. In this simulation method paths are
well distributed among transmission and scattering (equally in Q-space).

Sample components leave the units of flux for the probability
of the individual paths. That is more consitent than the
Sans_spheres routine. Furthermore one can simulate the
transmitted beam. This allows to determine the needed size of
the beam stop. Absorption is included to
these sample-components.

Example: SANS_Spheres_Abs(R=100, Phi=1e-3, Delta_rho=0.6, sigma_a = 50, qmax=0.03, xwidth=0.01, yheight=0.01, zthick=0.001)
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| R | AA | Radius of scattering hard spheres | 100 |
| dR |  |  | 0.0 |
| Phi | 1 | Particle volume fraction | 1e-3 |
| Delta_rho | fm/AA^3 | Excess scattering length density | 0.6 |
| sigma_a | m^-1 | Absorption cross section density at 2200 m/s | 0.50 |
| qmax | AA-1 | Maximum scattering vector (typically 10/R to observe the 3rd ring) | 0.03 |
| xwidth | m | horiz. dimension of sample, as a width | 0.01 |
| yheight | m | vert.. dimension of sample, as a height | 0.01 |
| zthick | m | thickness of sample | 0.001 |
| dbilayer |  |  | 35 |

## Links

- [Source code](SANS_Liposomes_Abs.comp) for `SANS_Liposomes_Abs.comp`.
- Sans_spheres component
- SANS_AnySamp component

---

*Generated on mcstas 3.99.99.*