# The `Exact_radial_coll` Component

*McStas: An exact radial Soller collimator.*

## Identification

- **Site:** 
- **Author:** Roland Schedler <roland.schedler at hmi.de>
- **Origin:** HMI
- **Date:** October 2006

## Description

```text
Radial Soller collimator with rectangular opening, specified length and
specified foil thickness.
The collimator is made of many trapezium shaped nslit stacked radially.
The nslit are separated by absorbing foils, the whole stuff is inside
an absorbing housing.
The component should be positioned at the radius center. The model is exact.
The neutron beam outside the collimator area is transmitted unaffected.

Example: Exact_radial_coll(theta_min=-5, theta_max=5, nslit=100,
radius=1.0, length=.3, h_in=.2, h_out=.3, d=0.0001)
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| theta_min | deg | Minimum Theta angle for the radial setting | -5 |
| theta_max | deg | Maximum Theta angle for the radial setting | 5 |
| nslit | 1 | Number of channels in the theta range | 100 |
| radius | m | Inner radius (focus point to foil start point). | 1.0 |
| length | m | Length of the foils / collimator | .5 |
| h_in | m | Input  window height | .3 |
| h_out | m | Output window height | .4 |
| d | m | Thickness of the absorbing foils | 0.0001 |
| verbose | 0/1 | Gives additional information | 0 |

## Links

- [Source code](/Users/peterwillendrup/Projects/willend-McCode/mcstas-comps/contrib/Exact_radial_coll.comp) for `Exact_radial_coll.comp`.

---

*Generated on mcstas 3.99.99.*