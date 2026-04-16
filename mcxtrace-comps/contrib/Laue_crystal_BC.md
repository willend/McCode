# The `Laue_crystal_BC` Component

*McXtrace: Perfect, Laue crystal with common cubic structures (diamond, fcc, or bcc, and others if symmetry form factor multipliers provided explicitly)*

## Identification

- **Site:** 
- **Author:** Marcus H Mendenhall, NIST <marcus.mendenhall@nist.gov>
- **Origin:** NIST
- **Date:** June, 2017

## Description

```text
NIST_Laue_crystal_BC.comp is written by Marcus H. Mendenhall, NIST, Gaithersburg, MD, USA
It is based on the full vector math and exact solution  of the dispersion relation in
Batterman and Cole, Reviews of Modern Physics 36 number 3, page 681, July 1964
Perfect crystal with common cubic structures (diamond, fcc, or bcc, and others if symmetry form factor multipliers provided explicitly)

Reads atomic form factors from a data input file.
The Laue_Crystal code reflects rays in an ideal geometry, does not include surface imperfections or mosaicity.

The crystal is positioned such that the long axis of the crystal surface coincides with
z-axis and the outer normal to the crystal surface is along +y.

The ratio of the transmitted beam and forward-diffracted Borrman-effect beam is a hack.  The sum of the
two is exactly right, but the actual ratio depends critically on geometry, and I just put in a wild estimate
to allow one to demonstrate what the Borrmann effect looks like. If this is turned on, the displacement of the
transmitted beam and forward diffracted beam at the back side of the crystal will be correctly computed.
This displacement is only exact for symmetrical Laue; asymmetrical computation requires more effort,
and is probably not worth it.
The sampling of these processes are controlled by the 3 variables transmission_sampling, forward_diffraction_sampling,
and Laue_sampling. Since 99% of uses of this will have the transmitted beam turned off, and use Laue diffraction mode,
the values should be just 0,0,1. If the general behavior of the transmitted beams
is interesting, use 1,1,1 which samples all beams equally.  Results weights are adjusted for this,
so computed intensities won't be affected.

Non-copyright notice:
Contributed by the National Institute of Standards and Technology; not subject to copyright in the United States.
This is not an official contribution, in that the results are in no way certified by NIST.
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| length | m | zdepth (length) of the crystal. | 0.05 |
| width | m | width of the crystal. | 0.02 |
| thickness | m | thickness of crystal (along y-axis, the surface normal) | 1e-4 |
| V | AA^3 | unit cell volume | 160.1826 |
| form_factors |  | "FormFactors.txt" from McXtrace install, usually | "FormFactors.txt" |
| material |  | Si ("Si.txt"), Ge ("Ge.txt") | "Si.txt" |
| alphax |  | x component of normal (unit vector) to crystal planes. Vector is usually [0,0,1] for symmetric Laue. Crystal surface itself has normal [0,1,0]. | 0.0 |
| alphay |  | y component of normal (unit vector) to crystal planes. | 0.0 |
| alphaz |  | z component of normal (unit vector) to crystal planes. | 1.0 |
| debye_waller_B | AA^2 | Debye-Waller temperature factor, M=B*(sin(theta)/lambda)^2*(2/3), default=silicon at room temp, 0.4632 | 0.4632 |
| crystal_type |  | 1 => Mx_crystal_explicit: provide explicit real and imaginary form factor multipliers structure_factor_scale_r, structure_factor_scale_i, | 1 |
| h |  | 1st Miller index of reflection | 1 |
| k |  | 2nd Miller index of reflection | 1 |
| l |  | 3rd Miller index of reflection | 1 |
| structure_factor_scale_r |  | real part of complex explicit override of structure factor multiplier for crystal structure if Bragg_crystal_explicit | 0.0 |
| structure_factor_scale_i |  | imaginary part of complex explicit override of structure factor multiplier for crystal structure if Bragg_crystal_explicit | 0.0 |
| transmission_sampling |  | enable sampling of transmission diffraction mode. | 1.0 |
| forward_diffraction_sampling |  | enable sampling of forward diffraftion mode. | 1.0 |
| laue_sampling |  | enable sampling of Laue diffraction mode. | 1.0 |

## Links

- [Source code](/Users/peterwillendrup/Projects/willend-McCode/mcxtrace-comps/contrib/Laue_crystal_BC.comp) for `Laue_crystal_BC.comp`.
- material datafile obtained from http://physics.nist.gov/cgi-bin/ffast/ffast.pl

---

*Generated on mcxtrace 3.99.99.*