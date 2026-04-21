# The `DivLambda_monitor` Component

*McStas: Divergence/wavelength monitor.*

## Identification

- **Site:** 
- **Author:** Kristian Nielsen
- **Origin:** Risoe
- **Date:** 1999

## Description

```text
2D detector for intensity as a function of both horizontal divergence
and wavelength.

Example: DivLambda_monitor(nL=20, nh=20, filename="Output.div",
xmin=-0.1, xmax=0.1, ymin=-0.1, ymax=0.1,
maxdiv_h=2, Lmin=2, Lmax=10)
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| nL | 1 | Number of bins in wavelength | 20 |
| nh | 1 | Number of bins in divergence | 20 |
| nowritefile | 1 | If set, monitor will skip writing to disk | 0 |
| filename | string | Name of file in which to store the detector image | 0 |
| xmin | m | Lower x bound of detector opening | -0.05 |
| xmax | m | Upper x bound of detector opening | 0.05 |
| ymin | m | Lower y bound of detector opening | -0.05 |
| ymax | m | Upper y bound of detector opening | 0.05 |
| xwidth | m | Width of detector. Overrides xmin,xmax. | 0 |
| yheight | m | Height of detector. Overrides ymin,ymax. | 0 |
| maxdiv_h | degrees | Maximal horizontal divergence detected | 2 |
| **Lmin** | AA | Minimum wavelength detected |  |
| **Lmax** | AA | Maximum wavelength detected |  |
| restore_neutron | 1 | If set, the monitor does not influence the neutron state | 0 |
| nx | 1 |  | 0 |
| ny | 1 | Vector definition of "forward" direction wrt. divergence, to be used e.g. when the monitor is rotated into the horizontal plane. | 0 |
| nz | 1 |  | 1 |

## Links

- [Source code](DivLambda_monitor.comp) for `DivLambda_monitor.comp`.

---

*Generated on mcstas 3.99.99.*