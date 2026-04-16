# The `Union_init` Component

*McStas: Initialize component that needs to be place before any Union component*

## Identification

- **Site:** 
- **Author:** Mads Bertelsen
- **Origin:** ESS DMSC
- **Date:** 20.08.15

## Description

```text
Part of the Union components, a set of components that work together and thus
sperates geometry and physics within McStas.
The use of this component requires other components to be used.

1) One specifies a number of processes using process components
2) These are gathered into material definitions using this component
3) Geometries are placed using Union_box/cylinder/sphere, assigned a material
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

## Links

- [Source code](/Users/peterwillendrup/Projects/willend-McCode/mcstas-comps/union/Union_init.comp) for `Union_init.comp`.

---

*Generated on mcstas 3.99.99.*