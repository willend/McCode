# The `Slit` Component

*McStas: Rectangular/circular slit*

## Identification

- **Site:** 
- **Author:** Kim Lefmann and Henrik M. Roennow
- **Origin:** Risoe
- **Date:** June 16, 1997

## Description

```text
A simple rectangular or circular slit. You may either
specify the radius (circular shape), or the rectangular bounds.
No transmission around the slit is allowed.

Example: Slit(xmin=-0.01, xmax=0.01, ymin=-0.01, ymax=0.01)
Slit(xwidth=0.02, yheight=0.02)
Slit(radius=0.01)

The Slit will issue a warning if run as "closed"
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| xmin | m | Lower x bound | UNSET |
| xmax | m | Upper x bound | UNSET |
| ymin | m | Lower y bound | UNSET |
| ymax | m | Upper y bound | UNSET |
| radius | m | Radius of slit in the z=0 plane, centered at Origin | UNSET |
| xwidth | m | Width of slit. Overrides xmin,xmax if they are unset. | UNSET |
| yheight | m | Height of slit. Overrides ymin,ymax if they are unset. | UNSET |

## Links

- [Source code](Slit.comp) for `Slit.comp`.

---

*Generated on mcstas 3.99.99.*