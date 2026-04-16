# The `Guide_anyshape_r` Component

*McStas: Reflecting surface (guide and mirror) with any shape, defined from an OFF file
and a patch to allow m-, alpha- and W-values added per polygon face.
Derived from Guide_anyshape / Guide_anyshape_r .*

## Identification

- **Site:** 
- **Author:** Emmanuel Farhi, adapted by Peter Link and Gaetano Mangiapia
- **Origin:** ILL/MLZ
- **Date:** August 4th 2010

## Description

```text
This is a reflecting object component, derived from Guide_anyshape.
Its shape, as well as m-, alpha- and W-values (IN THIS ORDER) for each face, are defined from
an OFF file, given with its file name. The object size is set as given from the file, where
dimensions should be in meters. The bounding box may be re-scaled by specifying
xwidth,yheight,zdepth parameters. The object may optionally be centered when
using 'center=1'.

If in input only the values of R0 and Qc are specified, leaving m, alpha and W all null, then
Guide_anyshape_g will use the values of these last three parameters that are specified in the OFF
file for each face: floating point based values may be provided for them.
In case at least one among m, alpha and W is not null, then Guide_anyshape_g will use these
values as input (common for all the faces), ignoring those specified in the OFF file

The complex OFF/PLY geometry option handles any closed non-convex polyhedra.
It supports the OFF and NOFF file format but not COFF (colored faces).
Standard .OFF files may be generated from XYZ data using:
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
| alpha | AA | Slope of reflectivity | 0 |
| m | 1 | m-value of material. Zero means completely absorbing. | 0 |
| W | AA-1 | Width of supermirror cut-off | 0 |
| geometry | str | Name of the OFF/PLY file describing the guide geometry | 0 |

## Links

- [Source code](/Users/peterwillendrup/Projects/willend-McCode/mcstas-comps/contrib/Guide_anyshape_r.comp) for `Guide_anyshape_r.comp`.
- <a href="http://www.geomview.org">Geomview and Object File Format (OFF)</a>
- Java version of Geomview (display only) <a href="http://www.holmes3d.net/graphics/roffview/">jroff.jar</a>
- <a href="http://qhull.org">qhull</a>
- <a href="http://www.cs.ucdavis.edu/~amenta/powercrust.html">powercrust</a>

---

*Generated on mcstas 3.99.99.*