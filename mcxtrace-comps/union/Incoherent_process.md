# The `Incoherent_process` Component

*McXtrace: A sample component to separate geometry and phsysics*

## Identification

- **Site:** 
- **Author:** Mads Bertelsen and Erik B Knudsen
- **Origin:** ESS DMSC & DTU Physics
- **Date:** 20.08.15

## Description

```text
This Union_process is based on the Incoherent.comp component originally written
by Kim Lefmann and Kristian Nielsen

Part of the Union components, a set of components that work together and thus
separates geometry and physics within McXtrace.
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
| f_QE | 1 | Fraction of quasielastic scattering (rest is elastic) | 0 |
| gamma | 1 | Lorentzian width of quasielastic broadening (HWHM) | 0 |
| packing_factor | 1 | How dense is the material compared to optimal 0-1 | 1 |
| unit_cell_volume |  |  | 13.8 |
| interact_fraction |  |  | -1 |
| init | string | name of Union_init component (typically "init", default) | "init" |

## Links

- [Source code](/Users/peterwillendrup/Projects/willend-McCode/mcxtrace-comps/union/Incoherent_process.comp) for `Incoherent_process.comp`.
- The test/example instrument <a href="../examples/Test_Phonon.instr">Test_Phonon.instr</a>.

---

*Generated on mcxtrace 3.99.99.*