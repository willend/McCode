# The `PSDlin_monitor` Component

*McStas: Rectangular 1D PSD, measuring intensity vs. position along an axis,*

## Identification

- **Site:** 
- **Author:** Kim Lefmann
- **Origin:** Risoe
- **Date:** May 7, 2001

## Description

```text
A 1-dimensional PSD measuring intensity along either the horizontal axis x (default) or
the vertical axis y.


Example: PSDlin_monitor(nbins=20, filename="Output.x", xmin=-0.1, xmax=0.1, ymin=-0.1, ymax=0.1)
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| nbins | 1 | Number of positional bins. | 20 |
| filename | str | Name of file in which to store the detector image. | 0 |
| xmin | m | Lower x bound of detector opening. | -0.05 |
| xmax | m | Upper x bound of detector opening. | 0.05 |
| ymin | m | Lower y bound of detector opening. | -0.05 |
| ymax | m | Upper y bound of detector opening. | 0.05 |
| nowritefile | 1 | If set, monitor will skip writing to disk | 0 |
| xwidth | m | Width of detector. Overrides xmin, xmax. | 0 |
| yheight | m | Height of detector. Overrides ymin, ymax. | 0 |
| restore_neutron | 1 | If set, the monitor does not influence the neutron state. | 0 |
| vertical | 1 | Flag to indicate whether the monitor measures along the horiz. or vert. axis | 0 |

## Links

- [Source code](/Users/peterwillendrup/Projects/willend-McCode/mcstas-comps/monitors/PSDlin_monitor.comp) for `PSDlin_monitor.comp`.

---

*Generated on mcstas 3.99.99.*