# The `SANS_DebyeS` Component

*McStas: Sample for Small Angle Neutron Scattering, Debye-Scherrer Ring*

## Identification

- **Site:** 
- **Author:** Henrich Frielinghaus
- **Origin:** FZ-Juelich/FRJ-2/IFF/KWS-2
- **Date:** Sept 2004

## Description

```text
Debye-Scherrer Ring: Model for highly ordered diblock copolymer.
This example is highly simple.
Multiple scattering neglected, but could be incorporated.
Sample that only produces a DebyeSherrer ring.
Advantages:  Transmitted beam is simulated.
Intensities still in flux units.
Minor point: Absolute scattering probability given by transmission.

Sample components leave the units of flux for the probability
of the individual paths. That is more consitent than the
Sans_spheres routine. Furthermore one can simulate the
transmitted beam. This allows to determine the needed size of
the beam stop. Only absorption has not been included yet to
these sample-components. But thats really nothing.

Example: SANS_DebyeS(transm=0.5, qDS=0.008, xwidth=0.01, yheight=0.01, zdepth=0.001)
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| transm | 1 | coherent transmission of sample for the optical path "zdepth" | 0.5 |
| qDS | AA-1 | Scattering vector of Debye-Sherrer ring | 0.008 |
| xwidth | m | horiz. dimension of sample, as a width (m) | 0.01 |
| yheight | m | vert.. dimension of sample, as a height (m) | 0.01 |
| zdepth | m | thickness of sample (m) | 0.001 |

## Links

- [Source code](/Users/peterwillendrup/Projects/willend-McCode/mcstas-comps/contrib/SANS_DebyeS.comp) for `SANS_DebyeS.comp`.
- Sans_spheres component

---

*Generated on mcstas 3.99.99.*