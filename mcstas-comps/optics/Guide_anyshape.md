# The `Guide_anyshape` Component

*McStas: Reflecting surface (guide and mirror) with any shape, defined from an OFF file.*

## Identification

- **Site:** 
- **Author:** Emmanuel Farhi
- **Origin:** ILL
- **Date:** August 4th 2010

## Description

```text
This is a reflecting object component. Its shape is defined from an OFF file,
given with its file name. The object size is set as given from the file, where
dimensions should be in meters. The bounding box may be re-scaled by specifying
xwidth,yheight,zdepth parameters. The object may optionally be centered when
using 'center=1'.

The reflectivity is specified either from the usual parametric description
R0,Qc,alpha,W,m, or from a reflectivity file 'reflect' with a 2 column
format [q(Angs-1) R(0-1)].

The complex OFF/PLY geometry option handles any closed non-convex polyhedra.
It supports the OFF and NOFF file format but not COFF (colored faces).
Such files may be generated from XYZ data using:
qhull < coordinates.xyz Qx Qv Tv o > geomview.off
or
powercrust coordinates.xyz
and viewed with geomview or java -jar jroff.jar (see below).
The default size of the object depends of the OFF file data, but its
bounding box may be resized using xwidth,yheight and zdepth.
PLY geometry files are also supported.
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| xwidth | m | Redimension the object bounding box on X axis is non-zero | 0 |
| yheight | m | Redimension the object bounding box on Y axis is non-zero | 0 |
| zdepth | m | Redimension the object bounding box on Z axis is non-zero | 0 |
| center | 1 | When set to 1, the object will be centered w.r.t. the local coordinate frame | 0 |
| transmit | 1 | When true, non reflected neutrons are transmitted through the surfaces, instead of being absorbed. No material absorption is taken into account though | 0 |
| R0 | 1 | Low-angle reflectivity | 0.99 |
| Qc | AA-1 | Critical scattering vector | 0.0219 |
| alpha | AA | Slope of reflectivity | 3 |
| m | 1 | m-value of material. Zero means completely absorbing. | 2 |
| W | AA-1 | Width of supermirror cut-off | 0.003 |
| reflect | q(Angs-1) R(0-1) | (str)  Reflectivity file name. Format | 0 |
| geometry | str | Name of the OFF/PLY file describing the guide geometry | 0 |

## Links

- [Source code](/Users/peterwillendrup/Projects/willend-McCode/mcstas-comps/optics/Guide_anyshape.comp) for `Guide_anyshape.comp`.
- <a href="http://www.geomview.org">Geomview and Object File Format (OFF)</a>
- Java version of Geomview (display only) <a href="http://www.holmes3d.net/graphics/roffview/">jroff.jar</a>
- <a href="http://qhull.org">qhull</a>
- <a href="http://www.cs.ucdavis.edu/~amenta/powercrust.html">powercrust</a>

---

*Generated on mcstas 3.99.99.*