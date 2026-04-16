# The `Bragg_crystal` Component

*McXtrace: Perfect, reflecting crystal with common cubic structures (diamond, fcc, or bcc, and others if symmetry form factor multipliers provided explicitly)*

## Identification

- **Site:** 
- **Author:** Marcus H Mendenhall, NIST <marcus.mendenhall@nist.gov>
- **Origin:** NIST, Gaithersburg, MD, USA
- **Date:** December 1, 2016

## Description

```text
Bragg_crystal.comp supercedes Perfect_Crystal.comp with major edits and corrections.

For details see:
The optics of focusing bent-crystal monochromators on X-ray powder diffractometers with application to lattice parameter determination and microstructure analysis,
Marcus H. Mendenhall,* David Black and James P. Cline, J. Appl. Cryst. (2019). 52, https://doi.org/10.1107/S1600576719010951

Reads atomic formfactors from a data input file.

The crystal code reflects ray in an ideal geometry, i.e. does not include surface imperfections or mosaicity.
The crystal planes from which the reflection is made lies in the X-Z plane on the unbent crystal rotated
by an angle alpha about the Y axis with respect to the crystal surface.

The crystal itself is set in the X-Z plane positioned such that the long axis of the crystal surface coincides with
the Z-axis, with its normam pointing in the positve Y-direction. The angle between the Bragg planes and the crystal surface is alpha

This code has been validated against both experimental data
(2 channel-cut 3-bounce Si 440 crystals together in non-dispersive mode, at Cu kalpha)
and against theoretical rocking rocking curves from XOP for Si220 at Sc kalpha and Si440 at Cu kalpha.

Changelog:
- Off-axis rays fixed June 2015 so axial divergence corrections are right
- Inclusion of polarization and temperature dependence (via Debye-Waller factor), June-September 2015
- Errors in complex arithmetic in DarwinReflectivity2 corrected, September 2015, MHM
- Symmetries for form factors corrected 20150924
- Rotation code updated to use exact DarwinReflectivity Theta0, Thetah so answer is right even if alpha != 0. 20151009 MHM
- Results for (1,1,1) etc. with complex form factor made to agree with XOP. December 1st, 2016

Notation follows Tadashi Matsushita and Hiro-O Hashizume, X-RAY MONOCHROMATORS. Handbook on Synchrotron Radiation,North-Holland Publishing Company, 1:263–274, 1983.

Non-copyright notice:
Contributed by the National Institute of Standards and Technology; not subject to copyright in the United States.
This is not an official contribution, in that the results are in no way certified by NIST.

Example: Bragg_crystal(
length=0.05, width=0.02, V=160.1826, h=1, k=1, l=1, alpha=0)
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| length | m | z depth (length) of the crystal. | 0.05 |
| width | m | x width of the crystal. | 0.02 |
| V | AA^3 | Unit cell volume | 160.1826 |
| form_factors | str | File for X-ray form factors | "FormFactors.txt" |
| material | str | Si, Ge (maybe also GaAs?) | "Si.txt" |
| alpha | rad | Asymmetry angle (alpha=0 for symmetric reflection, ie the Bragg planes are parallel to the crystal surface). alpha is defined so that positive alpha reduces the Bragg angle to the plane i.e. alpha=Thetain grazes the planes. if alpha!=0,  one should restrict to rays which have small kx values, since otherwise the alpha rotation is not around the diffraction axis. | 0.0 |
| R0 | 0-1 | Reflectivity. Overrides the computed Darwin reflectivity. Probably only useful for debugging. | 0 |
| debye_waller_B | AA^2 | Debye-Waller temperature factor, M=B*(sin(theta)/lambda)^2*(2/3), default=silicon at room temp. | 0.4632 |
| crystal_type | 1 | 1 => Mx_crystal_explicit: provide explicit real and imaginary form factor multipliers structure_factor_scale_r, structure_factor_scale_i; 2 => Mx_crystal_diamond: diamond; 3 => Mx_crystal_fcc: fcc; 4 => Mx_crystal_fcc: bcc | 1 |
| h | 1 | Miller index of reflection | 1 |
| k | 1 | Miller index of reflection | 1 |
| l | 1 | Miller index of reflection | 1 |
| structure_factor_scale_r | 1 | real      form factor multiplier | 0.0 |
| structure_factor_scale_i | 1 | imaginary form factor multiplier | 0.0 |

## Links

- [Source code](/Users/peterwillendrup/Projects/willend-McCode/mcxtrace-comps/optics/Bragg_crystal.comp) for `Bragg_crystal.comp`.

---

*Generated on mcxtrace 3.99.99.*