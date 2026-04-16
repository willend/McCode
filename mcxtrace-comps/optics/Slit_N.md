# The `Slit_N` Component

*McXtrace: Release: McXtrace 0.1

Rectangular/circular slit, duplicated*

## Identification

- **Site:** 
- **Author:** Erik Knudsen
- **Origin:** Risoe
- **Date:** June 16, 2009

## Description

```text
Based on Slit-comp by Kim Lefmann and Henrik Roennow
A simple rectangular or circular slit. You may either
specify the radius (circular shape), which takes precedence,
or the rectangular bounds. The slits are separated with 'd', and arranged along X.
No transmission around the slit is allowed.
If cutting option is used, low-weight x-rays are ABSORBED

Example: Slit_N(xwidth=0.01, yheight=0.01, d=0.02)
Slit_N(radius=0.01, cut=1e-10, d=0.03)
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| radius | m | Radius of slit in the z=0 plane, centered at Origo | 0 |
| cut |  | Lower limit for allowed weight (1) | 0 |
| xwidth | m | Width of slit. Overrides xmin,xmax. | 0 |
| yheight | m | Height of slit. Overrides ymin,ymax. | 0 |
| N | 1 | Number of slit openings along X | 2 |
| d | m | Separation of slits | 0 |

## Links

- [Source code](/Users/peterwillendrup/Projects/willend-McCode/mcxtrace-comps/optics/Slit_N.comp) for `Slit_N.comp`.

---

*Generated on mcxtrace 3.99.99.*