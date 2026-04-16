# The `Capillary` Component

*McXtrace: Release: McXtrace 1.2

A capillary tube*

## Identification

- **Site:** 
- **Author:** Erik B Knudsen
- **Origin:** DTU Physics
- **Date:** July 2015

## Description

```text
A Capillary tube allowing for reflections along the tube. A material coating can be applied. Multilayer
coatings may be handled by generating a reflectivity file (e.g. by IMD) and setting rtable=1.
Waviness is implemented using the model described in
Wang et.al., J. Appl. Phys., 1996 where the grazing incidence angle <span class="latex">$\theta$</span> is altered as
<br>
<div class="latex">
$\theta' = \theta + \delta \theta \in [-min(theta,\Delta\theta,\Delta\theta]$
</div>
This ensures that reflected rays will never be scattered into the capillary.
<span class="latex">$\Delta\theta$</span> is the value specified by the parameter waviness.

Example: Capillary(
radius=1e-4,length=0.1, R0=0, coating="Rh.txt")
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| coating | str | Name of file containing the material data (i.e. f1 and f2) for the coating | "Be.txt" |
| longw | 0/1 | If non-zero, waviness is purely longitudinal in its nature. | 1 |
| radius | m | Radius of curvature. | 1 |
| length | m | Length of the unbent mirror. | 0.2 |
| R0 | 0-1 | Fixed constant reflectivity | 0 |
| rtable | 0/1 | If nonzero, the coating file contains an E,theta parameterized matrix of raw reflectivities. | 0 |
| waviness | rad | The momentaneous waviness is uniformly distributed in the range [-waviness,waviness]. | 0 |

## Links

- [Source code](/Users/peterwillendrup/Projects/willend-McCode/mcxtrace-comps/optics/Capillary.comp) for `Capillary.comp`.

---

*Generated on mcxtrace 3.99.99.*