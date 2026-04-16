# The `Multilayer_elliptic` Component

*McXtrace: Elliptic multilayer mirror (in XZ)*

## Identification

- **Site:** 
- **Author:** Jana Baltser, Peter Willendrup, Anette Vickery, Andrea Prodi, Erik Knudsen
- **Origin:** NBI
- **Date:** February 2011

## Description

```text
Reads reflectivity values from a data input file (Ref.dat) for a Si/W multilayer.
The multilayer code reflects ray in an ideal geometry, does not include surface imperfections

The mirror is positioned such that the long axis of the mirror elliptical surface coincides with
z-axis

The algorithm:
Incoming photon's coordinates and direction (k-vector) are transformed into an elliptical reference frame
(elliptical parameters are calculated according to the mirror's position and its focusing distances and the
incident angle), the intersection point is then defined. A new, reflected photon is then starting at the
point of intersection.

Example: Multilayer_elliptic(
coating = "Ref_W_B4C.txt", theta = 1.2,
s1 = 1, s2 = 2, length = 0.1, width = 0.1, R0 = 1,
Emin=7, Emax=10, Estep=0.05)
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| coating | str | Datafile containing reflectivity values as a function of q and E. | "Ref_W_B4C.txt" |
| theta | deg | Design angle of incidence. | 1.2 |
| s1 | m | Design distance from the source to the multilayer. | 0 |
| s2 | m | Design focusing distance of the multilayer. | 0 |
| length | m | alternate name for zdepth (obsolete) | 0.5 |
| width | m | alternate name for xwidth (obsolete) | 0.2 |
| R0 | 1 | Maximal reflectivity | 1 |
| Emin | keV | Lower limit of energy interval in datafile. Overrides what's written in the datafile header. | -1 |
| Emax | keV | Upper limit of energy interval in datafile. Overrides what's written in the datafile header. | -1 |
| Estep | keV | Step between energy sample points in datafile. Overrides what's written in the datafile header. | -1 |
| Gamma |  | High electron density fraction of bilayer (in kinematical appr.). | 0 |
| Lambda | m | Thickness of bilayer (in kinematical appr.). | 0 |
| rho_AB |  | Number electron density constrast in bilayer (in kinematical appr.). | 0 |
| N | 1 | Number of bilayers (in kinematical appr.). | 0 |
| xwidth | m | Width of the mirror along X-axis. | 0 |
| zdepth | m | Length of the mirror along Z. | 0 |

## Links

- [Source code](/Users/peterwillendrup/Projects/willend-McCode/mcxtrace-comps/optics/Multilayer_elliptic.comp) for `Multilayer_elliptic.comp`.

---

*Generated on mcxtrace 3.99.99.*