# The `TOFLambda_monitor` Component

*McStas: Time-of-flight/wavelength monitor.*

## Identification

- **Site:** 
- **Author:** KL
- **Origin:** Risoe
- **Date:** September 28, 2001

## Description

```text
2D detector for intensity as a function of both time-of-flight
and wavelength.
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| nowritefile | 1 | If set, monitor will skip writing to disk | 0 |
| nL | 1 | Number of bins in wavelength | 20 |
| nt | 1 | Number of bins in TOF | 128 |
| **tmin** | us | Minimum time |  |
| **tmax** | us | Maximum time |  |
| filename | string | Name of file in which to store the detector image | 0 |
| xmin | m | Lower x bound of detector opening | -0.05 |
| xmax | m | Upper x bound of detector opening | 0.05 |
| ymin | m | Lower y bound of detector opening | -0.05 |
| ymax | m | Upper y bound of detector opening | 0.05 |
| xwidth | m | Width/diameter of detector (x). Overrides xmin, xmax | 0 |
| yheight | m | Height of detector (y). Overrides ymin, ymax | 0 |
| **Lmin** | AA | Minimum wavelength detected |  |
| **Lmax** | AA | Maximum wavelength detected |  |
| restore_neutron | 1 | If set, the monitor does not influence the neutron state | 0 |

## Links

- [Source code](/Users/peterwillendrup/Projects/willend-McCode/mcstas-comps/monitors/TOFLambda_monitor.comp) for `TOFLambda_monitor.comp`.

---

*Generated on mcstas 3.99.99.*