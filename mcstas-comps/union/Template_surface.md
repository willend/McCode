# The `Template_surface` Component

*McStas: A template process for building Union surface processes*

## Identification

- **Site:** 
- **Author:** Mads Bertelsen
- **Origin:** University of Copenhagen
- **Date:** 20.08.15

## Description

```text
This is a template for a new contributor to create their own surface process.
The comments in this file are meant to teach the user about creating their own
surface component, rather than explaining this one. For comments on how this
code works, look in the Mirror_surface.comp.
To add a new surface process, three changes are needed in other files:
Add entry in surface enum (match your process)
Add storage struct in the union-lib.c file
Add the surface function in inion-suffix.c switch

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
| reflect | str | Name of reflectivity file. Format q(Angs-1) R(0-1) | 0 |
| R0 | 1 | Low-angle reflectivity | 0.99 |
| Qc | AA-1 | Critical scattering vector | 0.0219 |
| alpha | AA | Slope of reflectivity | 6.07 |
| m | 1 | m-value of material. Zero means completely absorbing. | 2 |
| W | AA-1 | Width of supermirror cut-off | 0.003 |
| init | string | Name of Union_init component (typically "init", default) | "init" |

## Links

- [Source code](/Users/peterwillendrup/Projects/willend-McCode/mcstas-comps/union/Template_surface.comp) for `Template_surface.comp`.

---

*Generated on mcstas 3.99.99.*