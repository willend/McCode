# The `Absorption_sample` Component

*McXtrace: Sample component with absorbing materials.*

## Identification

- **Site:** 
- **Author:** Erik B Knudsen
- **Origin:** Risoe
- **Date:** March 2011

## Description

```text
A sample component consisting of a volume of one material and volume of another
material inside. This is useful as a phantom for simulating tomography experiments.
The inner material can be left unset (all 0), to only have one volume.

Sample shape may be a cylinder, a sphere, a box or any other shape
box/plate:       xwidth x yheight x zdepth
cylinder:        radius x yheight
sphere:          radius (yheight=0)
any shape:       geometry=OFF/PLY file

Example: Absorption_sample( material_datafile_o="Mn.txt", xwidth_o = 0.5, yheight_o = 0.5, zdepth_o = 0.0001, rho_o=7.15 )
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| material_datafile_i | str | Name of file containing material data for inclusion. | "" |
| material_datafile_o | str | Name of file containing material data for outer volume. | "" |
| radius_o | m | Radius of "outer" enclosing material cylinder (0) | 0 |
| xwidth_o | m | Width of "outer" enclosing material box (yheight) | 0 |
| yheight_o | m | Height of "outer enclosing material box (1) | 1 |
| zdepth_o | m | Thickness of outer enclosing material box (yheight) | 0 |
| radius_i | m | Radius of "inner" enclosed material cylinder (0) | 0 |
| xwidth_i | m | Width of "inner" enclosed material box (yheight) | 0 |
| yheight_i | m | Height of "inner enclosed material (1) | 0.0 |
| zdepth_i | m | Thickness of inner enclosed material box (yheight) | 0 |
| x_i | m | Center x-coordinate of "inner" object | 0 |
| y_i | m | Center y-coordinate of "inner" object | 0 |
| z_i | m | Center z-coordinate of "inner" object | 0 |
| rho_i | g/cm^3 | density of the enclosed material | 0 |
| rho_o | g/cm^3 | density of the enclosing material | 0 |
| geometry_i | str | Name of an inner Object File Format (OFF) or PLY file for complex geometry. The OFF/PLY file may be generated from XYZ coordinates using qhull/powercrust [str] | "" |
| geometry_o | str | Name of the outer Object File Format (OFF) or PLY file for complex geometry. The OFF/PLY file may be generated from XYZ coordinates using qhull/powercrust | "" |

## Links

- [Source code](/Users/peterwillendrup/Projects/willend-McCode/mcxtrace-comps/samples/Absorption_sample.comp) for `Absorption_sample.comp`.
- Meshlab https://www.meshlab.net/
- Geomview and Object File Format (OFF) <http://www.geomview.org>
- Java version of Geomview (display only) jroff.jar <http://www.holmes3d.net/graphics/roffview/>
- qhull <http://qhull.org>
- Powercrust https://www.cs.ucdavis.edu/~amenta/powercrust.html

---

*Generated on mcxtrace 3.99.99.*