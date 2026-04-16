# The `Mirror` Component

*McXtrace: Perfectly flat mirror (in XZ or YZ), or polygonal*

## Identification

- **Site:** 
- **Author:** Erik B Knudsen
- **Origin:** DTU Physics
- **Date:** July 2016

## Description

```text
This is a simple implementation of a perfectly flat mirror. The mirror plane is in the XZ-plane.
It can be oriented in the YZ plane by setting 'yheight'.
It may also be a complex polygonal geometry (OFF/PLY) by setting 'geometry'.

Reflectivity may be specified either as a number (R0) or by means of a material datafile.
The material datafile may be specified as a coating or as relfectivity - either parameterized by q or E,theta.
If the datafile is identified as a coating recipe, an ab-initio reflectivity calculation is triggered.

Example: Mirror(xwidth=5e-2, zdepth=2e-1, R0=1, coating="B4C.dat")
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| zdepth | m | The length of the mirror | 0.1 |
| xwidth | m | The width of the mirror | 0.01 |
| yheight | m | The height of the mirror. This overrides xwidth and puts the mirror in the yz-plane. | 0 |
| coating | str | Filename containing reflectivities (or coating). | "" |
| R0 | 0-1 | Constant reflectivity | 0 |
| geometry | str | Filename of an OFF/PLY geometry providing a polygonal surface. When xwidth/yheight/zdepth are also given, the object is rescaled accordingly. | "" |

## Links

- [Source code](/Users/peterwillendrup/Projects/willend-McCode/mcxtrace-comps/optics/Mirror.comp) for `Mirror.comp`.

---

*Generated on mcxtrace 3.99.99.*