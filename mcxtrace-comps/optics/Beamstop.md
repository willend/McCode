# The `Beamstop` Component

*McXtrace: Rectangular/circular beam stop.*

## Identification

- **Site:** 
- **Author:** Kristian Nielsen
- **Origin:** Risoe
- **Date:** March 2011

## Description

```text
A simple rectangular or circular beam stop.
Infinitely thin and infinitely absorbing.
The beam stop is by default rectangular. You may either
specify the radius (circular shape), or the rectangular bounds.

Example: Beamstop(xmin=-0.05, xmax=0.05, ymin=-0.05, ymax=0.05)
Beamstop(radius=0.1)
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| xmin | m | Lower x bound | -0.05 |
| xmax | m | Upper x bound | 0.05 |
| ymin | m | Lower y bound | -0.05 |
| ymax | m | Upper y bound | 0.05 |
| xwidth | m | Width of beamstop (x). Overrides xmin,xmax. | 0 |
| yheight | m | Height of beamstop (y). Overrides ymin,ymax. | 0 |
| radius | m | Radius of the beam stop in the z=0 plane, centered at Origo | 0 |

## Links

- [Source code](/Users/peterwillendrup/Projects/willend-McCode/mcxtrace-comps/optics/Beamstop.comp) for `Beamstop.comp`.

---

*Generated on mcxtrace 3.99.99.*