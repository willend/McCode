# The `Powder_process` Component

*McStas: Port of the PowderN process to the Union components*

## Identification

- **Site:** 
- **Author:** Mads Bertelsen
- **Origin:** University of Copenhagen
- **Date:** 20.08.15

## Description

```text
This Union_process is based on the PowderN.comp component originally written
by P. Willendrup, L. Chapon, K. Lefmann, A.B.Abrahamsen, N.B.Christensen,
E.M.Lauridsen.

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
| reflections | string | Input file for reflections. No scattering if NULL or "" [string] | "NULL" |
| packing_factor | 1 | How dense is the material compared to optimal 0-1 | 1 |
| Vc | AA^3 | Volume of unit cell=nb atoms per cell/density of atoms. | 0 |
| delta_d_d | 0/1 | Global relative delta_d_d/d broadening when the 'w' column is not available. Use 0 if ideal. | 0 |
| DW | 1 | Global Debye-Waller factor when the 'DW' column is not available. Use 1 if included in F2 | 0 |
| nb_atoms | 1 | Number of sub-unit per unit cell, that is ratio of sigma for chemical formula to sigma per unit cell | 1 |
| d_phi | deg | Angle corresponding to the vertical angular range to focus to, e.g. detector height. 0 for no focusing. | 0 |
| density | g/cm^3 | Density of material. rho=density/weight/1e24*N_A. | 0 |
| weight | g/mol | Atomic/molecular weight of material. | 0 |
| barns | 1 | Flag to indicate if \|F\|^2 from 'reflections' is in barns or fm^2 (barns=1 for laz, barns=0 for lau type files). | 1 |
| Strain | ppm | Global relative delta_d_d/d shift when the 'Strain' column is not available. Use 0 if ideal. | 0 |
| interact_fraction | 1 | How large a part of the scattering events should use this process 0-1 (sum of all processes in material = 1) | -1 |
| format | no quotes | Name of the format, or list of column indexes (see Description). | {0, 0, 0, 0, 0, 0, 0, 0, 0} |

## Links

- [Source code](/Users/peterwillendrup/Projects/willend-McCode/mcstas-comps/union/Powder_process.comp) for `Powder_process.comp`.

---

*Generated on mcstas 3.99.99.*