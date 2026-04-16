# The `Moderator` Component

*McStas: A simple pulsed source for time-of-flight.*

## Identification

- **Site:** 
- **Author:** KN, M.Hagen
- **Origin:** Risoe
- **Date:** August 1998

## Description

```text
Produces a simple time-of-flight spectrum, with a flat energy distribution

Example: Moderator(radius = 0.0707, dist = 9.035, focus_xw = 0.021, focus_yh = 0.021, Emin = 10, Emax = 15, Ec = 9.0, t0 = 37.15, gamma = 39.1)
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| radius | m | Radius of source | 0.07 |
| **Emin** | meV | Lower edge of energy distribution |  |
| **Emax** | meV | Upper edge of energy distribution |  |
| dist | m | Distance from source to the focusing rectangle | 0 |
| focus_xw | m | Width of focusing rectangle | 0.02 |
| focus_yh | m | Height of focusing rectangle | 0.02 |
| t0 | mus | decay constant for low-energy neutrons | 37.15 |
| Ec | meV | Critical energy, below which the flux decay is constant | 9.0 |
| gamma | meV | energy dependence of decay time | 39.1 |
| target_index | 1 | relative index of component to focus at, e.g. next is +1 this is used to compute 'dist' automatically. | 1 |
| flux | 1/(s cm 2 st meV) | flux | 1 |

## Links

- [Source code](/Users/peterwillendrup/Projects/willend-McCode/mcstas-comps/sources/Moderator.comp) for `Moderator.comp`.

---

*Generated on mcstas 3.99.99.*