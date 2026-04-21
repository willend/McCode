# The `Spot_sample` Component

*McStas: Spot sample.*

## Identification

- **Site:** 
- **Author:** Garrett Granroth
- **Origin:** Oak Ridge National Laboratory
- **Date:** 14.11.14

## Description

```text
A sample that is a series of delta functions in omega and Q.  The Q is
determined by a two theta value and an equal number of spots around the
beam center.  This component is a variation of the V sample written
by Kim Lefmann and Kristian Nielsen.  The following text comes from their
original component.
A Double-cylinder shaped incoherent scatterer (a V-sample)
No multiple scattering. Absorbtion included.
The shape of the sample may be a box with dimensions xwidth, yheight, zthick.
The area to scatter to is a disk of radius 'focus_r' situated at the target.
This target area may also be rectangular if specified focus_xw and focus_yh
or focus_aw and focus_ah, respectively in meters and degrees.
The target itself is either situated according to given coordinates (x,y,z), or
setting the relative target_index of the component to focus at (next is +1).
This target position will be set to its AT position. When targeting to centered
components, such as spheres or cylinders, define an Arm component where to
focus at.

Example: spot_sample(radius_o=0.01, h=0.05, pack = 1,
xwidth=0, yheight=0, zthick=0, Eideal=100.0,w=50.0,two_theta=25.0,n_spots=4)
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| radius_o | m | Outer radius of sample in (x,z) plane | 0.01 |
| h | m | Height of sample y direction | 0.05 |
| pack | 1 | Packing factor | 1 |
| xwidth | m | horiz. dimension of sample, as a width | 0 |
| yheight | m | vert.. dimension of sample, as a height | 0 |
| zthick | m | thickness of sample | 0 |
| Eideal | meV | The presumed incident energy | 100.0 |
| w | meV | The energy transfer of the delta function | 50.0 |
| two_theta | degrees | the scattering angle of the spot | 25.0 |
| n_spots | 1 | The number of spots to generate symmetrically around the beam | 4 |

## Links

- [Source code](Spot_sample.comp) for `Spot_sample.comp`.

---

*Generated on mcstas 3.99.99.*