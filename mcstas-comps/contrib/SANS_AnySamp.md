# The `SANS_AnySamp` Component

*McStas: Sample for Small Angle Neutron Scattering. To be customized.*

## Identification

- **Site:** 
- **Author:** Henrich Frielinghaus
- **Origin:** FZ-Juelich/FRJ-2/IFF/KWS-2
- **Date:** Sept 2004

## Description

```text
Sample for Small Angle Neutron Scattering.
May be customized for Any Sample model.
Copy this component and modify it to your needs.
Just give shape of scattering function.
Normalization of scattering will be done in INITIALIZE.

Some remarks:
Scattering function should be a defined the same way in INITIALIZE and TRACE sections
There exist maybe better library functions for the integral.

Here for comparison: Guinier.
Transmitted paths set to 3% of all paths. In this simulation method paths are
well distributed among transmission and scattering (equally in Q-space).

Sample components leave the units of flux for the probability
of the individual paths. That is more consitent than the
Sans_spheres routine. Furthermore one can simulate the
transmitted beam. This allows to determine the needed size of
the beam stop. Only absorption has not been included yet to
these sample-components. But thats really nothing.

Example: SANS_AnySamp(transm=0.5, Rg=100, qmax=0.03, xwidth=0.01, yheight=0.01, zdepth=0.001)
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| transm | 1 | coherent transmission of sample for the optical path "zdepth" | 0.5 |
| Rg | Angs | Radius of Gyration | 100 |
| qmax | AA-1 | Maximum scattering vector | 0.03 |
| xwidth | m | horizontal dimension of sample, as a width | 0.01 |
| yheight | m | vertical dimension of sample, as a height | 0.01 |
| zdepth | m | thickness of sample | 0.001 |

## Links

- [Source code](SANS_AnySamp.comp) for `SANS_AnySamp.comp`.
- Sans_spheres component

---

*Generated on mcstas 3.99.99.*