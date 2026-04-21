# The `Template_process` Component

*McStas: A template process for building Union processes*

## Identification

- **Site:** 
- **Author:** Mads Bertelsen
- **Origin:** University of Copenhagen
- **Date:** 20.08.15

## Description

```text
This is a template for a new contributor to create their own physical process.
The comments in this file are meant to teach the user about creating their own
process file, rather than explaining this one. For comments on how this code works,
look in the Incoherent_process.comp.

Part of the Union components, a set of components that work together and thus
sperates geometry and physics within McStas.
The use of this component requires other components to be used.

1) One specifies a number of processes using process components like this one
2) These are gathered into material definitions using Union_make_material
3) Geometries are placed using Union_box / Union_cylinder, assigned a material
4) A Union_master component placed after all of the above

Only in step 4 will any simulation happen, and per default all geometries
defined before the master, but after the previous will be simulated here.

There is a dedicated manual available for the Union_components


Algorithm:
Described elsewhere
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| sigma | barns | Incoherent scattering cross section | 5.08 |
| packing_factor | 1 | How dense is the material compared to optimal 0-1 | 1 |
| unit_cell_volume | AA^3 | Unit_cell_volume | 13.8 |
| interact_fraction | 1 | How large a part of the scattering events should use this process 0-1 (sum of all processes in material = 1) | -1 |
| init | string | Name of Union_init component (typically "init", default) | "init" |

## Links

- [Source code](Template_process.comp) for `Template_process.comp`.

---

*Generated on mcstas 3.99.99.*