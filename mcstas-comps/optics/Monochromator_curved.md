# The `Monochromator_curved` Component

*McStas: Double bent multiple crystal slabs with anisotropic gaussian mosaic.*

## Identification

- **Site:** 
- **Author:** Emmanuel Farhi, Kim, Lefmann, Peter Link
- **Origin:** <a href="http://www.ill.fr">ILL</a>
- **Date:** Aug. 24th 2001

## Description

```text
Double bent infinitely thin mosaic crystal, useful as a monochromator or
analyzer. which uses a small-mosaicity approximation and taking into account
higher  order scattering. The mosaic is anisotropic gaussian, with different
FWHMs in the Y and Z directions. The scattering vector is perpendicular to the
surface. For an unrotated monochromator component, the crystal plane lies in
the y-z plane (ie. parallel to the beam). The component works in reflection, but
also transmits the non-diffracted beam. Reflectivity and transmission files may
be used. The slabs are positioned in the vertical plane (not on a
cylinder/sphere), and are rotated according to the curvature radius.
When curvatures are set to 0, the monochromator is flat.
The curvatures approximation for parallel beam focusing to distance L, with
monochromator rotation angle A1 are:
RV = 2*L*sin(DEG2RAD*A1);
RH = 2*L/sin(DEG2RAD*A1);

When you rotate the component by A1 = asin(Q/2/Ki)*RAD2DEG, do not forget to
rotate the following components by A2=2*A1 (for 1st order) !

Example: Monochromator_curved(zwidth=0.01, yheight=0.01, gap=0.0005, NH=11, NV=11, mosaich=30.0, mosaicv=30.0, r0=0.7, Q=1.8734)

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
| reflect | str | reflectivity file name of text file as 2 columns [k, R] | "NULL" |
| transmit | str | transmission file name of text file as 2 columns [k, T] | "NULL" |
| zwidth | m | horizontal width of an individual slab | 0.01 |
| yheight | m | vertical height of an individual slab | 0.01 |
| gap | m | typical gap  between adjacent slabs | 0.0005 |
| NH | int | number of slabs horizontal | 11 |
| NV | int | number of slabs vertical | 11 |
| mosaich | arc minutes | Horisontal mosaic FWHM | 30.0 |
| mosaicv | arc minutes | Vertical mosaic FWHM | 30.0 |
| r0 | 1 | Maximum reflectivity. O unactivates component | 0.7 |
| t0 | 1 | transmission efficiency | 1.0 |
| Q | AA-1 | Scattering vector | 1.8734 |
| RV | m | radius of vertical focussing. flat for 0 | 0 |
| RH | m | radius of horizontal focussing. flat for 0 | 0 |
| DM | AA | monochromator d-spacing instead of Q=2*pi/DM | 0 |
| mosaic | arc minutes | sets mosaich=mosaicv | 0 |
| width | m | total width of monochromator, along Z | 0 |
| height | m | total height of monochromator, along Y | 0 |
| verbose | 0/1 | verbosity level | 0 |
| order | 1 | specify the diffraction order, 1 is usually prefered. Use 0 for all | 0 |

## Links

- [Source code](/Users/peterwillendrup/Projects/willend-McCode/mcstas-comps/optics/Monochromator_curved.comp) for `Monochromator_curved.comp`.
- <a href="http://mcstas.risoe.dk/pipermail/neutron-mc/1999q1/000133.html">Additional note</a> from Peter Link.
- Obsolete Mosaic_anisotropic by Kristian Nielsen
- Contributed Monochromator_2foc by Peter Link

---

*Generated on mcstas 3.99.99.*