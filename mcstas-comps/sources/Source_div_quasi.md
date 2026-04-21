# The `Source_div_quasi` Component

*McStas: Quasi-stochastic neutron source with Gaussian or uniform divergence*

## Identification

- **Site:** 
- **Author:** Mads Carlsen and Erik Bergbäck Knudsen (erkn@fysik.dtu.dk)
- **Origin:** DTU Physics
- **Date:** Jan 22

## Description

```text
A flat rectangular surface source with uniform or Gaussian divergence profile and focussing.
If the parametere gauss is not set (the default) the divergence profile is flat
in the range [-focus_ax,focus_ay]. If gauss is set, the focux_ax,focus_ay is considered
the standard deviation of the gaussian profile.
Currently focussing is only active for flat profile. The "focus window" is defined by focus_xw,focus_yh and dist.
The spectral intensity profile is uniformly distributed in the energy interval defined by e0+-dE/2 or
by wavelength lambda0+-dlambda/2

The phase space spanned by the generated neutrons is sampled by means of Halton-sequences, instead of regular
pseudo random numbers. This ensures that samples are evenly distributed within the phase space region of interest.

Example: Source_div_quasi(xwidth=0.1, yheight=0.1, focus_aw=2, focus_ah=2, E0=14, dE=2, gauss=0)

%VALIDATION

%BUGS
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| spectrum_file |  | File from which to read the spectral intensity profile | "" |
| xwidth | m | Width of source | 0 |
| yheight | m | Height of source | 0 |
| focus_xw | m | Width of sampling window | 0 |
| focus_yh | m | Height of sampling window | 0 |
| dist | m | Downstream distance to place sampling target window | 0 |
| focus_aw | rad | Std. dev. (Gaussian) or maximal (uniform) horz. width divergence. focus_xw overrrides if it is more restrictive. | 0 |
| focus_ah | rad | Std. dev. (Gaussian) or maximal (uniform) vert. height divergence. focus_yh overrrides if it is more restrictive. | 0 |
| E0 | meV | Mean energy of neutrons. | 0 |
| dE | meV | Energy spread of neutrons. | 0 |
| lambda0 | AA | Mean wavelength of neutrons (only relevant for E0=0) | 0 |
| dlambda | AA | Wavelength half spread of neutrons. | 0 |
| flux | 1/(s*cm**2*st*energy unit) | Flux per energy unit, Angs or meV | 0 |
| gauss | 1 | Criterion: 0: uniform, 1: Gaussian distribution of energy/wavelength | 0 |
| gauss_a | 1 | Criterion: 0: uniform, 1: Gaussian divergence distribution | 0 |
| randomphase |  | When=1, the X-ray phase is randomised | 1 |
| phase |  | Set to finite value to define X-ray phase (0:2 pi) | 0 |
| verbose |  | Generate more output on the console. | 1 |

## Links

- [Source code](Source_div_quasi.comp) for `Source_div_quasi.comp`.

---

*Generated on mcstas 3.99.99.*