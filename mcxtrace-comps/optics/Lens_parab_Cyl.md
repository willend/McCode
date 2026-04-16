# The `Lens_parab_Cyl` Component

*McXtrace: X-ray compound refractive lens (CRL) with a parabolic cylinder shape*

## Identification

- **Site:** 
- **Author:** Jana Baltser and Erik Knudsen
- **Origin:** NBI
- **Date:** April 2011

## Description

```text
An X-ray compound refractive lens (CRL) with a parabolic cylinder profile focusing in 1D, i.e. onto a line

The lens is invariant along the x-axis and has a parabolic profile along the y-axis defined as z/c = y^2/b^2.
Thus, i.e. it focuses onto a line along the x-axis.
N>1 means that a stack of lenses is to be simulated. Each lens consists of a pair of two opposing parabolic surfaces
with a distance d between them. The reference point of the component is at the bottom of the first parabolic
surface.

Example: Lens_parab_Cyl(r=.5e-3,yheight=1.3e-3,xwidth=1.3e-3,d=.1e-3,N=21,
material_datafile="Be.txt")
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| material_datafile | str | Datafile containing f1 constants | "Be.txt" |
| r | m | Radius of curvature (circular approximation at the tip of the profile). | .5e-3 |
| yheight | m | The CRL's aperture along Y. | 1.2e-3 |
| xwidth | m | The width of the CRL in the invariant direction x. | 1.2e-3 |
| d | m | Distance between two surfaces of the lens along the propagation axis. | .1e-3 |
| N | 1 | Number of single lenses in a stack. | 1 |
| rough_z | rad | RMS value of random slope along z. | 0 |
| rough_xy | rad | RMS value of random slope along x and y. | 0 |

## Links

- [Source code](/Users/peterwillendrup/Projects/willend-McCode/mcxtrace-comps/optics/Lens_parab_Cyl.comp) for `Lens_parab_Cyl.comp`.

---

*Generated on mcxtrace 3.99.99.*