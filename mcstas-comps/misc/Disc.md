# The `Disc` Component

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
| radius | m | Outer radius of geometry in (x,z) plane | 0 |
| xwidth | m | Horiz. dimension of geometry | 0 |
| yheight | m | Vert. dimensuon of geometry | 0 |
| zdepth | m | Depth dimension of geometry | 0 |
| nx | 1 | x-comp of orientation vector | 0 |
| ny | 1 | y-comp of orientation vector | 1 |
| nz | 1 | z-comp of orientation vector | 0 |

## Links

- [Source code](Disc.comp) for `Disc.comp`.
- mcdoc page of <a href="Shape.html">Shape</a></b> component

---

*Generated on mcstas 3.99.99.*