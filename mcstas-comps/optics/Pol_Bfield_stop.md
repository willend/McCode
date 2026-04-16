# The `Pol_Bfield_stop` Component

*McStas: Magnetic field component.*

## Identification

- **Site:** 
- **Author:** Erik B Knudsen, Peter Christiansen, and Peter Willendrup
- **Origin:** RISOE
- **Date:** August 2006

## Description

```text
End of magnetic field region defined by the latest preceeding Pol_Bfield component.

The component is concentric. It means that it requires a

// START MAGNETIC FIELD
COMPONENT msf =
Pol_Bfield(xw=0.08, yh=0.08, length=0.2, Bx=0, By=-0.678332e-4, Bz=0)
AT (0, 0, 0) RELATIVE armMSF

// HERE CAN BE OTHER COMPONENTS INSIDE THE MAGNETIC FIELD

// STOP MAGNETIC FIELD
COMPONENT msfCp = Pol_Bfield_stop()
AT ("SOMEWHERE") RELATIVE armMSF

In between the two components the propagation routine
PROP_DT also handles the spin propagation.
The current algorithm used for spin propagation is:
SimpleNumMagnetPrecession
in pol-lib.
and does not handle gravity.

GRAVITY: NO
POLARISATION: YES

Example: Pol_Bfield_stop()
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| geometry | str | Name of an Object File Format (OFF) or PLY file for complex field-geometry. | "" |
| yheight | m | Height of opening. | 0 |
| xwidth | m | Width of opening. | 0 |
| zdepth | m | Length of field. | 0 |
| radius | m | Radius of field if it is cylindrical or spherical. | 0 |

## Links

- [Source code](/Users/peterwillendrup/Projects/willend-McCode/mcstas-comps/optics/Pol_Bfield_stop.comp) for `Pol_Bfield_stop.comp`.

---

*Generated on mcstas 3.99.99.*