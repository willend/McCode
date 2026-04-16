# The `Mirror_Curved_Bispectral` Component

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
| **focus_s** | m | first focal point of ellipse in ABSOLUTE COORDINATES |  |
| **focus_e** | m | second focal point of ellipse in ABSOLUTE COORDINATES |  |
| **mirror_start** | m | start of mirror in ABSOLUTE COORDINATES |  |
| **guide_start** | m | start of guide in ABSOLUTE COORDINATES |  |
| **yheight** | m | the height of the mirror when not in the guide |  |
| **smallaxis** | m | the smallaxis of the guide |  |
| **length** | m | the length of the mirror |  |
| **m** |  | m-value of material |  |
| transmit | 0/1 | 0: non reflected neutrons are absorbed. 1: non reflected neutrons pass through | 0 |
| substrate_thickness | m | thickness of substrate (for absorption) | 0.0005 |
| coating_thickness | m | thickness of coating (for absorption) | 10e-6 |
| theta_1 | deg | angle of mirror wrt propagation direction at start of mirror | 1.25 |
| theta_2 | deg | angle of mirror wrt propagation direction at center of mirror | 1.25 |
| theta_3 | deg | angle of mirror wrt propagation direction at end of mirror | 1.25 |

## Links

- [Source code](/Users/peterwillendrup/Projects/willend-McCode/mcstas-comps/contrib/Mirror_Curved_Bispectral.comp) for `Mirror_Curved_Bispectral.comp`.

---

*Generated on mcstas 3.99.99.*