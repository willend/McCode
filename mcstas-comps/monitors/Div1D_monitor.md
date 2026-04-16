# The `Div1D_monitor` Component

*McStas: A 1D divergence sensitive monitor.*

## Identification

- **Site:** 
- **Author:** KL,
- **Origin:** Risoe
- **Date:** Nov. 11, 1998

## Description

```text
A divergence sensitive monitor. The counts are distributed in
ndiv pixels along either the horizontal axis x (default) or the vertical y.

Example: Div1D_monitor(xmin=-0.1, xmax=0.1, ymin=-0.1, ymax=0.1, ndiv=20, filename="Output.hd", maxdiv=2)
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| ndiv | 1 | Number of pixel rows | 20 |
| filename | str | Name of file in which to store the detector image | 0 |
| xmin | m | Lower x bound of detector opening | -0.05 |
| xmax | m | Upper x bound of detector opening | 0.05 |
| ymin | m | Lower y bound of detector opening | -0.05 |
| ymax | m | Upper y bound of detector opening | 0.05 |
| xwidth | m | Width of detector. Overrides xmin,xmax. | 0 |
| yheight | m | Height of detector. Overrides ymin,ymax. | 0 |
| maxdiv | deg | Maximal divergence detected | 2 |
| restore_neutron | 1 | If set, the monitor does not influence the neutron state | 0 |
| nowritefile | 1 | If set, monitor will skip writing to disk | 0 |
| vertical | 1 | If set, measure vertical divergence instead of horizontal. | 0 |

## Links

- [Source code](/Users/peterwillendrup/Projects/willend-McCode/mcstas-comps/monitors/Div1D_monitor.comp) for `Div1D_monitor.comp`.

---

*Generated on mcstas 3.99.99.*