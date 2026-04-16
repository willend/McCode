# The `Lens_simple` Component

*McXtrace: Simple refractive x-ray lens*

## Identification

- **Site:** 
- **Author:** Erik Knudsen
- **Origin:** Risoe
- **Date:** June 16, 2009

## Description

```text
Models a stack of N refractive lenses, with a radius of curvature, r, at the apex.
The model is a thin-lens approximation where photons are refracted in a the XY plane
at Z=0. Absorption is generally disregarded may be handled through the use of the optional
transmission parameter T, where 0<=T<=1.
Thus, the lens has the focal length of f=R/(2*N*&delta) where the x-ray refractive
index is written: n = 1 - &delta + i &beta.

Example: Lens_simple(xwidth=1e-5, yheight=1e-5, material_datafile="Be.txt",N=100,r=0.3e-3)
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| xwidth | m | Width of lens aperture. | 0 |
| yheight | m | Height of lens aperture. | 0 |
| radius | m | Radius of lens aperture (overrides xwidth & yheight). | 1e-3 |
| T | 0-1 | Transmission efficiency of the lens. | 1 |
| r | m | The radius of curvature of the lens. | 3e-4 |
| N | 1 | The number of successive lenses in the stack. | 1 |
| verbose | 0/1 | Extra information for debugging. | 0 |
| f | m | Focal length - overrides the material_datafile - and diregards chromatic aberration. | 0 |
| material_datafile |  | File where the material parameters for the lens may be found. Format is similar to what may be found off the NIST website. | "Be.txt" |

## Links

- [Source code](/Users/peterwillendrup/Projects/willend-McCode/mcxtrace-comps/optics/Lens_simple.comp) for `Lens_simple.comp`.
- material datafile obtained from http://physics.nist.gov/cgi-bin/ffast/ffast.pl

---

*Generated on mcxtrace 3.99.99.*