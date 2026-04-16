# The `DiskChopper` Component

*McStas: Based on Chopper (Philipp Bernhardt), Jitter and beamstop from work by
Kaspar Hewitt Klenoe (jan 2006), adjustments by Rob Bewey (march 2006)*

## Identification

- **Site:** 
- **Author:** Peter Willendrup
- **Origin:** Risoe
- **Date:** March 9 2006

## Description

```text
Models a disc chopper with nslit identical slits, which are symmetrically distributed
on the disc. At time t=0, the centre of the first slit opening will be situated at the
vertical axis when phase=0, assuming the chopper centre of rotation is placed <b>BELOW</b> the beam axis.
If you want to place the chopper <b>ABOVE</b> the beam axis, please use a 180 degree rotation around Z
(otherwise unexpected beam splitting can occur in combination with the isfirst=1 setting, see
<a href="https://github.com/mccode-dev/McCode/issues/650">related bug on GitHub</a>)

For more complicated gemometries, see component manual example of DiskChopper GROUPing.

If the chopper is the 1st chopper of a continuous source instrument, you should use the "isfirst" parameter.
This parameter SETS the neutron time to match the passage of the chooper slit(s), taking into account the
chopper timing and phasing (thus conserving your simulated statistics).

The isfirst parameter is ONLY relevant for use in continuous source settings.

Example: DiskChopper(radius=0.2, theta_0=10, nu=41.7, nslit=3, delay=0, isfirst=1) First chopper
DiskChopper(radius=0.2, theta_0=10, nu=41.7, nslit=3, delay=0, isfirst=0)

NOTA BENE wrt. GROUPing and isfirst:
When setting up a GROUP of DiskChoppers for a steady-state / reactor source, you will need
to set up
1) An initial chopper with isfirst=1, NOT part of the GROUP - and using a "big" chopper opening
that spans the full angular extent of the openings of the subsequent GROUP
2) Add your DiskChopper GROUP setting isfirst=0
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| theta_0 | deg | Angular width of the slits. | 0 |
| radius | m | Radius of the disc | 0.5 |
| **yheight** | m | Slit height (if = 0, equal to radius). Auto centering of beam at half height. |  |
| **nu** | Hz | Frequency of the Chopper, omega=2*PI*nu (algebraic sign defines the direction of rotation) |  |
| nslit | 1 | Number of slits, regularly arranged around the disk | 3 |
| jitter | s | Jitter in the time phase | 0 |
| delay | s | Time 'delay' | 0 |
| isfirst | 0/1 | Set it to 1 for the first chopper position in a cw source (it then spreads the neutron time distribution) | 0 |
| n_pulse | 1 | Number of pulses (Only if isfirst) | 1 |
| abs_out | 0/1 | Absorb neutrons hitting outside of chopper radius? | 1 |
| phase | deg | Angular 'delay' (overrides delay) | 0 |
| xwidth | m | Horizontal slit width opening at beam center | 0 |
| verbose | 1 | Set to 1 to display Disk chopper configuration | 0 |

## Links

- [Source code](/Users/peterwillendrup/Projects/willend-McCode/mcstas-comps/optics/DiskChopper.comp) for `DiskChopper.comp`.

---

*Generated on mcstas 3.99.99.*