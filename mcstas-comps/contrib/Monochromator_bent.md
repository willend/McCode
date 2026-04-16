# The `Monochromator_bent` Component

*McStas: A bent crystal monochromator. Based on the model implemented by Jan &Scaron;aroun in NIMA 529 (2004) pp 162-165.
Mosacity and bending radius can be set.*

## Identification

- **Site:** 
- **Author:** Daniel Lomholt Christensen <dlc@math.ku.dk> with help from Jan &Scaron;aroun
- **Origin:** ILL/NBI
- **Date:** 24 August 2023

## Description

```text
This monochromator is an array of crystals, that can be bent.
The crystals are placed by the user in the x,y,z pos and rot parameters.
The crystal is bent, so that it follows a curve on a cylinder of radius_x.
The monochromator lies along the z plane, so when a diffraction angle of theta
is desired, it should just be inserted in the ROTATED parameter around
the y-axis.
Instruments that showcase the use of this component is the
"Test_monochromator_bent.instr", and the "ILL_SALSA.instr" under the examples folder.
SALSA showcases its complex use in a real instrument, while Test_monochromator_bent
makes a simple show of its capabilities.
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| zwidth | m | Width of each crystal without bending. | 0.2 |
| yheight | m | Height of each crystal without bending. | 0.1 |
| xthickness | m | Thickness of each crystal without bending. | 0.0005 |
| radius_x | m | Radius of the circle the monochromator bends on in the plane. Can be negative. | 2 |
| radius_y | m | Radius of the (very large) circle the monochromator bends on as a side effect of the horizontal bending. The code assumes that it is so small that it does not affect the points of intersection appreciatively of the crystal. | 0 |
| plane_of_reflection | "Si400" | The plane of reflection from the material. The list of possible reflections can be seen in the source code. | "Si400" |
| angle_to_cut_horizontal | degrees | Angle between cut and normal of crystal slab, horizontally | 0 |
| mosaicity | arcmin | Gaussian mosaicity of the crystal. Always the horizontal mosaicity | 30 |
| mosaic_anisotropy | 1 | Anisotropy of the mosaicity, changes vertical mosaicity to be mosaic_anisotropy*mosaicity | 1 |
| n_crystals | # | Number of crystals in your array. | 1 |
| domainthickness | &#956;m | Thickness of the crystal domains. | 10 |
| temperature | K | Temperature of the monochromator in Kelvin. | 300 |
| optimize |  | Flag to tell if the component should optimize for reflections or not. | 0 |
| x_pos | vector | x-Position of each crystal | NULL |
| y_pos | vector | y-Position of each crystal | NULL |
| z_pos | vector | z-Position of each crystal | NULL |
| x_rot | vector | Rotation around x-axis for each crystal | NULL |
| y_rot | vector | Rotation around y-axis for each crystal | NULL |
| z_rot | vector | Rotation around z-axis for each crystal NOTE: Rotations happen around x, then y, then z. | NULL |
| verbose |  | Verbosity of the monochromator. Used for debugging. | 0 |
| draw_as_rectangles |  | Draw the monochromators as boxes. DOES NOT WORK WHEN USING _rot parameters. | 0 |

## Links

- [Source code](/Users/peterwillendrup/Projects/willend-McCode/mcstas-comps/contrib/Monochromator_bent.comp) for `Monochromator_bent.comp`.
- <a href="https://doi.org/10.1016/j.nima.2004.04.197">Jan &Scaron;aroun NIM A Volume 529, Issue 1-3 (2004), pp162-165</a>

---

*Generated on mcstas 3.99.99.*