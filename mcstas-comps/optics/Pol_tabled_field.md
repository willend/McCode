# The `Pol_tabled_field` Component

*McStas: Magnetic field component.*

## Identification

- **Site:** 
- **Author:** Erik B Knudsen, Peter Christiansen and Peter Willendrup
- **Origin:** RISOE
- **Date:** July 2011

## Description

```text
Region with a tabled magnetic field read from file.
The magnetic field is read from a text file where it is
specified as a point cloud with N rows of 6 columns:
x y z Bx By Bz
the B field map is resampled with Stepx*Stepy*Stepz points.
Use Stepx=Stepy=Stepz=0 to skip resampling and use the table as is.
The regions itself may be either a 3D rectangular block, a cylinder with axis along y,
or spherical. Interpolation is done between data-points.
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| xwidth | m | Width of opening. | 0 |
| yheight | m | Height of opening. | 0 |
| zdepth | m | Length of field. | 0 |
| radius | m | Radius of field if it is cylindrical or spherical. | 0 |
| filename | str | File where the magnetic field is tabulated. | "bfield.dat" |
| geometry | str | Name of an Object File Format (OFF) or PLY file for complex field-geometry. | NULL |
| interpol_method | str | Choice of interpolation method "kdtree" (default on CPU) / "regular" (default on GPU) | "default" |

## Links

- [Source code](/Users/peterwillendrup/Projects/willend-McCode/mcstas-comps/optics/Pol_tabled_field.comp) for `Pol_tabled_field.comp`.

---

*Generated on mcstas 3.99.99.*