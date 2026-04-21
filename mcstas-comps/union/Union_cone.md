# The `Union_cone` Component

*McStas: Cone geometry component for Union components*

## Identification

- **Site:** 
- **Author:** Martin Olsen
- **Origin:** University of Copenhagen
- **Date:** 17.09.18

## Description

```text
Part of the Union components, a set of components that work together and thus
sperates geometry and physics within McStas.
The use of this component requires other components to be used.

1) One specifies a number of processes using process components
2) These are gathered into material definitions using Union_make_material
3) Geometries are placed using Union_box/cylinder/sphere, assigned a material
4) A Union_master component placed after all of the above

Only in step 4 will any simulation happen, and per default all geometries
defined before this master, but after the previous will be simulated here.

There is a dedicated manual available for the Union_components

The position of this component is the center of the cone, and it thus
extends yheight/2 up and down along y axis.

It is allowed to overlap components, but it is not allowed to have two
parallel planes that coincides. This will crash the code on run time.
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| material_string | string | Material name of this volume, defined using Union_make_material | 0 |
| **priority** | 1 | Priotiry of the volume (can not be the same as another volume) A high priority is on top of low. |  |
| radius | m | Radius volume in (x,z) plane | 0 |
| radius_top | m | Top radius volume in (x,z) plane | 0 |
| radius_bottom | m | Bottom radius volume in (x,z) plane | 0 |
| **yheight** | m | Cone height in (y) direction |  |
| visualize | 1 | Set to 0 if you wish to hide this geometry in mcdisplay | 1 |
| target_index | 1 | Focuses on component a component this many steps further in the component sequence | 0 |
| target_x | m | X position of target to focus at | 0 |
| target_y | m | Y position of target to focus at | 0 |
| target_z | m | Z position of target to focus at | 0 |
| focus_aw | deg | Horiz. angular dimension of a rectangular area | 0 |
| focus_ah | deg | Vert. angular dimension of a rectangular area | 0 |
| focus_xw | m | Horiz. dimension of a rectangular area | 0 |
| focus_xh | m | Vert. dimension of a rectangular area | 0 |
| focus_r | m | Focusing on circle with this radius | 0 |
| p_interact | 1 | Probability to interact with this geometry [0-1] | 0 |
| mask_string | string | Comma seperated list of geometry names which this geometry should mask | 0 |
| mask_setting | string | "All" or "Any", should the masked volume be simulated when the ray is in just one mask, or all. | 0 |
| number_of_activations | 1 | Number of subsequent Union_master components that will simulate this geometry | 1 |
| curved_surface | string | Comma seperated string of Union surface definitions defined prior to this component, applied to curved wall of cone | 0 |
| top_surface | string | Comma seperated string of Union surface definitions defined prior to this component, applied to +y top face of cone | 0 |
| bottom_surface | string | Comma seperated string of Union surface definitions defined prior to this component, applied to -y bottom face of cone | 0 |
| all_face_surface | string | Comma seperated string of Union surface definitions defined prior to this component, applied to all faces above | 0 |
| cut_surface | string | Comma seperated string of Union surface definitions defined prior to this component, applied to all internal cuts | 0 |
| init | string | Name of Union_init component (typically "init", default) | "init" |

## Links

- [Source code](Union_cone.comp) for `Union_cone.comp`.

---

*Generated on mcstas 3.99.99.*