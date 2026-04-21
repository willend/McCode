# The `L_monitor` Component

*McStas: Wavelength-sensitive monitor.*

## Identification

- **Site:** 
- **Author:** Kristian Nielsen and Kim Lefmann
- **Origin:** Risoe
- **Date:** April 20, 1998

## Description

```text
A square single monitor that measures the wavelength of the incoming
neutrons.

Example: L_monitor(xmin=-0.1, xmax=0.1, ymin=-0.1, ymax=0.1, nL=20, filename="Output.L", Lmin=2, Lmax=10)
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| nL | 1 | Number of wavelength channels | 20 |
| filename | string | Name of file in which to store the detector image | 0 |
| nowritefile | 1 | If set, monitor will skip writing to disk | 0 |
| xmin | m | Lower x bound of detector opening | -0.05 |
| xmax | m | Upper x bound of detector opening | 0.05 |
| ymin | m | Lower y bound of detector opening | -0.05 |
| ymax | m | Upper y bound of detector opening | 0.05 |
| xwidth | m | Width of detector. Overrides xmin, xmax. | 0 |
| yheight | m | Height of detector. Overrides ymin, ymax. | 0 |
| **Lmin** | AA | Minimum wavelength to detect |  |
| **Lmax** | AA | Maximum wavelength to detect |  |
| restore_neutron | 1 | If set, the monitor does not influence the neutron state | 0 |

## Links

- [Source code](L_monitor.comp) for `L_monitor.comp`.

---

*Generated on mcstas 3.99.99.*