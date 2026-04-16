# The `Source_gaussian` Component

*McXtrace: Gaussian cross-section source*

## Identification

- **Site:** 
- **Author:** Jana Baltser & Erik Knudsen
- **Origin:** NBI
- **Date:** April, 2011.

## Description

```text
A simple source model emitting photons from a gaussian distribution in the X-Y plane with the specified
standard deviations and divergence. A square target centered on the beam (Z-axis)
may be used to restrict the beam to that aperture. If no target aperture is given the full gaussian cross-section is used.
Further, the beam is restricted to emit photons between E0+-dE keV, or lambda0+-dlambda, whichever is given, if a spectrum_file
is not specified, in which case the contents of the file dictates the emitted spectrum.

Example: Source_gaussian(sig_x=10e-6,sig_y=10e-6,dist=15,sigPr_x=9e-6, sigPr_y=9e-6,E0=12.5, dE=0.1)
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| spectrum_file |  | File from which to read the spectral intensity profile | "NULL" |
| sig_x | m | Horizontal standard deviation of source (rms source size). | 1 |
| sig_y | m | Vertical standard deviation of source (rms source size). | 0 |
| sigPr_x | rad | Angular horizontal divergence | 0 |
| sigPr_y | rad | Angular vertical divergence | 0 |
| flux |  | Scaling factor to set the total emitted unrestricted flux. | 1 |
| brilliance |  | Unit in spectrum_file is Brilliance - apply corrections to get to raw flux. | 0 |
| dist | m | Distance from source plane to sampling window. | 1 |
| gauss | 0/1 | Gaussian (1) or uniform (0) spectrum profile. | 0 |
| focus_xw | m | Width of sampling window dist m downstream from source to allow focused sampling. | 0 |
| focus_yh | m | Height of sampling window dist m downstream from source to allow focused sampling. | 0 |
| E0 | keV | Centre of emitted energy spectrum (overrides spectrum_file) | 0 |
| dE | kev | Half-width (or std. dev.) of emitted energy spectrum. | 0 |
| lambda0 | AA | Centre of emitted wavelength spectrum. | 0 |
| dlambda | AA | Half-width (or std. dev.) of emitted wavelength spectrum. | -1 |
| phase | rad | The initial phase of the photons. | 0 |
| randomphase | rad | If nonzero phase is random (incoherent radiation), otherwise it is set to the value of phase | 1 |

## Links

- [Source code](/Users/peterwillendrup/Projects/willend-McCode/mcxtrace-comps/sources/Source_gaussian.comp) for `Source_gaussian.comp`.

---

*Generated on mcxtrace 3.99.99.*