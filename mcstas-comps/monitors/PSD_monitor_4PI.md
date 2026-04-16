# The `PSD_monitor_4PI` Component

*McStas: Spherical position-sensitive detector.*

## Identification

- **Site:** 
- **Author:** Kim Lefmann and Kristian Nielsen
- **Origin:** Risoe
- **Date:** April 17, 1998

## Description

```text
An (n times m) pixel spherical PSD monitor using a cylindrical projection.
Mostly for test and debugging purposes.

Example: PSD_monitor_4PI(radius=0.1, nx=90, ny=90, filename="Output.psd")
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| nx | 1 | Number of pixel columns | 90 |
| ny | 1 | Number of pixel rows | 90 |
| filename | string | Name of file in which to store the detector image | 0 |
| nowritefile | 1 | If set, monitor will skip writing to disk | 0 |
| radius | m | Radius of detector | 1 |
| restore_neutron | 1 | If set, the monitor does not influence the neutron state | 0 |

## Links

- [Source code](/Users/peterwillendrup/Projects/willend-McCode/mcstas-comps/monitors/PSD_monitor_4PI.comp) for `PSD_monitor_4PI.comp`.
- <A HREF="http://neutron.risoe.dk/mcstas/components/tests/powder/">Test
- results</A> (not up-to-date).

---

*Generated on mcstas 3.99.99.*