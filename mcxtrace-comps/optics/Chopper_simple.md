# The `Chopper_simple` Component

*McXtrace: Ideal chopper*

## Identification

- **Site:** 
- **Author:** 
- **Origin:** Risoe
- **Date:** August 2011

## Description

```text
Ideal model of a chopper situated at Z=0. If a photon arrives at the chopper plane
at a time of t = [t0 +-n*T: t0 +-n*T +tau], where T is the period of the chopper, t0 the initial delay
and tau the opening time of the chopper, it is left untouched - otherwise it is ABSORBed.
If on a continous source the isfirst parameter may be used. In this case the photon time is _defined_
by the chopper. In other words no photons are absorbed, the photon time is merely sampled within the chopper window.
t_rise is the rise-time of the chopper opening giving a trapezoidal shape.
Limitations: this component does not take chopper geometry into account. If isfirst only samples in the first chopper opening window.

Example: Chopper_simple(
t0 = -0.5/M_C, T = 20e-6, tau = 100e-12, xwidth = 1e-4,
yheight = 1e-4, isfirst = 1)
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| t0 | s | Initial delay of the opening time | 0 |
| T | s | Period of the chopper | 1 |
| tau | s | Opening time of the chopper | 0.1 |
| xwidth | m | Height of the chopper opening | 0.1 |
| yheight | m | Width of the chopeper opening | 0.1 |
| isfirst | 0/1 | Is the chopper the first chopper on a continous source. | 0 |
| t_rise | s | Rise time of the chopper pulse. | 0 |
| tjit | 1 | Timing jitter in terms of the opening time tau. For each ray the opening window will be shifted by a random amount within t=[-tjit*.5*tau,tjit*.5*tau] | 0 |

## Links

- [Source code](/Users/peterwillendrup/Projects/willend-McCode/mcxtrace-comps/optics/Chopper_simple.comp) for `Chopper_simple.comp`.

---

*Generated on mcxtrace 3.99.99.*