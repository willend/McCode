# The `Source_div` Component

*McStas: Neutron source with Gaussian or uniform divergence*

## Identification

- **Site:** 
- **Author:** KL
- **Origin:** Risoe
- **Date:** November 20, 1998

## Description

```text
The routine is a rectangular neutron source, which has a gaussian or uniform
divergent output in the forward direction.
The neutron energy is distributed between lambda0-dlambda and
lambda0+dlambda or between E0-dE and E0+dE. The flux unit is specified
in n/cm2/s/st/energy unit (meV or Angs).
In the case of uniform distribution (gauss=0), angles are uniformly distributed
between -focus_aw and +focus_aw as well as -focus_ah and +focus_ah.
For Gaussian distribution (gauss=1), 'focus_aw' and 'focus_ah' define the
FWHM of a Gaussian distribution. Energy/wavelength distribution is also
Gaussian.

Example: Source_div(xwidth=0.1, yheight=0.1, focus_aw=2, focus_ah=2, E0=14, dE=2, gauss=0)

%VALIDATION
Feb 2005: tested by Kim Lefmann    (o.k.)
Apr 2005: energy distribution used in external tests of Fermi choppers (o.k.)
Jun 2005: wavelength distribution used in external tests of velocity selectors (o.k.)
Validated by: K. Lieutenant

%BUGS
distribution is uniform in (hor. and vert.) angle (relative to moderator normal),
therefore not suited for large angles
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| **xwidth** | m | Width of source |  |
| **yheight** | m | Height of source |  |
| **focus_aw** | deg | FWHM (Gaussian) or maximal (uniform) horz. width divergence |  |
| **focus_ah** | deg | FWHM (Gaussian) or maximal (uniform) vert. height divergence |  |
| E0 | meV | Mean energy of neutrons. | 0.0 |
| dE | meV | Energy half spread of neutrons. | 0.0 |
| lambda0 | Ang | Mean wavelength of neutrons (only relevant for E0=0) | 0.0 |
| dlambda | Ang | Wavelength half spread of neutrons. | 0.0 |
| gauss | 0\|1 | Criterion: 0: uniform, 1: Gaussian distributions | 0 |
| flux | 1/(s cm 2 st energy_unit) | flux per energy unit, Angs or meV | 1 |

## Links

- [Source code](Source_div.comp) for `Source_div.comp`.

---

*Generated on mcstas 3.99.99.*