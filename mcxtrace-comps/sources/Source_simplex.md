# The `Source_simplex` Component

*McXtrace: Release: McXtrace 1.2

Interface source for importing Simplex generated X-ray pulses into McXtrace*

## Identification

- **Site:** 
- **Author:** Erik B Knudsen
- **Origin:** Risoe
- **Date:** Aug. 10th, 2014

## Description

```text
This source model reads the dumped radiation field output from Simplex and samples it to be used
in McXtrace.
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| gridpoints | int | Number of mesh points along 1 axis. | 101 |
| fname | string | Filename of main output file of GENESIS 1.3. | "template.fld" |
| focus_xw | m | Width of target. | 0 |
| focus_yh | m | Height of target. | 0 |
| dist | m | Distance to target along z axis. | 1 |
| E0 | keV | Mean energy of xrays. | 0 |
| dE | keV | Energy half spread of x-rays. | 0 |
| meshsize | m | Spacing between mesh points (equal in x and y). | 1e-5 |
| nslices | 1 | Number of slices simulated. | 102 |
| s0 | m | Back end of pulse time sampling windows scaled by c^-1. | -2e-3 |
| s1 | m | Front end of pulse time sampling window scaled by c^-1. | 2e-3 |
| flux | 1 | Flux-multiplier. | 1.0 |
| focus_a | rad | Mean divergence angle. | 0.1 |

## Links

- [Source code](/Users/peterwillendrup/Projects/willend-McCode/mcxtrace-comps/sources/Source_simplex.comp) for `Source_simplex.comp`.
- Tanaka, Journal of Synchrotron Radiation 22, 1319 (2015) http://journals.iucr.org/s/issues/2015/05/00/gb5029/
- http://radiant.harima.riken.go.jp/simplex/

---

*Generated on mcxtrace 3.99.99.*