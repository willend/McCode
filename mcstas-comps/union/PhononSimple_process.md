# The `PhononSimple_process` Component

*McStas: Port of PhononSimple to Union components*

## Identification

- **Site:** 
- **Author:** Anders Komar Ravn, based on template by Mads Bertelsen and Phonon_Simple
- **Origin:** University of Copenhagen
- **Date:** 20.08.15

## Description

```text
Port of the PhononSimple component from the McStas library to the Union
components.

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
| packing_factor | 1 | How dense is the material compared to optimal 0-1 | 1 |
| unit_cell_volume | AA^3 | Unit cell volume | 13.8 |
| interact_fraction | 1 | How large a part of the scattering events should use this process 0-1 (sum of all processes in material = 1) | -1 |
| a | AA | fcc lattice constant | 4.95 |
| c | meV*AA | Velocity of sound | 10 |
| M | units | Nucleus atomic mass in units | 207.2 |
| b | fm | Scattring length | 9.4 |
| T | K | Temperature | 290 |
| DW | 1 | Debye-Waller factor | 1 |
| longitudinal | 0/1 | Simulate longitudinal branches | 1 |
| transverse | 0/1 | Simulate transverse branches | 1 |
| init | string | Name of Union_init component (typically "init", default) | "init" |

## Links

- [Source code](PhononSimple_process.comp) for `PhononSimple_process.comp`.

---

*Generated on mcstas 3.99.99.*