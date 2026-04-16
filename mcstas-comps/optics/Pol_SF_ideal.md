# The `Pol_SF_ideal` Component

*McStas: Pol_SF_ideal component*

## Identification

- **Site:** 
- **Author:** 
- **Origin:** 
- **Date:** 

## Description

```text
This component simply mirrors the polarization vector of the neutron
ray in the plane through (0,0,0) with normal nx,ny,nz.
The flipper is surrounded by a perfectly absorbing box. Neutron rays not hitting
the box are left untouched.
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| nx |  | x-component of the normal vector of the flipping plane. | 0 |
| ny |  | y-component of the normal vector of the flipping plane. | 1 |
| nz |  | z-component of the normal vector of the flipping plane. | 0 |
| xwidth | m | width of the spin flipper. | 0.1 |
| yheight | m | height of the spin flipper. | 0.1 |
| zdepth | m | length of the spin flipper. | 0.1 |

## Links

- [Source code](/Users/peterwillendrup/Projects/willend-McCode/mcstas-comps/optics/Pol_SF_ideal.comp) for `Pol_SF_ideal.comp`.

---

*Generated on mcstas 3.99.99.*