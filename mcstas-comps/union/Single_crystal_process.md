# The `Single_crystal_process` Component

*McStas: Port of the Single_crystal component to the Union components*

## Identification

- **Site:** 
- **Author:** Mads Bertelsen
- **Origin:** University of Copenhagen
- **Date:** 20.08.15

## Description

```text
This Union_process is based on the Single_crystal.comp component originally
written by Kristian Nielsen

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
| reflections | string | File name containing structure factors of reflections. Use empty ("") or NULL for incoherent scattering only | 0 |
| delta_d_d | 1 | Lattice spacing variance, gaussian RMS | 1e-4 |
| mosaic | arc minutes | Crystal mosaic (isotropic), gaussian RMS. Puts the crystal in the isotropic mosaic model state, thus disregarding other mosaicity parameters. | -1 |
| mosaic_a | arc minutes | Horizontal (rotation around lattice vector a) mosaic (anisotropic), gaussian RMS. Put the crystal in the anisotropic crystal vector state. I.e. model mosaicity through rotation around the crystal lattice vectors. Has precedence over in-plane mosaic model. | -1 |
| mosaic_b | arc minutes | Vertical (rotation around lattice vector b) mosaic (anisotropic), gaussian RMS. | -1 |
| mosaic_c | arc minutes | Out-of-plane (Rotation around lattice vector c) mosaic (anisotropic), gaussian RMS | -1 |
| mosaic_AB | arc_minutes, arc_minutes,1, 1, 1, 1, 1, 1 | In Plane mosaic rotation and plane vectors (anisotropic), mosaic_A, mosaic_B, A_h,A_k,A_l, B_h,B_k,B_l. Puts the crystal in the in-plane mosaic state. Vectors A and B define plane in which  the crystal roation is defined, and mosaic_A, mosaic_B, denotes the resp. mosaicities (gaussian RMS) with respect to the two reflections chosen by A and B (Miller indices). | {0,0, 0,0,0, 0,0,0} |
| recip_cell | 1 | Choice of direct/reciprocal (0/1) unit cell definition | 0 |
| barns | 1 | Flag to indicate if \|F\|^2 from 'reflections' is in barns or fm^2. barns=1 for laz and isotropic constant elastic scattering (reflections=NULL), barns=0 for lau type files | 0 |
| ax | AA or AA^-1 | Coordinates of first (direct/recip) unit cell vector | 0 |
| ay | AA or AA^-1 | a on y axis | 0 |
| az | AA or AA^-1 | a on z axis | 0 |
| bx | AA or AA^-1 | Coordinates of second (direct/recip) unit cell vector | 0 |
| by | AA or AA^-1 | b on y axis | 0 |
| bz | AA or AA^-1 | b on z axis | 0 |
| cx | AA or AA^-1 | Coordinates of third (direct/recip) unit cell vector | 0 |
| cy | AA or AA^-1 | c on y axis | 0 |
| cz | AA or AA^-1 | c on z axis | 0 |
| aa | deg | Unit cell angles alpha, beta and gamma. Then uses norms of vectors a,b and c as lattice parameters | 0 |
| bb | deg | Beta angle | 0 |
| cc | deg | Gamma angle | 0 |
| order | 1 | Limit multiple scattering up to given order (0: all, 1: first, 2: second, ...) (Not supported in Union) | 0 |
| RX | m | Radius of lattice curvature along X. flat when 0. | 0 |
| RY | m | Radius of lattice curvature along Y. flat when 0. | 0 |
| RZ | m | Radius of lattice curvature along Z. flat when 0. | 0 |
| powder | 1 | Flag to indicate powder mode, for simulation of Debye-Scherrer cones via random crystallite orientation. A powder texture can be approximated with 0 | 0 |
| PG | 1 | Flag to indicate "Pyrolytic Graphite" mode, only meaningful with choice of Graphite.lau, models PG crystal. A powder texture can be approximated with 0 | 0 |
| interact_fraction | 1 | How large a part of the scattering events should use this process 0-1 (sum of all processes in material = 1) | -1 |
| packing_factor | 1 | How dense is the material compared to optimal 0-1 | 1 |

## Links

- [Source code](Single_crystal_process.comp) for `Single_crystal_process.comp`.

---

*Generated on mcstas 3.99.99.*