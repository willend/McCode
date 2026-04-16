# The `Test_Fluorescence` Instrument

*McXtrace: Example instrument to test the Fluorescence sample.*

## Identification

- **Site:** Tests_samples
- **Author:** E. Farhi (emmanuel.farhi@synchrotron-soleil.fr)
- **Origin:** Synchrotron SOLEIL
- **Date:** March '21

## Description

```text
This instrument simply has a lab source, a few monitors and a sample
to model material fluorescence, Compton and Rayleigh scattering.
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| material | str | Material file to use, e.g. chemical formulae "Pb2SnO4" | "LaB6" |
| E0 | keV | Mean photon energy | 39 |
| dE | keV | Photon energy spread, half width | 0.06 |

## Links

- [Source code](/Users/peterwillendrup/Projects/willend-McCode/mcxtrace-comps/examples/Tests_samples/Test_Fluorescence/Test_Fluorescence.instr) for `Test_Fluorescence.instr`.

---

*Generated for mcxtrace 3.99.99.*