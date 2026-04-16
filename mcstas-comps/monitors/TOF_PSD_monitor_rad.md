# The `TOF_PSD_monitor_rad` Component

*McStas: Position-sensitive TOF monitor with radially averaging.*

## Identification

- **Site:** 
- **Author:** Kim Lefmann
- **Origin:** UCPH
- **Date:** March 2012

## Description

```text
TOF monitor that performs radial averaging.
Comment: The intensity is given as two 2D files:
1) a radial sum vs. TOF
2) a radial average (i.e. intensity per area) vs. TOF

Example: TOF_PSD_monitor_rad(rmax=0.2, nr=100, filename="Output.psd", filename_av="Output_av.psd")
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| nr | 1 | Number of concentric circles | 100 |
| nt | 1 | Number of time bins | 100 |
| nowritefile | 1 | If set, monitor will skip writing to disk | 0 |
| filename | string | Name of file in which to store the detector image | 0 |
| filename_av | string | Name of file in which to store the averaged detector image | 0 |
| rmax | m | Outer radius of detector | 0.2 |
| **tmin** | mu-s | Beginning of time window |  |
| **tmax** | mu-s | End of time window |  |
| restore_neutron | 1 | If set, the monitor does not influence the neutron state | 0 |

## Links

- [Source code](/Users/peterwillendrup/Projects/willend-McCode/mcstas-comps/monitors/TOF_PSD_monitor_rad.comp) for `TOF_PSD_monitor_rad.comp`.

---

*Generated on mcstas 3.99.99.*