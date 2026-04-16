# The `V_sample` Component

*McStas: Vanadium sample.*

## Identification

- **Site:** 
- **Author:** Kim Lefmann and Kristian Nielsen
- **Origin:** Risoe
- **Date:** 15.4.98

## Description

```text
A Double-cylinder shaped incoherent scatterer (a V-sample)
with both elastic and quasielastic (Lorentzian) components.
No multiple scattering. Absorbtion included.
The shape of the sample may be a box with dimensions xwidth, yheight, zthick.
The area to scatter to is a disk of radius 'focus_r' situated at the target.
This target area may also be rectangular if specified focus_xw and focus_yh
or focus_aw and focus_ah, respectively in meters and degrees.
The target itself is either situated according to given coordinates (x,y,z),
or defined with the relative target_index of the component to focus
to (next is +1).
This target position will be set to its AT position. When targeting to
centered components, such as spheres or cylinders, define an Arm component
where to focus to.

Example: V_sample(radius_i=0.001,radius_o=0.01,h=0.02,focus_r=0.035,pack=1,
target_index=1)
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| radius | m | Outer radius of sample in (x,z) plane | 0 |
| thickness | m | Thickness of outer wall | 0 |
| zdepth | m | depth of box sample | 0 |
| Vc |  | Unit cell volume [AA^3] | 13.827 |
| sigma_abs | barns | Absorbtion cross section pr. unit cell | 5.08 |
| sigma_inc | barns | Incoherent scattering cross section pr. unit cell | 5.08 |
| radius_i | m | radius-thickness | 0 |
| radius_o | m | Same as radius | 0 |
| h | m | Same as yheight | 0 |
| focus_r | m | Radius of disk containing target. Use 0 for full space | 0 |
| pack | 1 | Packing factor | 1 |
| frac | 1 | MC Probability for scattering the ray; otherwise penetrate | 1 |
| f_QE | 1 | Fraction of quasielastic scattering (rest is elastic) | 0 |
| gamma | 1 | Lorentzian width of quasielastic broadening (HWHM) | 0 |
| target_x |  |  | 0 |
| target_y | m | position of target to focus at | 0 |
| target_z |  |  | 0 |
| focus_xw | m | horiz. dimension of a rectangular area | 0 |
| focus_yh | m | vert.  dimension of a rectangular area | 0 |
| focus_aw | deg | angular width dimension of a rectangular area | 0 |
| focus_ah | deg | angular height dimension of a rectangular area | 0 |
| xwidth | m | horiz. dimension of sample | 0 |
| yheight | m | vert.  dimension of sample | 0 |
| zthick | m | Same as zdepth | 0 |
| rad_sphere | m | Radius for a spherical sample | 0 |
| sig_a | barns | Same as sigma_abs | 0 |
| sig_i | barns | Same as sigma_inc | 0 |
| V0 |  | Same as Vc [AA^3] | 0 |
| target_index | 1 | relative index of component to focus at, e.g. next is +1 | 0 |
| multiples | 1 | Apply crude estimate for multiple scattering | 1 |

## Links

- [Source code](/Users/peterwillendrup/Projects/willend-McCode/mcstas-comps/obsolete/V_sample.comp) for `V_sample.comp`.
- <A HREF="http://neutron.risoe.dk/mcstas/components/tests/v_sample/">Test
- results</A> (not up-to-date).
- The test/example instrument <a href="../examples/vanadium_example.instr">vanadium_example.instr</a>.
- The test/example instrument <a href="../examples/QENS_test.instr">QENS_test.instr</a>.

---

*Generated on mcstas 3.99.99.*