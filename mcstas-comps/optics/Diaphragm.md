# The `Diaphragm` Component

*McStas: Rectangular/circular diaphragm (alias of the Slit component)*

## Identification

- **Site:** 
- **Author:** Peter Willendrup
- **Origin:** DTU
- **Date:** February 2016

## Description

```text
A simple rectangular or circular diaphragm. You may either
specify the radius (circular shape), or the rectangular bounds.
No transmission around the diaphragm is allowed.

Example: Diaphragm(xmin=-0.01, xmax=0.01, ymin=-0.01, ymax=0.01)
Diaphragm(radius=0.01)


For <B>INPUT PARAMETERS</B> - please consult <a href="Slit.html">Slit.comp</a> as Diaphragm is a copy of that component.
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|

## Links

- [Source code](/Users/peterwillendrup/Projects/willend-McCode/mcstas-comps/optics/Diaphragm.comp) for `Diaphragm.comp`.

---

*Generated on mcstas 3.99.99.*