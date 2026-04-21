# The `Rotator` Component

*McStas: A rotative frame along vertical axis*

## Identification

- **Site:** 
- **Author:** Emmanuel Farhi
- **Origin:** <a href="http://www.ill.fr">ILL</a>
- **Date:** June 20th 2013

## Description

```text
All components positioned after this one are rotating at frequency 'nu' with
phase 'phase'. Use the Derotator component to put back the model steady.
The rotation is performed w.r.t. the position of the component, along a chosen
main axis (use directon=1 for x, direction=2 for y, direction=3 for z).

Default rotation axis is vertical axis / 'y'.

Example:
R=Rotator(nu=14, phase=0)
...
DR=Derotator(rotator=R)
AT (0,0,0) RELATIVE R
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| nu | Hz | Rotation frequency (round/s) in the rotating option (vertical axis) | 0 |
| phase | deg | Phase shift | 0 |
| direction | 1 | Rotation axis selection 1=x, 2=y, 3=z | 2 |

## Links

- [Source code](Rotator.comp) for `Rotator.comp`.

---

*Generated on mcstas 3.99.99.*