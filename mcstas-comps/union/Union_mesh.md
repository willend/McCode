# The `Union_mesh` Component

*McStas: Component for including 3D mesh in Union geometry*

## Identification

- **Site:** 
- **Author:** Martin Olsen, and expanded upon by Daniel Lomholt Christensen
- **Origin:** University of Copenhagen / ACTNXT project
- **Date:** 17.09.18

## Description

```text
Part of the Union components, a set of components that work together and thus
separates geometry and physics within McStas.
The use of this component requires other components to be used.

1) One specifies a number of processes using process components
2) These are gathered into material definitions using Union_make_material
3) Geometries are placed using Union_box/cylinder/sphere/mesh, assigned a material
4) A Union_master component placed after all the above

Only in step 4 will any simulation happen, and per default all geometries
defined before this master, but after the previous will be simulated here.

There is a dedicated manual available for the Union_components

The mesh component loads a 3D off or stl files as the geometry.
The mesh geometry that is loaded must be a watertight mesh.
In order to check this, the component implements a simple Euler Pointcare value,
To check if the given geometry is watertight. This check is sometimes too rigid,
so a user can set the skip_convex_check parameter in order to not have this
check performed.


If you load an off file, we currently only support rank 3 polygons, i.e
triangular meshes.

It is allowed to overlap components, but it is not allowed to have two
parallel planes that coincides. This will crash the code on run time.
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| filename | str | Name of file that contains the 3D geometry. Can be either .OFF, .off, .STL, or .stl | 0 |
| material_string | string | material name of this volume, defined using Union_make_material | 0 |
| **priority** | 1 | priotiry of the volume (can not be the same as another volume) A high priority is on top of low. |  |
| visualize | 1 | set to 0 if you wish to hide this geometry in mcdisplay | 1 |
| all_surfaces |  |  | 0 |
| cut_surface |  |  | 0 |
| target_index | 1 | Focuses on component a component this many steps further in the component sequence | 0 |
| target_x | m |  | 0 |
| target_y | m | Position of target to focus at | 0 |
| target_z | m |  | 0 |
| focus_aw | deg | horiz. angular dimension of a rectangular area | 0 |
| focus_ah | deg | vert. angular dimension of a rectangular area | 0 |
| focus_xw | m | horiz. dimension of a rectangular area | 0 |
| focus_xh | m | vert. dimension of a rectangular area | 0 |
| focus_r | m | focusing on circle with this radius | 0 |
| p_interact | 1 | probability to interact with this geometry [0-1] | 0 |
| mask_string | string | Comma seperated list of geometry names which this geometry should mask | 0 |
| mask_setting | string | "All" or "Any", should the masked volume be simulated when the ray is in just one mask, or all. | 0 |
| number_of_activations | 1 | Number of subsequent Union_master components that will simulate this geometry | 1 |
| skip_convex_check | 1 | when set to 1, skips the check for whether input .off file is convex. | 0 |
| coordinate_scale | 1e-3 | Multiplier that the vertex positions are multiplied by. Set to 1 for input coordinates in meters. Set to 1e-3 for input coordinates in mm. | 1e-3 |
| init | string | name of Union_init component (typically "init", default) | "init" |

## Links

- [Source code](Union_mesh.comp) for `Union_mesh.comp`.

---

*Generated on mcstas 3.99.99.*