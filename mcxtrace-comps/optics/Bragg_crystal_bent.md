# The `Bragg_crystal_bent` Component

*McXtrace: Bent, perfect, reflecting crystal with common cubic structures (diamond, fcc, or bcc, and others if symmetry form factor multipliers provided explicitly)*

## Identification

- **Site:** 
- **Author:** Marcus H Mendenhall, NIST <marcus.mendenhall@nist.gov>
- **Origin:** Marcus H. Mendenhall, NIST, Gaithersburg, MD, USA
- **Date:** December 1, 2016

## Description

```text
Bragg_crystal_bent.comp supercedes Perfect_Crystal_bent.comp with major edits and corrections.

Reads atomic formfactors from a data input file.

The crystal code reflects ray in an ideal geometry, does not include surface imperfections or mosaicity
The crystal planes from which the reflection is made must lie in the X-Z plane on the unbent crystal rotated
by an angle alpha about the x axis with respect to the crystal surface.

The external geometry of the crystal follows that of Elliptic_mirror.comp.
I.e. the crystal is positioned such that the a-axis of the ellipsoid is on the
z-axis, the b-axis is along the y-axis and the c is along the x-axis.
The reference point of the crystal is the ellipsoid centre, offset by one half-axis along the y-axis.
(See the component manual for Elliptic_mirror for a drawing).

N.B. The component does not work for negative curvature, nor for rays hitting the back of the monochromator.

Notation follows Tadashi Matsushita and Hiro-O Hashizume, X-RAY MONOCHROMATORS. Handbook on Synchrotron Radiation,North-Holland Publishing Company, 1:263–274, 1983.

Non-copyright notice:
Contributed by the National Institute of Standards and Technology; not subject to copyright in the United States.
This is not an official contribution, in that the results are in no way certified by NIST.

NOTE: elliptical coordinate code and documentation taken from Mirror_elliptic.comp distributed in McXtrace v1.2
However, the coordinates are rotated to be consistent with Bragg_crystal_flat.comp and Perfect_Crystal.comp.
Idealized elliptic mirror with surface ellipse and lattice ellipses independent, to allow construction of
Johansson optics, for example.

Example: Bragg_crystal_bent(
length=0.05, width=0.02, V=160.1826, h=1, k=1, l=1, alpha=0,y_b=1, lattice_y_b=1, z_c=1, lattice_z_c=1)
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| x_a | m | 1st short half axis (along x). Commonly set to zero, which really implies infinite value, so crystal is an elliptic cylinder. | 0 |
| y_b | m | 2nd short half axis (along y), which is also the presumed near-normal direction, reflection near the y-z plane. | 1.0 |
| z_c | m | Long  half axis (along z). Commonly a=0. b=c, which creates a circular cylindrical surface. | 1.0 |
| lattice_x_a | m | Curvature matrix for underlying lattice, for bent/ground/rebent crystals THERE HAS BEEN NO TESTING for the case in which lattice_x_a != x_a. | 0 |
| lattice_y_b | m | Curvature matrix for underlying lattice, for bent/ground/rebent crystals | 1.0 |
| lattice_z_c | m | Curvature matrix for underlying lattice, for bent/ground/rebent crystals | 1.0 |
| length | m | z depth (length) of the crystal. | 0.05 |
| width | m | x width of the crystal. | 0.02 |
| V | AA^3 | Unit cell volume | 160.1826 |
| form_factors | str | File for X-ray form factors | "FormFactors.txt" |
| material | str | Si, Ge (maybe also GaAs?) | "Si.txt" |
| alpha | rad | Asymmetry angle (alpha=0 for symmetric reflection, ie the Bragg planes are parallel to the crystal surface); alpha is defined so that positive alpha reduces the Bragg angle to the plane i.e. alpha=Thetain grazes the planes; if alpha!=0,  one should restrict to rays which have small kx values, since otherwise the alpha rotation is not around the diffraction axis. | 0.0 |
| R0 | 0-1 | Reflectivity. Overrides the computed Darwin reflectivity. Probably only useful for debugging. | 0 |
| debye_waller_B | AA^2 | Debye-Waller temperature factor, M=B*(sin(theta)/lambda)^2*(2/3), default=silicon at room temp. | 0.4632 |
| crystal_type | 1 | 1 => Bragg_crystal_explicit: provide explicit real and imaginary form factor multipliers structure_factor_scale_r, structure_factor_scale_i; 2 => Bragg_crystal_diamond: diamond; 3 => Bragg_crystal_fcc: fcc; 4 => Bragg_crystal_fcc: bcc | 1 |
| h | 1 | Miller index of reflection | 1 |
| k | 1 | Miller index of reflection | 1 |
| l | 1 | Miller index of reflection | 1 |
| structure_factor_scale_r | 1 | real      form factor multiplier | 0.0 |
| structure_factor_scale_i | 1 | imaginary form factor multiplier | 0.0 |

## Links

- [Source code](/Users/peterwillendrup/Projects/willend-McCode/mcxtrace-comps/optics/Bragg_crystal_bent.comp) for `Bragg_crystal_bent.comp`.
- material datafile obtained from http://physics.nist.gov/cgi-bin/ffast/ffast.pl

---

*Generated on mcxtrace 3.99.99.*