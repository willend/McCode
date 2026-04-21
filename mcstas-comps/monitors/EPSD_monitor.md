# The `EPSD_monitor` Component

*McStas: A monitor measuring neutron intensity vs. position, x, and neutron energy, E*

## Identification

- **Site:** 
- **Author:** Kim Lefmann
- **Origin:** Risoe
- **Date:** 16.4.00

## Description

```text
A monitor measuring neutron intensity vs. position, x, and neutron energy, E

Example: EPSD_monitor(xmin=-0.1, xmax=0.1, ymin=-0.1, ymax=0.1,
Emin=1, Emax=50, nx=20, nE=20, filename="Output.poe")
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| nx | 1 | Number of pixel columns in scattering plane | 20 |
| nE | 1 | Number of energy bins | 20 |
| filename | string | Name of file in which to store the detector image | 0 |
| xmin | m | Lower x bound of detector opening | -0.05 |
| xmax | m | Upper x bound of detector opening | 0.05 |
| ymin | m | Lower y bound of detector opening | -0.05 |
| ymax | m | Upper y bound of detector opening | 0.05 |
| nowritefile | 1 | If set, monitor will skip writing to disk | 0 |
| xwidth | m | Width of detector. Overrides xmin,xmax. | 0 |
| yheight | m | Height of detector. Overrides ymin,ymax. | 0 |
| **Emin** | meV | Lower bound of energy |  |
| **Emax** | meV | Upper bound of energy |  |
| restore_neutron | 1 | If set, the monitor does not influence the neutron state | 0 |

## Links

- [Source code](EPSD_monitor.comp) for `EPSD_monitor.comp`.

---

*Generated on mcstas 3.99.99.*