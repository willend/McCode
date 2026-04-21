# The `multi_pipe` Component

*McStas: multi-pipe circular slit.*

## Identification

- **Site:** 
- **Author:** Uwe Filges
- **Origin:** PSI
- **Date:** March, 2005

## Description

```text
No transmission around the slit is allowed.

example for an input file
# user defined geometry
# x(i) y(i) r(i) [m]
0.02 0.03 0.01
-0.04 0.015 0.005

warning: at least two values must be in the file

Example: multi_pipe(xmin=-0.01, xmax=0.01, ymin=-0.01, ymax=0.01)
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| filename | str | define user table of holes | 0 |
| **xmin** | m | Lower x bound |  |
| **xmax** | m | Upper x bound |  |
| **ymin** | m | Lower y bound |  |
| **ymax** | m | Upper y bound |  |
| radius |  | radius of a single hole | 0.0 |
| gap | m | distance between holes | 0.0 |
| thickness | m | thickness of the pipe | 0.0 |
| xwidth | m | Width of slit plate. Overrides xmin,xmax. | 0 |
| yheight | m | Height of slit plate. Overrides ymin,ymax. | 0 |

## Links

- [Source code](multi_pipe.comp) for `multi_pipe.comp`.

---

*Generated on mcstas 3.99.99.*