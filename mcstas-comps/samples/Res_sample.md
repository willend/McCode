# The `Res_sample` Component

*McStas: Sample for resolution function calculation.*

## Identification

- **Site:** 
- **Author:** Kristian Nielsen
- **Origin:** Risoe
- **Date:** 1999

## Description

```text
An inelastic sample with completely uniform scattering in both Q and
energy. This sample is used together with the Res_monitor component and
(optionally) the mcresplot front-end to compute the resolution function of
triple-axis or inverse-geometry time-of-flight instruments.

The shape of the sample is either a hollow cylinder or a rectangular box. The
hollow cylinder shape is specified with an inner and outer radius.
The box is specified with dimensions xwidth, yheight, zdepth.

The scattered neutrons will have directions towards a given disk and
energies betweed E0-dE and E0+dE.
This target area may also be rectangular if specified focus_xw and focus_yh
or focus_aw and focus_ah, respectively in meters and degrees.
The target itself is either situated according to given coordinates (x,y,z), or
setting the relative target_index of the component to focus at (next is +1).
This target position will be set to its AT position. When targeting to centered
components, such as spheres or cylinders, define an Arm component where to focus at.

Example: Res_sample(thickness=0.001,radius=0.02,yheight=0.4,focus_r=0.05, E0=14.6,dE=2, target_x=0, target_y=0, target_z=1)
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| thickness | m | Thickness of hollow cylinder in (x,z) plane | 0 |
| radius | m | Outer radius of hollow cylinder | 0.01 |
| focus_r | m | Radius of sphere containing target. | 0.05 |
| E0 | meV | Center of scattered energy range | 14 |
| dE | meV | half width of scattered energy range | 2 |
| target_x | m | X-position of target to focus at [m] | 0 |
| target_y | m | Y-position of target to focus at | 0 |
| target_z | m | Z-position of target to focus at [m] | .5 |
| focus_xw | m | horiz. dimension of a rectangular area | 0 |
| focus_yh | m | vert. dimension of a rectangular area | 0 |
| focus_aw | deg | horiz. angular dimension of a rectangular area | 0 |
| focus_ah | deg | vert. angular dimension of a rectangular area | 0 |
| xwidth | m | horiz. dimension of sample, as a width | 0 |
| yheight | m | vert. dimension of sample, as a height | 0.05 |
| zdepth | m | depth of sample | 0 |
| target_index | 1 | relative index of component to focus at, e.g. next is +1 | 0 |

## Links

- [Source code](/Users/peterwillendrup/Projects/willend-McCode/mcstas-comps/samples/Res_sample.comp) for `Res_sample.comp`.

---

*Generated on mcstas 3.99.99.*