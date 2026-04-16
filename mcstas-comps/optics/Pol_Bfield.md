# The `Pol_Bfield` Component

*McStas: Magnetic field component.*

## Identification

- **Site:** 
- **Author:** Erik B Knudsen, Peter Christiansen and Peter Willendrup
- **Origin:** RISOE
- **Date:** July 2011

## Description

```text
Region with a definable magnetic field.

The component is nestable if the concentric flag is set (the default). This means that it may have a
construction like the following:
// START MAGNETIC FIELD
COMPONENT msf =
Pol_Bfield(xwidth=0.08, yheight=0.08, zdepth=0.2, Bx=0, By=-0.678332e-4, Bz=0)
AT (0, 0, 0) RELATIVE armMSF

// OTHER COMPONENTS INSIDE THE MAGNETIC FIELD CAN BE PLACED HERE

// STOP MAGNETIC FIELD
COMPONENT msf_stop = Pol_simpleBfield_stop(magnet_comp_stop=msf)
AT (0, 0, 0) RELATIVE armMSF

Note that if you have objects within the magnetic field that extend outside it you may get
wrong results, because propagation within the field will then possibly extend outside, e.g.
when using a tabled field. The evaluated field will then use the nearest defined field point
_also_ outside the defintion area. If these outside-points have a non-zero field precession will
continue - even after the neutron has left the field region.

In between the two component instances the propagation routine
PROP_DT also handles spin propagation.
The current algorithm used for spin propagation is:
SimpleNumMagnetPrecession
in pol-lib.

Example: Pol_Bfield(xwidth=0.1, yheight=0.1, zdepth=0.2, Bx=0, By=1, Bz=0)
Pol_Bfield(xwidth=0.1, yheight=0.1, zdepth=0.2, field_type=1)

Functions supplied by the system are (the number is the ID of the function to be given as the field_type parameter:
1. Constant magnetic field: Constant field (Bx,By,Bz) within the region
2. Rotating magnetic_field: Field is initially (0,By,0) but after a length of zdepth
has rotated to (By,0,0)
3. Majorana magnetic_field: Field is initially (Bx,By,0) with By<<Bx, then linearly transforms to
(-Bx,By,0) at z=zdepth.
4. MSF field:
5. RF field: A radio frequency field is modeled by an implcit use of a roating frame.
6. Gradient field: Similar to Majorana by without an x-component to the field. I.e. it (0,By,0) at z=0, and
becomes (0,-By,0) AT z=zdepth.

If the concentric parameter is set to 1 the magnetic field is turned on by an
instance of this component, and turned off by an instance of Pol_simpleBfield_stop.
Anything in between is considered inside the field.
If concentric is zero the field is considered a closed component - neutrons are propagated
through the field region, and no other components are permitted inside the field.
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| field_type |  | ID of function describing the magnetic field. 1:constant field, 2: rotating fiel, 3: majorana type field, 4: MSF, 5: RF-field, 6: gradient field. | 0 |
| xwidth | m | Width of opening. | 0 |
| yheight | m | Height of opening. | 0 |
| zdepth | m | Length of field. | 0 |
| radius | m | Radius of field if it is cylindrical or spherical. | 0 |
| Bx | T | Parameter used for x composant of field. | 0 |
| By | T | Parameter used for y composant of field. | 0 |
| Bz | T | Parameter used for z composant of field. | 0 |
| concentric |  | Allow components and/or other fields inside field. Requires a subsequent Pol_simpleBfield_stop component. | 1 |

## Links

- [Source code](/Users/peterwillendrup/Projects/willend-McCode/mcstas-comps/optics/Pol_Bfield.comp) for `Pol_Bfield.comp`.

---

*Generated on mcstas 3.99.99.*