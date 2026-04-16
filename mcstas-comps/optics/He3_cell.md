# The `He3_cell` Component

*McStas: version: $Revision$

Polarised 3He cell*

## Identification

- **Site:** 
- **Author:** Trefor Roberts & Erik B Knudsen
- **Origin:** ILL/DTU Physics
- **Date:** March 1999

## Description

```text
Simple polarised 3He neutron spin filter cell, defaults to a cylindrical geometry but may be
used with a sphere or box geometry also.
The glass container for the cell is not included in the model.

This component has been validated against:
Batz, M, Baessler, S, Heil, W, et al., J Res Natl Inst Stand Technol. 2005;110(3):293–298.

Example: He3_cell(radius=0.1,length=.2,pressure=3,p3he=0.7,bx=0,by=1e-3,bz=0)
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| xwidth | m | width of box geometry | 0 |
| yheight | m | height of the box geometry | 0 |
| radius | m | radius of the cylinder / sphere geometry | 0.11 |
| length | m | length of the cylinder / box geometry along z | 0.01 |
| pressure | bar | pressure of the gas in the cell | 3 |
| p3he |  | polarisation of the 3He gas [-1 to +1] | 0.7 |
| bx | tesla | x component of field at the cell | 0 |
| by | tesla | y component of field at the cell | 1e-3 |
| bz | tesla | z component of field at the cell | 0 |

## Links

- [Source code](/Users/peterwillendrup/Projects/willend-McCode/mcstas-comps/optics/He3_cell.comp) for `He3_cell.comp`.

---

*Generated on mcstas 3.99.99.*