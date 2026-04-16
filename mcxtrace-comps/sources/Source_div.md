# The `Source_div` Component

*McXtrace: Release: McXtrace 0.1

X-ray source with Gaussian or uniform divergence*

## Identification

- **Site:** 
- **Author:** Erik Knudsen
- **Origin:** Risoe
- **Date:** November 11, 2009

## Description

```text
A flat rectangular surface source with uniform or Gaussian divergence profile and focussing.
If the parametere gauss is not set (the default) the divergence profile is flat
in the range [-focus_ax,focus_ay]. If gauss is set, the focux_ax,focus_ay is considered
the standard deviation of the gaussian profile.
Currently focussing is only active for flat profile. The "focus window" is defined by focus_xw,focus_yh and dist.
The spectral intensity profile is uniformly distributed in the energy interval defined by e0+-dE/2 or
by wavelength lambda0+-dlambda/2

Example: Source_div(xwidth=0.1, yheight=0.1, focus_aw=2, focus_ah=2, E0=14, dE=2, gauss=0)
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| spectrum_file | string | File from which to read the spectral intensity profile | "NULL" |
| xwidth | m | Width of source. | 0 |
| yheight | m | Height of source. | 0 |
| dist | m | Downstream distance to place sampling target window | 0 |
| focus_xw | m | Width of sampling window | 0 |
| focus_yh | m | Height of sampling window | 0 |
| focus_aw | rad | Standard deviation (Gaussian) or maximal (uniform) horz. width divergence. | 0 |
| focus_ah | rad | Standard deviation (Gaussian) or maximal (uniform) vert. height divergence. | 0 |
| focus_ar | rad | Standard deviation (Gaussian) or maximal (uniform) radial divergence. | 0 |
| radius | m | Radius of circular source | 0 |
| E0 | keV | Mean energy of X-rays. | 0 |
| dE | keV | Energy half spread of X-rays. If gauss==0 dE is the half-spread, i.e. E\in[E0-dE,E0+dE], if gauss!=0 it's interpreted as the standard dev. | 0 |
| lambda0 | AA | Mean wavelength of X-rays (only relevant for E0=0). | 0 |
| dlambda | AA | Wavelength half spread of X-rays. | 0 |
| flux | 1/(s * mm**2 *mrad**2 * energy unit) | flux per energy unit, Angs or keV. | 0 |
| gauss | 1 | Criterion: 0: uniform, 1: Gaussian distribution of energy/wavelength. | 0 |
| gauss_a | 1 | Criterion: 0: uniform, 1: Gaussian divergence distribution. | 0 |
| randomphase | 1 | If !=0 the photon phase is chosen randomly. | 1 |
| phase | 1 | Value of the photon phase (if randomphase==0). | 0 |
| verbose | 0/1 | Show more information | 0 |

## Links

- [Source code](/Users/peterwillendrup/Projects/willend-McCode/mcxtrace-comps/sources/Source_div.comp) for `Source_div.comp`.

---

*Generated on mcxtrace 3.99.99.*