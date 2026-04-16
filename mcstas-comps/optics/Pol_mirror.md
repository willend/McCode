# The `Pol_mirror` Component

*McStas: Polarising mirror.*

## Identification

- **Site:** 
- **Author:** Peter Christiansen
- **Origin:** RISOE
- **Date:** July 2006

## Description

```text
This component models a rectangular infinitely thin mirror.
For an unrotated component, the mirror surface lies in the Y-Z
plane (ie. parallel to the beam).
It relies on similar physics as the Monochromator_pol.
The reflectivity function (see e.g. share/ref-lib for examples) and parameters
are passed to this component to give a bigger freedom.
The up direction is hardcoded to be along the y-axis (0, 1, 0)
IMPORTANT: At present the component only works correctly for polarization along the up/down
direction and for completely unpolarized beams, i.e. sx=sy=sz=0 for all rays.

For now we assume:
P(Transmit|Q) = 1 - P(Reflect|Q)
i.e. NO ABSORPTION!


The component can both reflect and transmit neutrons with a respective proportion
depending on the p_reflect parameter:
p_reflect=-1 Reflect and transmit (proportions given from reflectivity) [default]
p_reflect=1 Only handle reflected events
p_reflect=0 Only handle transmitted events (reduce weight)
p_reflect=0-1 Both transmit and reflect with fixed statistics proportions

The parameters can either be
double pointer initializations (e.g. {R0, Qc, alpha, m, W})
or table names (e.g."supermirror_m2.rfl" AND useTables=1).
NB! This might cause warnings by the compiler that can be ignored.

Examples:
Reflection function parametrization
Pol_mirror(zwidth = 0.40, yheight = 0.40, rUpFunc=StdReflecFunc, rUpPar={1.0, 0.0219, 6.07, 2.0, 0.003})

Table function
Pol_mirror(zwidth = 0.40, yheight = 0.40, rUpFunc=TableReflecFunc, rUpPar="supermirror_m2.rfl", rDownFunc=TableReflecFunc, rDownPar="supermirror_m3.rfl", useTables=1)

See also the example instrument Test_Pol_Mirror (under tests).

GRAVITY: YES

%BUGS
NO ABSORPTION
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| rUpPar | 1 | Parameters for rUpFunc | {0.99,0.0219,6.07,2.0,0.003} |
| rDownPar | 1 | Parameters for rDownFunc | {0.99,0.0219,6.07,2.0,0.003} |
| rUpData | str | Mirror Reflectivity data file for spin up | "" |
| rDownData | str | Mirror Reflectivity data file for spin down | "" |
| p_reflect | 1 | Proportion of reflected events. Use 0 to only get the transmitted beam, and 1 to get only the reflected beam. Use -1 to use the mirror reflectivity. This value is purely computational and is not related to the actual reflectivity | -1 |
| **zwidth** | m | Width of the mirror |  |

## Links

- [Source code](/Users/peterwillendrup/Projects/willend-McCode/mcstas-comps/optics/Pol_mirror.comp) for `Pol_mirror.comp`.

---

*Generated on mcstas 3.99.99.*