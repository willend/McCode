# The `TwinKB_ML` Component

*McXtrace: Montel optic model (aka side-by-side Kirkpatrick Baez)*

## Identification

- **Site:** 
- **Author:** Jana Baltser, Peter Willendrup, Anette Vickery, Andrea Prodi, Erik Knudsen, Jesper Buch Jensen
- **Origin:** NBI
- **Date:** May 2012

## Description

```text
Models a Montel optic, or Twin Kirkpatrick Baez mirror optic (hence the component name).
The mirror are fully abutting, i.e. there's is no gap between them, and perfectly elliptic.

Reads reflectivity values from a data input file for a W/B4C multilayer.
The multilayer code reflects ray in an ideal geometry, the reflectivity datafile accounts for surface roughness, sigma.

The mirror is positioned such that the long axis of the mirror elliptical surface coincides with the z-axis.

The algorithm:
Incoming photon's coordinates and direction (k-vector) are transformed into an elliptical reference frame
(elliptical parameters are calculated according to the mirror's position and its focusing distances and the  * incident angle), the intersection point is then defined. A new, reflected photon is then starting at the
point of intersection.

Example: TwinKB_ML( theta=1.2, s1=.045 , s2=.9 , length=0.06 , width=0.2 , R0=0 , reflectivity_datafile="Ref_W_B4C.txt")
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| reflectivity_datafile | str | File which contains reflectivities as a function of q. | "Ref.txt" |
| theta | deg | Incident angle | 1.2 |
| **s1** | m | Distance from the source to the multilayer |  |
| **s2** | m | Focusing distance of the multilayer |  |
| length | m | Length of the mirrors | 0.6 |
| width | m | Width of the mirror along x-axis | 0.2 |
| R0 | 0-1 | Constant reflectivity, R0=1 for an ideal situation. If R0=0, the code reads the reflectivity from the datafile | 0 |

## Links

- [Source code](/Users/peterwillendrup/Projects/willend-McCode/mcxtrace-comps/optics/TwinKB_ML.comp) for `TwinKB_ML.comp`.

---

*Generated on mcxtrace 3.99.99.*