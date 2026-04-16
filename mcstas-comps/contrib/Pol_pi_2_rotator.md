# The `Pol_pi_2_rotator` Component

*McStas: Ideal &pi;/2-rotator*

## Identification

- **Site:** 
- **Author:** Erik Knudsen (erkn@fysik.dtu.dk)
- **Origin:** Risoe
- **Date:** 8/4-2008

## Description

```text
Simple, idelized, component that turns the polarization exactly &pi;/2 around the specified vector
vector (rx,ry,rx).
The geometry of the component is realized as a box, where the the spin is rotated at the z-midpoint.
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| xwidth | m | width of the component | 0.1 |
| yheight | m | height of the component | 0.1 |
| zdepth | m | thickness of the component | 0.01 |
| rx |  | x-component of the rotation axis | 0 |
| ry |  | y-component of the rotation axis | 0 |
| rz |  | z-component of the rotation axis | 1 |

## Links

- [Source code](/Users/peterwillendrup/Projects/willend-McCode/mcstas-comps/contrib/Pol_pi_2_rotator.comp) for `Pol_pi_2_rotator.comp`.

---

*Generated on mcstas 3.99.99.*