# The `V_selector` Component

*McStas: Velocity selector.*

## Identification

- **Site:** 
- **Author:** Kim Lefmann
- **Origin:** Risoe
- **Date:** Nov 25, 1998

## Description

```text
Velocity selector consisting of rotating Soller-like blades
defining a helically twisted passage.
Geometry defined by two identical, centered apertures at 12 o'clock
position, Origo is at the centre of the selector (input is at -zdepth/2).
Transmission is analytical assuming a continuous source.

Example: V_selector(xwidth=0.03, yheight=0.05, zdepth=0.30, radius=0.12, alpha=48.298, length=0.25, d=0.0004, nu=20000, nslit=72)
These are values for the D11@ILL Dornier 'Dolores' Velocity Selector (NVS 023)

%VALIDATION
Jun 2005: extensive external test, no problems found
Validated by: K. Lieutenant
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| xwidth | m | Width of entry aperture | 0.03 |
| yheight | m | Height of entry aperture | 0.05 |
| zdepth | m | Distance between apertures, for housing containing the rotor | 0.30 |
| radius | m | Height from aperture centre to rotation axis | 0.12 |
| alpha | deg | Twist angle along the cylinder | 48.298 |
| length | m | Length of cylinder/rotor (less than zdepth) | 0.25 |
| d | m | Thickness of blades | 0.0004 |
| nu | Hz | Cylinder rotation speed, counter-clockwise, which is ideally 3956*alpha*DEG2RAD/2/PI/lambda/length | 300 |
| nslit | 1 | Number of Soller blades | 72 |

## Links

- [Source code](/Users/peterwillendrup/Projects/willend-McCode/mcstas-comps/optics/V_selector.comp) for `V_selector.comp`.

---

*Generated on mcstas 3.99.99.*