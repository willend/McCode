# The `MultiDiskChopper` Component

*McStas: Based on DiskChopper (Revision 1.18) by Peter Willendrup (2006),
which in turn is based on Chopper (Philipp Bernhardt), Jitter and beamstop from work by
Kaspar Hewitt Klenoe (jan 2006), adjustments by Rob Bewey (march 2006)*

## Identification

- **Site:** 
- **Author:** Markus Appel
- **Origin:** ILL / FAU Erlangen-Nuernberg
- **Date:** 2015-10-19

## Description

```text
Models a disk chopper with a freely configurable slit pattern. For simple applications,
use the DiskChopper component and see the component manual example of DiskChopper GROUPing.
If the chopper slit pattern should be dynamically configurable or a complicated pattern
is to be used as first chopper on a continuous source, use this component.

Width and position of the slits is defined as a list in string parameters so
they can easily be taken from instrument parameters.
The chopper axis is located on the y axis as defined by the parameter delta_y.
When the chopper is the first chopper after a continuous (i.e. time-independent)
source, the parameter isfirst should be set to 1 to increase Monte-Carlo efficiency.


Examples (see parameter definitions for details):
Two opposite slits with 10 and 20deg opening, with the 20deg slit in the beam at t=0.02:
MultiDiskChopper(radius=0.2, slit_center="0;180", slit_width="10;20", delta_y=-0.1,
nu=302, nslits=2, phase=180, delay=0.02)

First chopper on a continuous source, creating pulse trains for one additional revolution
before and after the revolution at t=0:
MultiDiskChopper(radius=0.2, slit_center="0;180", slit_width="10;20", delta_y=-0.1,
nu=302, nslits=2, phase=180, isfirst=1, nrev=1)
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| slit_center | string | (deg)   Angular position of the slits (similar to slit_width) | "0 180" |
| slit_width | string | (deg)   Angular width of the slits, given as list in a string separated by space ' ', comma ',', underscore '_' or semicolon ';'. Example: "0;20;90;135;270" | "10 20" |
| nslits |  | Number of slits to read from slit_width and slit_center | 2 |
| delta_y | m | y-position of the chopper rotation axis. If the chopper is located above the guide (delta_y>0), the coordinate system will be mirrored such that the created pulse pattern in time is the same as for delta_y<0. A warning will be printed in this case. | -0.3 |
| nu | Hz | Rotation speed of the disk, the sign determines the direction. | 0 |
| nrev |  | When isfirst=1: Number of *additional* disk revolutions before *and* after the one around t=delay to distribute events on. If set to 2 for example, there will be 2 leading, 1 central, and 2 trailing revolutions of the disk (2*nrev+1 in total). | 0 |
| ratio |  | When isfirst=1: Spacing of the additional revolutions from the parameter nrev from the central revolution. | 1 |
| jitter | s | Jitter in the time phase. | 0 |
| delay | s | Time delay of the chopper clock. | 0 |
| isfirst | 0/1 | Set to 1 for the first chopper after a continuous source. The neutron events | 0 |
| phase | deg | Phase angle located on top of the disk at t=delay (see below). | 0 |
| radius | m | Outer radius of the disk | 0.375 |
| equal | 0/1 | When isfirst=1: If 0, the neutron events will be distributed between different slits proportional to the slit size. If 1, the events will be distributed such that each slit transmits the same number of events. This parameter can be used to achieve comparable simulation statistics over different pulses when simulating small and large slits together. | 0 |
| abs_out |  | If 1, absorb all neutrons outside the disk diameter. | 0 |
| verbose | 0/1 | Set to 1 to display more information during the simulation. | 0 |

## Links

- [Source code](MultiDiskChopper.comp) for `MultiDiskChopper.comp`.

---

*Generated on mcstas 3.99.99.*