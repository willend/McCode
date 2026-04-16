# The `Union_master_GPU` Component

*McStas: Master component for Union components that performs the overall simulation*

## Identification

- **Site:** 
- **Author:** Mads Bertelsen
- **Origin:** University of Copenhagen
- **Date:** 20.08.15

## Description

```text
Part of the Union components, a set of components that work together and thus
sperates geometry and physics within McStas.
The use of this component requires other components to be used.

1) One specifies a number of processes using process components
2) These are gathered into material definitions using Union_make_material
3) Geometries are placed using Union_box/cylinder/sphere, assigned a material
4) This master component placed after all of the above

Only in step 4 will any simulation happen, and per default all geometries
defined before this master, but after the previous will be simulated here.

There is a dedicated manual available for the Union_components

Algorithm:
Described elsewhere
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| verbal | 0/1 | Toogles terminal output describing the defined simulation | 1 |
| list_verbal | 0/1 | Toogles information of all internal lists in intersection network | 0 |
| finally_verbal | 0/1 | Toogles information about cleanup performed in finally section | 0 |
| allow_inside_start | 0/1 | Set to 1 if rays are expected to start inside a volume in this master | 0 |
| enable_tagging | 0/1 | Enable tagging of ray history (geometry, scattering process) | 0 |
| history_limit | 1 | Limit the number of unique histories that are saved | 300000 |
| enable_conditionals | 0/1 | Use conditionals with this master | 1 |
| inherit_number_of_scattering_events | 0/1 | Inherit the number of scattering events from last master | 0 |
| init |  |  | "init" |

## Links

- [Source code](/Users/peterwillendrup/Projects/willend-McCode/mcstas-comps/union/Union_master_GPU.comp) for `Union_master_GPU.comp`.

---

*Generated on mcstas 3.99.99.*