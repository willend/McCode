# The `Monochromator_2foc` Component

*McStas: Double bent monochromator with multiple slabs*

## Identification

- **Site:** 
- **Author:** <a href="mailto:plink@physik.tu-muenchen.de">Peter Link</a>.
- **Origin:** Uni. Gottingen (Germany)
- **Date:** Feb. 12,1999

## Description

```text
Double bent monochromator which uses a small-mosaicity approximation as well
as the approximation vy^2 << vz^2 + vx^2.
Second order scattering is neglected.
For an unrotated monochromator component, the crystal plane lies in the y-z
plane (ie. parallel to the beam).
When curvatures are set to 0, the monochromator is flat.
The curvatures approximation for parallel beam focusing to distance L, with
monochromator rotation angle A1 are:
RV = 2*L*sin(DEG2RAD*A1);
RH = 2*L/sin(DEG2RAD*A1);

Example: Monochromator_2foc(zwidth=0.02, yheight=0.02, gap=0.0005, NH=11, NV=11,
mosaich=30, mosaicv=30, r0=0.7, Q=1.8734)

Example values for lattice parameters
PG       002 DM=3.355 AA (Highly Oriented Pyrolytic Graphite)
PG       004 DM=1.607 AA
Heusler  111 DM=3.362 AA (Cu2MnAl)
CoFe         DM=1.771 AA (Co0.92Fe0.08)b
Ge       311 DM=1.714 AA
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
| reflect | k, R | reflectivity file name of text file as 2 columns | 0 |
| zwidth | m | horizontal width of an individual slab | 0.01 |
| yheight | m | vertical height of an individual slab | 0.01 |
| gap | m | typical gap  between adjacent slabs | 0.0005 |
| NH | columns | number of slabs horizontal | 11 |
| NV | rows | number of slabs vertical | 11 |
| mosaich | arcmin | Horisontal mosaic FWHM | 30.0 |
| mosaicv | arcmin | Vertical mosaic FWHM | 30.0 |
| r0 | 1 | Maximum reflectivity | 0.7 |
| Q | AA-1 | Scattering vector | 1.8734 |
| RV | m | radius of vertical focussing, flat for 0 | 0 |
| RH | m | radius of horizontal focussing, flat for 0 | 0 |
| DM | Angstrom | monochromator d-spacing instead of Q=2*pi/DM | 0 |
| mosaic | arcmin | sets mosaich=mosaicv | 0 |
| width | m | total width of monochromator | 0 |
| height | m | total height of monochromator | 0 |
| verbose | 0/1 | verbosity level | 0 |

## Links

- [Source code](/Users/peterwillendrup/Projects/willend-McCode/mcstas-comps/contrib/Monochromator_2foc.comp) for `Monochromator_2foc.comp`.
- <a href="http://mailman.risoe.dk/pipermail/neutron-mc/1999q1/000133.html">Additional note</a> from <a href="mailto:plink@physik.tu-muenchen.de">Peter Link</a>.

---

*Generated on mcstas 3.99.99.*