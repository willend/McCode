# The `Pol_triafield` Component

*McStas: Constant magnetic field in a isosceles triangular coil*

## Identification

- **Site:** 
- **Author:** Morten Sales, based on Pol_constBfield by Peter Christiansen
- **Origin:** Helmholtz-Zentrum Berlin
- **Date:** 2013

## Description

```text
Rectangular box with constant B field along y-axis (up) in a isosceles triangle.
There is a guide (or precession) field as well. It is along y in the entire rectangular box.
A neutron hitting outside the box opening or the box sides is absorbed.


__________________
|        /\        |
| Bguide/  \Bguide |      x
|      /    \      |      ^
|     /      \     |      |
|    /   B    \    |      |-----> z
|   /   and    \   |
|  /   Bguide   \  |
| /              \ |
|/________________\|

The angle of the inclination of the triangular field boundary is given by the arctangent to xwidth/(0.5*zdepth)

This component does NOT take gravity into account.

Example: Pol_triafield(xwidth=0.1, yheight=0.1, zdepth=0.2, B=1e-3, Bguide=0.0)
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| **xwidth** | m | Width of opening |  |
| **yheight** | m | Height of opening |  |
| **zdepth** | m | zdepth of field |  |
| B | T | Magnetic field along y-direction inside triangle | 0 |
| Bguide | T | Magnetic field along y-direction inside entire box | 0 |

## Links

- [Source code](Pol_triafield.comp) for `Pol_triafield.comp`.

---

*Generated on mcstas 3.99.99.*