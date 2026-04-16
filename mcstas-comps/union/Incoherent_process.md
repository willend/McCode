# The `Incoherent_process` Component

*McStas: A sample component to separate geometry and phsysics*

## Identification

- **Site:** 
- **Author:** Mads Bertelsen
- **Origin:** University of Copenhagen
- **Date:** 20.08.15

## Description

```text
This Union_process is based on the Incoherent.comp component originally written
by Kim Lefmann and Kristian Nielsen

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
| f_QE | 1 | Fraction of quasielastic scattering (rest is elastic) [1] | 0 |
| gamma | meV | Lorentzian width of quasielastic broadening (HWHM) [1] | 0 |
| packing_factor | 1 | How dense is the material compared to optimal 0-1 | 1 |
| unit_cell_volume | AA^3 | Unit cell volume | 13.8 |
| interact_fraction | 1 | How large a part of the scattering events should use this process 0-1 (sum of all processes in material = 1) | -1 |
| init | string | name of Union_init component (typically "init", default) | "init" |

## Links

- [Source code](/Users/peterwillendrup/Projects/willend-McCode/mcstas-comps/union/Incoherent_process.comp) for `Incoherent_process.comp`.
- The test/example instrument <a href="../examples/Test_Phonon.instr">Test_Phonon.instr</a>.

---

*Generated on mcstas 3.99.99.*