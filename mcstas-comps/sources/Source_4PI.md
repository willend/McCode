# The `Source_4PI` Component

*McStas: Spherical, 4PI-emitting, monochromatic source for benchmarking purposes*

## Identification

- **Site:** 
- **Author:** Peter Willendrup
- **Origin:** DTU
- **Date:** May 2024

## Description

```text
Spherical, 4PI-emitting, monochromatic source for benchmarking purposes
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| radius | m | Radius of spherical source | 0 |
| flux | n/s/4PI | Neutron flux | 1e14 |
| gauss |  | Flag to indicate if Energy/Wavelength distribution is gaussian | 0 |
| E0 | meV | Mean energy of neutrons. | 0 |
| dE | meV | Energy half spread of neutrons (flat or gaussian sigma). | 0 |
| lambda0 | AA | Mean wavelength of neutrons. | 0 |
| dlambda | AA | Wavelength half spread of neutrons. | 0 |

## Links

- [Source code](Source_4PI.comp) for `Source_4PI.comp`.

---

*Generated on mcstas 3.99.99.*