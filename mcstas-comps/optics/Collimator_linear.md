# The `Collimator_linear` Component

*McStas: A simple analytical Soller collimator (with triangular transmission).*

## Identification

- **Site:** 
- **Author:** Kristian Nielsen
- **Origin:** Risoe
- **Date:** August 1998

## Description

```text
Soller collimator with rectangular opening and specified length. The
transmission function is an average and does not utilize knowledge of the
actual neutron trajectory. A zero divergence disables collimation (then the
component works as a double slit).

Example: Collimator_linear(xmin=-0.1, xmax=0.1, ymin=-0.1, ymax=0.1, length=0.25, divergence=40,transmission=0.7)
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| xmin | m | Lower x bound on slits | -0.02 |
| xmax | m | Upper x bound on slits | 0.02 |
| ymin | m | Lower y bound on slits | -0.05 |
| ymax | m | Upper y bound on slits | 0.05 |
| xwidth | m | Width of slits | 0 |
| yheight | m | Height of slits | 0 |
| length | m | Distance between input and output slits | 0.3 |
| divergence | minutes of arc | Divergence horizontal angle (calculated as atan(d/length), where d is the blade spacing) | 40 |
| transmission | 1 | Transmission of Soller (0<=t<=1) | 1 |
| divergenceV | minutes of arc | Divergence vertical angle | 0 |

## Links

- [Source code](/Users/peterwillendrup/Projects/willend-McCode/mcstas-comps/optics/Collimator_linear.comp) for `Collimator_linear.comp`.

---

*Generated on mcstas 3.99.99.*