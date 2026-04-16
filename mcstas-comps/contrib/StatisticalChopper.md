# The `StatisticalChopper` Component

*McStas: Statistical (correlation) Chopper*

## Identification

- **Site:** 
- **Author:** C. Monzat/E. Farhi/S. Rozenkranz
- **Origin:** ILL
- **Date:** Nov 10th, 2009

## Description

```text
This component is a statistical chopper based on a pseudo random sequence that the user
can specify. Inspired from DiskChopper, it should be used with SatisticalChopper_Monitor component.

Example: StatisticalChopper(nu=1487*60/255) use default sequence
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| radius | m | Radius of the disc | 0.5 |
| yheight | m | Slit height (if = 0, equal to radius). Auto centering of beam at half height. | 0 |
| **nu** | Hz | Frequency of the Chopper, omega=2*PI*nu |  |
| jitter | s | Jitter in the time phase | 0 |
| delay | s | Time 'delay'. | 0 |
| isfirst | 0/1 | Set it to 1 for the first chopper position in a cw source | 0 |
| abs_out | 0/1 | Absorb neutrons hitting outside of chopper radius? | 1 |
| phase | deg | Angular 'delay' (overrides delay) | 0 |
| verbose | 1 | Set to 1 to display Disk chopper configuration | 0 |
| n_pulse | 1 | Number of pulses (Only if isfirst) | 1 |
| sequence | str | Slit sequence around disk, with 0=closed, 1=open positions. | "NULL" |

## Links

- [Source code](/Users/peterwillendrup/Projects/willend-McCode/mcstas-comps/contrib/StatisticalChopper.comp) for `StatisticalChopper.comp`.
- R. Von Jan and R. Scherm. The statistical chopper for neutron time-of-flight spectroscopy. Nuclear Instruments and Methods, 80 (1970) 69-76.

---

*Generated on mcstas 3.99.99.*