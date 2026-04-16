# The `Slit` Component

*McXtrace: Rectangular/circular slit*

## Identification

- **Site:** 
- **Author:** Erik Knudsen
- **Origin:** DTU Physics
- **Date:** June 16, 2009

## Description

```text
Based on Slit-comp by Kim Lefmann and Henrik Roennow
A simple rectangular or circular slit. You may either
specify the radius (circular shape), which takes precedence,
or rectangular bounds.
No transmission around the slit is allowed.



Example: Slit(xmin=-0.01, xmax=0.01, ymin=-0.01, ymax=0.01)
Slit(radius=0.01)
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| xmin | m | Lower x bound. | 0 |
| xmax | m | Upper x bound. | 0 |
| ymin | m | Lower y bound. | 0 |
| ymax | m | Upper y bound. | 0 |
| radius | m | Radius of slit in the z=0 plane, centered at Origin. | 0 |
| xwidth | m | Width of slit. Overrides xmin,xmax. | 0.001 |
| yheight | m | Height of slit. Overrides ymin,ymax. | 0.001 |
| dist | m | Distance from slit plane to plane containing resampling target. | 0 |
| focus_xw | m | Width of resampling window. | 0 |
| focus_yh | m | Height of resampling window. | 0 |
| focus_x0 | m | Centre (x) of resampling window. | 0 |
| focus_y0 | m | Centre (y) of resampling window. | 0 |

## Links

- [Source code](/Users/peterwillendrup/Projects/willend-McCode/mcxtrace-comps/optics/Slit.comp) for `Slit.comp`.

---

*Generated on mcxtrace 3.99.99.*