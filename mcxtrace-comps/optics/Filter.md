# The `Filter` Component

*McXtrace: Release: McXtrace 1.1

Block of an attenuating material*

## Identification

- **Site:** 
- **Author:** Erik Knudsen
- **Origin:** DTU Physics
- **Date:** Jan 24, 2011

## Description

```text
A chunk of attenuating material. Attenuation is computed through
the effective length travelled within the material.
No scattering is modelled at present.

Filter shape may be a cylinder, a sphere, a box or any other shape.
box/plate:       xwidth x yheight x zdepth
cylinder:        radius x yheight (along Y axis)
sphere:          radius
any shape:       geometry=OFF/PLY_file

Example: Filter(material_datafile="Ge.txt",
geometry="wire.ply",xwidth=0.02,yheight=0,zdepth=0)
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| refraction | 0/1 | If nonzero, refraction is enabled. | 1 |
| fixed_delta | 0/1 | Use a fixed delta to compute refraction - useful for debugging. | 0 |
| material_datafile | str | File where the material parameters for the filter may be found. Format is similar to what may be found off the NIST website. [Be.txt] | "Be.txt" |
| geometry | str | File containing the polygon definition of a general shape object. When xwidth is also given, the object is rescaled accordingly (OFF/PLY) | 0 |
| xwidth | m | Width of block. | 0 |
| yheight | m | Height of block. | 0 |
| zdepth | m | Thickness of block. | 0 |
| radius | m | Radius of cylinder or sphere. | 0 |

## Links

- [Source code](/Users/peterwillendrup/Projects/willend-McCode/mcxtrace-comps/optics/Filter.comp) for `Filter.comp`.
- Meshlab https://www.meshlab.net/
- Geomview and Object File Format (OFF) <http://www.geomview.org>
- Java version of Geomview (display only) jroff.jar <http://www.holmes3d.net/graphics/roffview/>
- qhull <http://qhull.org>
- Powercrust https://www.cs.ucdavis.edu/~amenta/powercrust.html
- material datafile obtained from http://physics.nist.gov/cgi-bin/ffast/ffast.pl

---

*Generated on mcxtrace 3.99.99.*