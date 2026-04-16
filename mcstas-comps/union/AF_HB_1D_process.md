# The `AF_HB_1D_process` Component

*McStas: 1D Antiferromagnetic Heisenberg chain*

## Identification

- **Site:** 
- **Author:** Mads Bertelsen
- **Origin:** University of Copenhagen
- **Date:** 20.08.15

## Description

```text
1D Antiferromagnetic Heisenberg chain

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
| atom_distance | AA | Distance between atom's in chain | 1 |
| number_density | 1/AA^3 | Number of scatteres per volume | 0 |
| unit_cell_volume | AA^3 | Unit cell volume (set either unit_cell_volume or number density) | 0 |
| A_constant | unitless | Constant from M&uuml;ller paper 1981, probably somewhere between 1 and 1.5 | 1 |
| J_interaction | meV | Exchange constant | 1 |
| packing_factor | 1 | How dense is the material compared to optimal 0-1 | 1 |
| interact_fraction | 1 | How large a part of the scattering events should use this process 0-1 (sum of all processes in material = 1) | -1 |
| init | string | name of Union_init component (typically "init", default) | "init" |

## Links

- [Source code](/Users/peterwillendrup/Projects/willend-McCode/mcstas-comps/union/AF_HB_1D_process.comp) for `AF_HB_1D_process.comp`.

---

*Generated on mcstas 3.99.99.*