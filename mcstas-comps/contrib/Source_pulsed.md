# The `Source_pulsed` Component

*McStas: A pulsed source for variable proton pulse lenghts*

## Identification

- **Site:** 
- **Author:** Klaus Lieutenant, based on component 'Moderator' by K. Nielsen, M. Hagen and 'ESS_moderator_long_2001' by K. Lefmann
- **Origin:** FZ Juelich
- **Date:** 

## Description

```text
Produces a long pulse spectrum with a wavelength distribution as a sum of up to 3 Maxwellian distributions and one of undermoderated neutrons

It uses the time dependence of long pulses. Short pulses can, however, also be simulated by setting the proton pulse short.

If moderator width and height are given, it assumes a rectangular moderator, and otherwise a circular

Usage example:
Source_pulsed(xwidth=0.04, yheight=0.04, Lmin=1.0, Lmax=3.0, t_min=0.0, t_max=0.5, dist=0.700, focus_xw=0.020, focus_yh=0.020,
freq=96.0, t_pulse=0.000208, T1=325.0, I1=7.6e09, tau1=0.000170, I_um=2.7e08, chi_um=2.5)

Parameters for some sources:
HBS thermal source: xwidth=0.04, yheight=0.04, T1=325.0, I1=0.68e+12/freq, tau1=0.000125, n_mod=10, I_um=2.47e+10/freq, chi_um=2.5, t_pulse=0.016/freq, freq=96.0 or 24.0
HBS cold source   : radius=0.010,              T1= 60.0, I1=1.75e+12/freq, tau2=0.000170, n_mod= 5, I_um=3.82e+10/freq, chi_um=0.9, t_pulse=0.016/freq, freq=24.0 or 96.0
HBS bi-spectral   : radius=0.022, r_i=0.010,   T1= 60.0, I1=1.75e+12/freq, tau2=0.000170,
T2=305.0, I2=0.56e+12/freq, tau1=0.000130, n_mod= 5, I_um=3.82e+10/freq, chi_um=2.5, t_pulse=0.016/freq, freq=24.0 or 96.0
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| xwidth | m | Width of the source | 0.0 |
| yheight | m | Height of the source | 0.0 |
| radius | m | Outer radius of the source | 0.010 |
| r_i | m | Radius of a central circle that is sorrounded by a ring of different temperature | 0.0 |
| **Lmin** | Ang | Lower edge of the wavelength distribution |  |
| **Lmax** | Ang | Upper edge of the wavelength distribution |  |
| t_min | s | Lower edge of the time interval | 0.0 |
| t_max | s | Upper edge of the time interval | 0.001 |
| target_index | 1 | relative index of component to focus at, e.g. next is +1 this is used to compute 'dist' automatically. | 1 |
| dist | m | Distance from the source to the target | 0.0 |
| focus_xw | m | Width  of the target (= focusing rectangle) | 0.02 |
| focus_yh | m | Height of the target (= focusing rectangle) | 0.02 |
| **freq** | Hz | Frequency of pulses |  |
| **t_pulse** | s | Proton pulse length |  |
| T1 | K | Temperature of the 1st Maxwellian distribution, for r_i > 0 only for radii r in the range 0 < r < r_i | 0.0 |
| I1 | 1/(cm**2*sr) | Flux per solid angle of the 1st Maxwellian distribution (integrated over the whole wavelength range). | 0.0 |
| tau1 | s | Pulse decay constant of the 1st Maxwellian distribution | 0.000125 |
| T2 | K | Temperature of the 2nd Maxwellian distribution, 0=none, for r_i > 0 only for radii r in the range r_i < r < radius | 0.0 |
| I2 | 1/(cm**2*sr) | Flux per solid angle of the 2nd Maxwellian distribution | 0.0 |
| tau2 | s | Pulse decay constant of the 2nd Maxwellian distribution | 0.0 |
| T3 | K | Temperature of the 3rd Maxwellian distribution, 0=none | 0.0 |
| I3 | 1/(cm**2*sr) | Flux per solid angle of the 3rd Maxwellian distribution | 0.0 |
| tau3 | s | Pulse decay constant of the 3rd Maxwellian distribution | 0.0 |
| n_mod | 1 | Ratio of pulse decay constant to pulse ascend constant of moderated neutrons | 10 |
| I_um | 1/(cm**2*sr) | Flux per solid angle for the under-moderated neutrons | 0.0 |
| tau_um | s | Pulse decay constant of under-moderated neutrons | 0.000012 |
| n_um | 1 | Ratio of pulse decay constant to pulse ascend constant of under-moderated neutrons | 5 |
| chi_um | 1/Ang | Factor for the wavelength dependence of under-moderated neutrons | 2.5 |
| kap_um | 1 | Scaling factor for the flux of under-moderated neutrons | 2.2 |

## Links

- [Source code](Source_pulsed.comp) for `Source_pulsed.comp`.

---

*Generated on mcstas 3.99.99.*