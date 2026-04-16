# The `Bragg_crystal_BC` Component

*McXtrace: Perfect, reflecting crystal with common cubic structures (diamond, fcc, or bcc, and others if symmetry form factor multipliers provided explicitly)*

## Identification

- **Site:** 
- **Author:** Marcus H Mendenhall, NIST <marcus.mendenhall@nist.gov>
- **Origin:** NIST
- **Date:** May, 2017

## Description

```text
Bragg_crystal_BC.comp is intended to supercede Bragg_Crystal.comp.

For details see:
The optics of focusing bent-crystal monochromators on X-ray powder diffractometers with application to lattice parameter determination and microstructure analysis,
Marcus H. Mendenhall, David Black and James P. Cline, J. Appl. Cryst. (2019). 52, https://doi.org/10.1107/S1600576719010951

Reads atomic formfactors from a data input file.
The Bragg_Crystal code reflects ray in an ideal geometry, does not include surface imperfections or mosaicity

The crystal code reflects ray in an ideal geometry, i.e. does not include surface imperfections or mosaicity.
The crystal planes from which the reflection is made lies in the X-Z plane on the unbent crystal rotated
by an angle alpha about the Y axis with respect to the crystal surface.

The crystal itself is set in the X-Z plane positioned such that the long axis of the crystal surface coincides with
the Z-axis, withs normal pointing in the poisitivce Y-direction.

N.B. The component does not work for rays hitting the back of the monochromator.

Bragg_crystal_BC.comp is written by Marcus H. Mendenhall, NIST, Gaithersburg, MD, USA
It is based on the full vector math and exact solution  of the dispersion relation in
Batterman and Cole, Reviews of Modern Physics 36 number 3, page 681, July 1964

This code has been validated against both experimental data
(2 channel-cut 3-bounce Si 440 crystals together in non-dispersive mode, at Cu kalpha)
and against theoretical rocking rocking curves from XOP for Si220 at Sc kalpha and Si440 at Cu kalpha.

Non-copyright notice:
Contributed by the National Institute of Standards and Technology; not subject to copyright in the United States.
This is not an official contribution, in that the results are in no way certified by NIST.

Example: Bragg_crystal_BC( length=0.05, width=0.02, V=160.1826, h=1, k=1, l=1, alphay=1)
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| length | m | z depth (length) of the crystal. | 0.05 |
| width | m | x width of the crystal. | 0.02 |
| V | AA^3 | unit cell volume | 160.1826 |
| form_factors |  |  | "FormFactors.txt" |
| material |  | Si, Ge (maybe also GaAs?) | "Si.txt" |
| alphax |  |  | 0.0 |
| alphay |  |  | 1.0 |
| alphaz |  |  | 0.0 |
| R0 |  | Reflectivity. Overrides the computed Darwin reflectivity. Probably only useful for debugging. | 0 |
| debye_waller_B | AA^2 | Debye-Waller temperature factor, M=B*(sin(theta)/lambda)^2*(2/3), default=silicon at room temp. | 0.4632 |
| crystal_type |  | 1 => Mx_crystal_explicit: provide explicit real and imaginary form factor multipliers structure_factor_scale_r, structure_factor_scale_i; 2 => Mx_crystal_diamond: diamond; 3 => Mx_crystal_fcc: fcc; 4 => Mx_crystal_fcc: bcc | 1 |
| h |  | Miller index of reflection | 1 |
| k |  | Miller index of reflection | 1 |
| l |  | Miller index of reflection | 1 |
| structure_factor_scale_r |  |  | 0.0 |
| structure_factor_scale_i |  |  | 0.0 |
| verbose |  | if non-zero: Output more information (warnings and messages) to the console. | 0 |

## Links

- [Source code](/Users/peterwillendrup/Projects/willend-McCode/mcxtrace-comps/contrib/Bragg_crystal_BC.comp) for `Bragg_crystal_BC.comp`.
- material datafile obtained from http://physics.nist.gov/cgi-bin/ffast/ffast.pl

---

*Generated on mcxtrace 3.99.99.*