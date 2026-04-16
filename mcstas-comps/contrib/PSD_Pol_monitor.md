# The `PSD_Pol_monitor` Component

*McStas: Position-sensitive monitor.*

## Identification

- **Site:** 
- **Author:** Alexander Backs, based on PSD_monitor by K. Lefmann
- **Origin:** ESS
- **Date:** 2022

## Description

```text
An (n times m) pixel PSD monitor, measuring local polarisation as function of x,y coordinates.

Example: PSD_Pol_monitor(xmin=-0.1, xmax=0.1, ymin=-0.1, ymax=0.1, nx=90, ny=90, my=1, filename="Output.psd")
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| nx | 1 | Number of pixel columns | 90 |
| ny | 1 | Number of pixel rows | 90 |
| filename | string | Name of file in which to store the detector image | 0 |
| xmin | m | Lower x bound of detector opening | -0.05 |
| xmax | m | Upper x bound of detector opening | 0.05 |
| ymin | m | Lower y bound of detector opening | -0.05 |
| ymax | m | Upper y bound of detector opening | 0.05 |
| xwidth | m | Width of detector. Overrides xmin, xmax | 0 |
| yheight | m | Height of detector. Overrides ymin, ymax | 0 |
| restore_neutron | 1 | If set, the monitor does not influence the neutron state | 0 |
| nowritefile | 1 | If set, monitor will skip writing to disk | 0 |
| mx | 1 | Define the projection axis along which the polarizatoin is evaluated, x-component | 0 |
| my | 1 | Define the projection axis along which the polarizatoin is evaluated, y-component | 0 |
| mz | 1 | Define the projection axis along which the polarizatoin is evaluated, z-component | 0 |

## Links

- [Source code](/Users/peterwillendrup/Projects/willend-McCode/mcstas-comps/contrib/PSD_Pol_monitor.comp) for `PSD_Pol_monitor.comp`.

---

*Generated on mcstas 3.99.99.*