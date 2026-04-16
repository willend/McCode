# The `Pol_constBfield` Component

*McStas: Constant magnetic field.*

## Identification

- **Site:** 
- **Author:** Peter Christiansen
- **Origin:** RISOE
- **Date:** July 2006

## Description

```text
Rectangular box with constant B field along y-axis (up). The
component can be rotated to make either a guide field or a spin
flipper. A neutron hitting outside the box opening or the box sides
is absorbed.

Example: Pol_constBfield(xwidth=0.1, yheight=0.1, zdepth=0.2, fliplambda=5.0)
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| **xwidth** | m | Width of opening |  |
| **yheight** | m | Height of opening |  |
| **zdepth** | m | Length of field |  |
| B | Gauss | Magnetic field along y-direction | 0 |
| fliplambda | AA | lambda for calculating B field | 0 |
| flipangle | deg | Angle flipped for lambda = fliplambda fliplambda and flipangle overrides B so a neutron with s= (1, 0, 0) and v = (0, 0, v(fliplambda)) will have s =(cos(flipangle), sin(flipangle), 0) after the section. | 180 |

## Links

- [Source code](/Users/peterwillendrup/Projects/willend-McCode/mcstas-comps/optics/Pol_constBfield.comp) for `Pol_constBfield.comp`.

---

*Generated on mcstas 3.99.99.*