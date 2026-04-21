# The `Mirror_surface` Component

*McStas: A Mirror surface process*

## Identification

- **Site:** 
- **Author:** Mads Bertelsen
- **Origin:** University of Copenhagen
- **Date:** 20.08.15

## Description

```text
This is a Union surface process that describes a supermirror or other surface
that only have specular reflection. The reflectivity can be given as a file
or using the standard reflectivity inputs. To use this in a simulation an
instance of this component should be defined in the instrument file, then
attatched to one or more geometries in their surface stacks pertaining to
each face of the geometry.

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

- [Source code](Mirror_surface.comp) for `Mirror_surface.comp`.

---

*Generated on mcstas 3.99.99.*