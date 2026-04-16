# The `TOF2E_monitor` Component

*McStas: TOF-sensitive monitor, converting to energy*

## Identification

- **Site:** 
- **Author:** Kim Lefmann and Helmuth Schoeber
- **Origin:** Risoe
- **Date:** Sept. 13, 2006

## Description

```text
A square single monitor that measures the energy of the incoming neutrons
from their time-of-flight

Example: TOF2E_monitor(xmin=-0.1, xmax=0.1, ymin=-0.1, ymax=0.1, Emin=1, Emax=50, nE=20, filename="Output.nrj", L_flight=20, T_zero=0)
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| nE | 1 | Number of energy channels | 20 |
| filename | string | Name of file in which to store the detector image | 0 |
| nowritefile | 1 | If set, monitor will skip writing to disk | 0 |
| xmin | m | Lower x bound of detector opening | -0.05 |
| xmax | m | Upper x bound of detector opening | 0.05 |
| ymin | m | Lower y bound of detector opening | -0.05 |
| ymax | m | Upper y bound of detector opening | 0.05 |
| xwidth | m | Width of detector. Overrides xmin, xmax | 0 |
| yheight | m | Height of detector. Overrides ymin, ymax | 0 |
| **Emin** | meV | Minimum energy to detect |  |
| **Emax** | meV | Maximum energy to detect |  |
| **T_zero** | s | Zero point in time |  |
| **L_flight** | m | flight length user in conversion |  |
| restore_neutron | 1 | If set, the monitor does not influence the neutron state | 0 |

## Links

- [Source code](/Users/peterwillendrup/Projects/willend-McCode/mcstas-comps/monitors/TOF2E_monitor.comp) for `TOF2E_monitor.comp`.

---

*Generated on mcstas 3.99.99.*