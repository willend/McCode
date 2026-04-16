# The `Source_genesis13` Component

*McXtrace: Release: McXtrace 1.2

Interface source for importing GENESIS 1.3 generated X-ray pulses into McXtrace*

## Identification

- **Site:** 
- **Author:** Erik B Knudsen
- **Origin:** Risoe
- **Date:** Aug. 10th, 2014

## Description

```text
This source model reads the dumped radiation field output from GENESIS 1.3 and samples it to be used
in McXtrace.

Example: Source_pt(dist=1,focus_xw=0.1,focus_yh=0.1, lamda=0.231, dlambda=0.002)
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| gridpoints | int | Number of mesh points along 1 axis. | 101 |
| fname | string | Filename of main output file of GENESIS 1.3. | "template.out" |
| focus_xw | m | Width of target. | 0 |
| focus_yh | m | Height of target. | 0 |
| dist | m | Distance to target along z axis. | 1 |
| E0 | keV | Mean energy of xrays. | 0 |
| dE | kev | Half-width (or std. dev.) of emitted energy spectrum. | 0 |
| meshsize | m | Spacing between mesh points (equal in x and y). | 1e-5 |
| nslices | int | Number of slices simulated | 102 |
| s0 | m | Back end of pulse time sampling windows scaled by c^-1. | -2e-3 |
| s1 | m | Front end of pulse time sampling window scaled by c^-1. | 2e-3 |
| flux | 1 | Flux-multiplier | 1.0 |
| focus_a | rad | Mean divergence angle. | 0.1 |

## Links

- [Source code](/Users/peterwillendrup/Projects/willend-McCode/mcxtrace-comps/sources/Source_genesis13.comp) for `Source_genesis13.comp`.

---

*Generated on mcxtrace 3.99.99.*