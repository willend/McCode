# The `Tunneling_sample` Component

*McStas: A Double-cylinder shaped all-incoherent scatterer
with elastic, quasielastic (Lorentzian), and tunneling (sharp)
components.*

## Identification

- **Site:** 
- **Author:** Kim Lefmann
- **Origin:** Risoe
- **Date:** 10.05.07

## Description

```text
A Double-cylinder shaped all-incoherent scatterer
with both elastic, quasielastic (Lorentzian), and tunneling (sharp)
components. No multiple scattering. Absorbtion included.
The shape of the sample may be a box with dimensions xwidth, yheight, zdepth.
The area to scatter to is a disk of radius 'focus_r' situated at the target.
This target area may also be rectangular if specified focus_xw and focus_yh
or focus_aw and focus_ah, respectively in meters and degrees.
The target itself is either situated according to given coordinates (x,y,z),
or defined with the relative target_index of the component to focus
to (next is +1).
This target position will be set to its AT position. When targeting to
centered components, such as spheres or cylinders, define an Arm component
where to focus to.

The outgoing polarization is calculated as for nuclear spin incoherence:
P' = 1/3*P-2/3P = -1/3P
As above multiple scattering is ignored .

Example: Tunneling_sample(thickness=0.001,radius=0.01,yheight=0.02,focus_r=0.035,
target_index=1)
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| thickness | m | Thickness of cylindrical sample in (x,z) plane | 0 |
| radius | m | Outer radius of sample in (x,z) plane | 0.01 |
| focus_r | m | Radius of disk containing target. Use 0 for full space | 0 |
| p_interact | 1 | MC Probability for scattering the ray; otherwise transmit | 1 |
| f_QE | 1 | Fraction of quasielastic scattering | 0 |
| f_tun | 1 | Fraction of tunneling scattering (f_QE+f_tun < 1) | 0 |
| gamma | meV | Lorentzian width of quasielastic broadening (HWHM) | 0 |
| E_tun | meV | Tunneling energy | 0 |
| target_x | m | X-position of target to focus at | 0 |
| target_y | m | Y-position of target to focus at | 0 |
| target_z | m | Z-position of target to focus at | 0.235 |
| focus_xw | m | horiz. dimension of a rectangular area | 0 |
| focus_yh | m | vert.  dimension of a rectangular area | 0 |
| focus_aw | deg | horiz. angular dimension of a rectangular area | 0 |
| focus_ah | deg | vert.  angular dimension of a rectangular area | 0 |
| xwidth | m | horiz. dimension of sample, as a width | 0 |
| yheight | m | vert.  dimension of sample, as a height | 0.05 |
| zdepth | m | depth of sample | 0 |
| sigma_abs | barns | Absorbtion cross section pr. unit cell | 5.08 |
| sigma_inc | barns | Total incoherent scattering cross section pr. unit cell | 4.935 |
| Vc | AA^3 | Unit cell volume | 13.827 |
| target_index | 1 | relative index of component to focus at, e.g. next is +1 | 0 |

## Links

- [Source code](Tunneling_sample.comp) for `Tunneling_sample.comp`.
- <A HREF="http://neutron.risoe.dk/mcstas/components/tests/v_sample/">Test
- results</A> (not up-to-date).

---

*Generated on mcstas 3.99.99.*