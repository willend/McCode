# The `Set_pol` Component

*McStas: (Unphysical) way of setting the polarization.*

## Identification

- **Site:** 
- **Author:** Peter Christiansen
- **Origin:** Risoe
- **Date:** August 2006

## Description

```text
This component has no physical size (like Arm - also drawn that
way), but is used to set the polarisation in one of four ways:
1) (randomOn=0, normalize=0) Hardcode the polarisation to the vector (px, py, pz)
2) (randomOn!=0, normalize!=0) Set the polarisation to a random vector on the unit sphere
3) (randomOn!=0, normalize=0) Set the polarisation to a radnom vector within the unit sphere
4) (randomOn=0, normalize!=0) Hardcode the polarisation to point in the direction of (px,py,pz) but with polarization=1.
Example: Set_pol(px=0, py=-1, pz=0)
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| px | 1 | X-component of polarisation vector (can be negative) | 0 |
| py | 1 | Y-component of polarisation vector (can be negative) | 0 |
| pz | 1 | Z-component of polarisation vector (can be negative) | 0 |
| randomOn | 1 | Generate random values if randomOn!=0. | 0 |
| normalize | 1 | Normalize the polarization vector to unity length. | 0 |

## Links

- [Source code](/Users/peterwillendrup/Projects/willend-McCode/mcstas-comps/optics/Set_pol.comp) for `Set_pol.comp`.

---

*Generated on mcstas 3.99.99.*