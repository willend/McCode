# The `Annulus` Component

*McStas: A geometric shape without effect on neutron, for instrument display purpose.*

## Identification

- **Site:** 
- **Author:** E. Farhi
- **Origin:** ILL
- **Date:** June 23rd 2009

## Description

```text
An inactive geometrical shape (annulus), for drawing purposes only.
Derived from the <b><a href="Shape.html">Shape</a></b> component

Example: Annulus(radius=0.05, yheight=0.1)
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| outer_radius | m | Outer radius of geometry in (x,z) plane | 0 |
| inner_radius | m | Inner radius of geometry in (x,z) plane | 0 |
| radius | m | Outer radius of geometry in (x,z) plane | 0 |
| xwidth | m | Horiz. dimension of geometry as a width | 0 |
| yheight | m | Vert. | 0 |
| zdepth | m | Depth dimension of geometry | 0 |

## Links

- [Source code](Annulus.comp) for `Annulus.comp`.
- mcdoc page of <a href="Shape.html">Shape</a></b> component

---

*Generated on mcstas 3.99.99.*