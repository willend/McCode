# The `Monochromator_bent_complex` Component

*McStas: A bent crystal monochromator. Based on the model implemented by Jan &Scaron;aroun in NIMA 529 (2004) pp 162-165. Mosacity and bending radius can be set.*

## Identification

- **Site:** 
- **Author:** Daniel Lomholt Christensen <dlc@math.ku.dk> with help from Jan &Scaron;aroun
- **Origin:** ILL/NBI
- **Date:** 2 August 2025

## Description

```text
This component is a more complex implementation of Monochromator_bent.
This component only differs in the fact that it allows and forces the user
to set every single parameter for every single crystal in the crystal array.
An exception to this rule is the plane of reflection, for which one can
choose a single plane of reflection, and that will work for all crystals.
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| zwidth | m | Width of each crystal without bending. | NULL |
| yheight | m | Height of each crystal without bending. | NULL |
| xthickness | m | Thickness of each crystal without bending. | NULL |
| radius_x | m | Radius of the circle the monochromator bends on in the plane. Can be negative. | NULL |
| radius_y | m | Radius of the (very large) circle the monochromator bends on as a side effect of the horizontal bending. The code assumes that it is so small that it does not affect the points of intersection appreciatively of the crystal. | NULL |
| angle_to_cut_horizontal | degrees | Angle between cut and normal of crystal slab, horizontally | NULL |
| mosaicity | arcmin | Gaussian mosaicity of the crystal. Always the horizontal mosaicity | NULL |
| mosaic_anisotropy | 1 | Anisotropy of the mosaicity, changes vertical mosaicity to be mosaic_anisotropy*mosaicity | NULL |
| domainthickness | &#956;m | Thickness of the crystal domains. | NULL |
| temperature | K | Temperature of the monochromator in Kelvin. | NULL |
| plane_of_reflection | string | The plane of reflection from the material. The list of possible reflections can be seen in the source code. Each plane must be separated by a ";", like "Si400;Si111". | "Si400" |
| x_pos | vector | x-Position of each crystal | NULL |
| y_pos | vector | y-Position of each crystal | NULL |
| z_pos | vector | z-Position of each crystal | NULL |
| x_rot | vector | Rotation around x-axis for each crystal | NULL |
| y_rot | vector | Rotation around y-axis for each crystal | NULL |
| z_rot | vector | Rotation around z-axis for each crystal NOTE: Rotations happen around x, then y, then z. | NULL |
| n_crystals | 1 | Number of crystals in your array. | 1 |
| optimize | 1 | Flag to tell if the component should optimize for reflections or not. | 0 |
| verbose | 1 | Verbosity of the monochromator. Used for debugging. | 0 |
| draw_as_rectangles | 1 | Draw the monochromators as boxes. DOES NOT WORK WHEN USING _rot parameters. | 0 |

## Links

- [Source code](/Users/peterwillendrup/Projects/willend-McCode/mcstas-comps/contrib/Monochromator_bent_complex.comp) for `Monochromator_bent_complex.comp`.
- <a href="https://doi.org/10.1016/j.nima.2004.04.197">Jan &Scaron;aroun NIM A Volume 529, Issue 1-3 (2004), pp162-165</a>
- <a href="https://doi.org/10.3390/qubs10010006">Christensen, D.L.; Cabeza, S.; Pirling, T.; Lefmann, K.; &Scaron;aroun, J. Simulating Neutron Diffraction from Deformed Mosaic Crystals in McStas. Quantum Beam Sci. 2026, 10, 6. https://doi.org/10.3390/qubs10010006</a>

---

*Generated on mcstas 3.99.99.*