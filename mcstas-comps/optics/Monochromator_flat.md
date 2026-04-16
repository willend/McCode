# The `Monochromator_flat` Component

*McStas: Flat Monochromator crystal with anisotropic mosaic.*

## Identification

- **Site:** 
- **Author:** Kristian Nielsen
- **Origin:** Risoe
- **Date:** 1999

## Description

```text
Flat, infinitely thin mosaic crystal, useful as a monochromator or analyzer.
For an unrotated monochromator component, the crystal surface lies in the Y-Z
plane (ie. parallel to the beam).
The mosaic is anisotropic gaussian, with different FWHMs in the Y and Z
directions. The scattering vector is perpendicular to the surface.

Example: Monochromator_flat(zmin=-0.1, zmax=0.1, ymin=-0.1, ymax=0.1, mosaich=30.0, mosaicv=30.0, r0=0.7, Q=1.8734)

Monochromator lattice parameter
PG       002 DM=3.355 AA (Highly Oriented Pyrolythic Graphite)
PG       004 DM=1.677 AA
Heusler  111 DM=3.362 AA (Cu2MnAl)
CoFe         DM=1.771 AA (Co0.92Fe0.08)
Ge       111 DM=3.266 AA
Ge       311 DM=1.714 AA
Ge       511 DM=1.089 AA
Ge       533 DM=0.863 AA
Si       111 DM=3.135 AA
Cu       111 DM=2.087 AA
Cu       002 DM=1.807 AA
Cu       220 DM=1.278 AA
Cu       111 DM=2.095 AA
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| zmin | m | Lower horizontal (z) bound of crystal | -0.05 |
| zmax | m | Upper horizontal (z) bound of crystal | 0.05 |
| ymin | m | Lower vertical (y) bound of crystal | -0.05 |
| ymax | m | Upper vertical (y) bound of crystal | 0.05 |
| zwidth | m | Width of crystal, instead of zmin and zmax | 0 |
| yheight | m | Height of crystal, instead of ymin and ymax | 0 |
| mosaich | arc minutes | Horizontal mosaic (in z direction) (FWHM) | 30.0 |
| mosaicv | arc minutes | Vertical mosaic (in y direction) (FWHM) | 30.0 |
| r0 | 1 | Maximum reflectivity | 0.7 |
| Q | 1/angstrom | Magnitude of scattering vector | 1.8734 |
| DM | AA | monochromator d-spacing, instead of Q = 2*pi/DM | 0 |

## Links

- [Source code](/Users/peterwillendrup/Projects/willend-McCode/mcstas-comps/optics/Monochromator_flat.comp) for `Monochromator_flat.comp`.

---

*Generated on mcstas 3.99.99.*