# The `PSDlin_diff_monitor` Component

*McStas: Rectangular 1D PSD, measuring intensity vs. horizontal position, x
A second monitor shows the difference of intensities between in n'th and (n-1)'th pixels.*

## Identification

- **Site:** 
- **Author:** Kim Lefmann, Peter Willendrup, Linda Udby
- **Origin:** Risoe
- **Date:** May 7, 2001

## Description

```text
Example: PSDlin_diff_monitor(nx=20, filename="Output.x",
xmin=-0.1, xmax=0.1, ymin=-0.1, ymax=0.1)
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| nx | 1 | Number of x bins | 20 |
| filename | string | Name of file in which to store the detector image | 0 |
| xmin | m | Lower x bound of detector opening | -0.05 |
| xmax | m | Upper x bound of detector opening | 0.05 |
| ymin | m | Lower y bound of detector opening | -0.05 |
| ymax | m | Upper y bound of detector opening | 0.05 |
| nowritefile | 1 | If set, monitor will skip writing to disk | 0 |
| xwidth | m | Width of detector. Overrides xmin,xmax. | 0 |
| yheight | m | Height of detector. Overrides ymin,ymax. | 0 |
| restore_neutron | 1 | If set, the monitor does not influence the neutron state | 0 |

## Links

- [Source code](PSDlin_diff_monitor.comp) for `PSDlin_diff_monitor.comp`.

---

*Generated on mcstas 3.99.99.*