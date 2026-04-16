# The `Perfect_crystal` Component

*McXtrace: Perfect crystal with diamond or zincblende structure*

## Identification

- **Site:** 
- **Author:** Anette Vickery, Andrea Prodi, Erik Knudsen
- **Origin:** NBI
- **Date:** April 2011

## Description

```text
Reads atomic formfactors from a data input file.
The PerfectCrystal code reflects ray in an ideal geometry, does not include surface imperfections or mosaicity

The crystal is positioned such that the long axis of the crystal surface coincides with
z-axis. The angle between the Bragg planes and the crystal surface is alpha


The algorithm:
Incoming photon's coordinates and direction (k-vector) are transformed into an elliptical reference frame
(elliptical parameters are calculated according to the mirror's position and its focusing distances and the  * incident angle), the intersection point is then defined.
A new, reflected photon is then starting at the point of intersection.
Notation follows Tadashi Matsushita and Hiro-O Hashizume, X-RAY MONOCHROMATORS. Handbook on Synchrotron Radiation,North-Holland Publishing Company, 1:263–274, 1983.
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| form_factors |  |  | "FormFactors.txt" |
| material |  |  | "Si.txt" |
| R0 |  | Reflectivity. Overrides the computed Darwin reflectivity. Probably only useful for debugging. | 0 |
| length | m | length of the crystal (along z-axis) | 0.05 |
| width | m | width of the crystal (along x-axis) | 0.02 |
| V | AA^3 | unit cell volum | 160.1826 |
| h |  | Miller index of reflection | 1 |
| k |  | Miller index of reflection | 1 |
| l |  | Miller index of reflection | 1 |
| alpha | rad | asymmetry angle (alpha=0 for symmetric reflection, ie the Bragg planes are parallel to the crystal surface) | 0.0 |

## Links

- [Source code](/Users/peterwillendrup/Projects/willend-McCode/mcxtrace-comps/obsolete/Perfect_crystal.comp) for `Perfect_crystal.comp`.

---

*Generated on mcxtrace 3.99.99.*