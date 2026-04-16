# The `EPSD_monitor` Component

*McXtrace: Position-energy-sensitive monitor.*

## Identification

- **Site:** 
- **Author:** Erik B Knudsen
- **Origin:** DTU
- **Date:** June 22, 2009

## Description

```text
An nx times ny pixel energy resolved PSD monitor, which only counts photons with energy in an interval
given by Emin and Emax in nE energy bins. The default energy interval is (almost) infinite, with a single bin.
If nE>1 the component will output nE detector files + one which is integrated over the full energy interval.

Example: EPSD_monitor(xwidth=0.1, yheight=0.1,
nx=90, ny=90, filename="Output.psd")
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| nx | 1 | Number of pixel columns. | 90 |
| ny | 1 | Number of pixel rows. | 90 |
| filename | str | Name of file in which to store the detector image. | 0 |
| restore_xray | 1 | If set, the monitor does not influence the xray state. | 0 |
| xwidth | m | Width of detector. | 0.1 |
| yheight | m | Height of detector. | 0.1 |
| Emax | keV | Upper bound of energy interval. | 0 |
| Emin | keV | Lower bound of energy interval. | 0 |
| nE | 1 | Number of energy bins. | 1 |
| nowritefile | 1 | If set, monitor will skip writing to disk | 0 |

## Links

- [Source code](/Users/peterwillendrup/Projects/willend-McCode/mcxtrace-comps/monitors/EPSD_monitor.comp) for `EPSD_monitor.comp`.

---

*Generated on mcxtrace 3.99.99.*