# The `Mirror_Elliptic_Bispectral` Component

*McStas: Single mirror plate that is curved and fits into an elliptic guide.*

## Identification

- **Site:** 
- **Author:** Henrik Jacobsen
- **Origin:** RNBI
- **Date:** April 2012

## Description

```text

```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| reflect | q(Angs-1) R(0-1) | (str)  Name of relfectivity file. Format | 0 |
| **focus_start_w** | m | Horizontal position of first focal point of ellipse in ABSOLUTE COORDINATES |  |
| **focus_end_w** | m | Horizontal position of second focal point of ellipse in ABSOLUTE COORDINATES |  |
| **focus_start_h** | m | Vertical position of first focal point of ellipse in ABSOLUTE COORDINATES |  |
| **focus_end_h** | m | VErtical position of second focal point of ellipse in ABSOLUTE COORDINATES |  |
| **mirror_start** | m | start of mirror in ABSOLUTE COORDINATES |  |
| **m** |  | m-value of material |  |
| **smallaxis_w** | m | Small-axis dimension of horizontal ellipse |  |
| **smallaxis_h** | m | Small-axis dimension of vertical ellipse |  |
| **length** | m | the length of the mirror |  |
| transmit | 0/1 | 0: non reflected neutrons are absorbed. 1: non reflected neutrons pass through | 0 |
| substrate_thickness | m | thickness of substrate (for absorption) | 0.0005 |
| coating_thickness | m | thickness of coating (for absorption) | 10e-6 |

## Links

- [Source code](Mirror_Elliptic_Bispectral.comp) for `Mirror_Elliptic_Bispectral.comp`.

---

*Generated on mcstas 3.99.99.*