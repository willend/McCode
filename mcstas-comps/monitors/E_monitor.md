# The `E_monitor` Component

*McStas: Energy-sensitive monitor.*

## Identification

- **Site:** 
- **Author:** Kristian Nielsen and Kim Lefmann
- **Origin:** Risoe
- **Date:** April 20, 1998

## Description

```text
A square single monitor that measures the energy of the incoming neutrons.

Example: E_monitor(xmin=-0.1, xmax=0.1, ymin=-0.1, ymax=0.1,
Emin=1, Emax=50, nE=20, filename="Output.nrj")
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| nE | 1 | Number of energy channels | 20 |
| filename | string | Name of file in which to store the detector image | 0 |
| xmin | m | Lower x bound of detector opening | -0.05 |
| xmax | m | Upper x bound of detector opening | 0.05 |
| ymin | m | Lower y bound of detector opening | -0.05 |
| ymax | m | Upper y bound of detector opening | 0.05 |
| nowritefile | 1 | If set, monitor will skip writing to disk | 0 |
| xwidth | m | Width of detector. Overrides xmin, xmax. | 0 |
| yheight | m | Height of detector. Overrides ymin, ymax. | 0 |
| **Emin** | meV | Minimum energy to detect |  |
| **Emax** | meV | Maximum energy to detect |  |
| restore_neutron | 1 | If set, the monitor does not influence the neutron state | 0 |

## Links

- [Source code](E_monitor.comp) for `E_monitor.comp`.

---

*Generated on mcstas 3.99.99.*