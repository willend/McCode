# The `Source_pt` Component

*McXtrace: Release: McXtrace 0.1

An x-ray point source*

## Identification

- **Site:** 
- **Author:** Erik Knudsen
- **Origin:** Risoe
- **Date:** June 29th, 2009

## Description

```text
A simple source model emitting photons from a point source uniformly into 4pi. A square target centered
on the Z-axis restricts the beam to that aperture.
If an input spectrum datafile (spectrum_file) is not specified, the beam is restricted to emit photons between E0+-dE keV, or lambda0+-dlambda AA, whichever is given.
The input spectrum file should be formatted such that x-ray energy/wavelength is in the first column and the intensity in the second. Any preceding
lines starting with # are considered part of the file header. If a datafile is given, a nonzero E¤0 value indicates that is is parametrized by energy ( in keV)
as opposed to wavelength (in AA). Wavelength is the default.
Flux is given in the unit photons/s

Example: Source_pt(dist=1,focus_xw=0.1,focus_yh=0.1, lamda=0.231, dlambda=0.002)
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| focus_xw | m | Width of target | 0 |
| focus_yh | m | Height of target | 0 |
| focus_x0 | m | x-cocordinate of target centre. | 0 |
| focus_y0 | m | y-coordinate of target centre. | 0 |
| flux | ph/s | Total flux radiated from the source. | 0 |
| dist | m | Distance from source plane to sampling window. | 1 |
| E0 | keV | Mean energy of xrays. | 0 |
| dE | keV | Energy half spread of x-rays. | 0 |
| lambda0 | AA | Mean wavelength of x-rays. | 0 |
| dlambda | AA | Wavelength half spread of x-rays (flat or gaussian sigma). | 0 |
| phase | rad | Set phase to something given. | 0 |
| randomphase | 0/1 | If nonzero, the phase of the emotted photon is random, i.e. source is fully incoherent. otherwise the value of phase is used. | 1 |
| gauss | 1 | Gaussian (1) or Flat (0) energy/wavelength distribution | 0 |
| spectrum_file | string | File from which to read an input spectrum. | "" |
| verbose | 1 | Output more information runtime. | 0 |

## Links

- [Source code](/Users/peterwillendrup/Projects/willend-McCode/mcxtrace-comps/sources/Source_pt.comp) for `Source_pt.comp`.

---

*Generated on mcxtrace 3.99.99.*