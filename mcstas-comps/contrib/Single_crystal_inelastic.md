# The `Single_crystal_inelastic` Component

*McStas: An extension of Single crystal with material dispersion*

## Identification

- **Site:** 
- **Author:** Duc Le
- **Origin:** STFC
- **Date:** August 2020

## Description

```text
The component handles a 4D S(q,w) material dispersion, and scatters neutrons
out of it. It is based on the Isotropic_Sqw methodology, extended to 4D.

A number of approximations are applied:

- geometry is restricted to box, cylinder and sphere
- ignore absorption, multiple scattering and incoherent scattering
- no temperature handling. The temperature must be taken into account when
generating the S(q,w) data sets, which should contain Bose/detailed balance.
- intensity is used as provided by the S(q,w) data set

We recommend that you first try the Test_Single_crystal_inelastic example to
learn how to use this complex component.

4D S(q,w) data files
--------------------

The input data file derives from other McStas formats. It may contain structural
information as in Lau/Laz files, and a list of S(q,w) [one per row] with 5 columns

[ H K L E S(q,w) ]

An example file example.sqw4 is provided in the McStas/Data directory.

You may generate such files using <a href="http://ifit.mccode.org">iFit </a> such as:

s = sqw_vaks('defaults');             % a 4D model
d = iData(s);                         % use default coarse grid for axes [-0.5:0.5]
saveas(d, 'sx_coh.sqw4', 'mcstas');   % export to 4D Sqw file

%VALIDATION:
This component is undergoing validation.
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| mosaic_AB | arcmin,arcmin,1,1,1,1,1,1 | In Plane mosaic rotation and plane vectors (anisotropic), | {0,0, 0,0,0, 0,0,0} |
| sqw | string | Name of a 4d S(q,w) file - example.sqw4 is included in your installation | 0 |
| geometry | string | Name of an Object File Format (OFF) or PLY file for complex geometry. The OFF/PLY file may be generated from XYZ coordinates using qhull/powercrust. | 0 |
| qwidth |  |  | 0.05 |
| xwidth | m | Width of crystal. | 0 |
| yheight | m | Height of crystal. | 0 |
| zdepth | m | Depth of crystal (no extinction simulated) | 0 |
| radius | m | Outer radius of sample in (x,z) plane. | 0 |
| delta_d_d | 1 | Lattice spacing variance, gaussian RMS. | 1e-4 |
| mosaic | arcmin | Isotropic crystal mosaic, gaussian RMS. Puts the crystal in the isotropic mosaic model state, thus disregarding other mosaicity parameters. | -1 |
| mosaic_a | arcmin | Horizontal (rotation around lattice vector a) mosaic (anisotropic), gaussian RMS. Put the crystal in the anisotropic crystal vector state. I.e. model mosaicity through rotation around the crystal lattice vectors. Has precedence over in-plane mosaic model. | -1 |
| mosaic_b | arcmin | Vertical (rotation around lattice vector b) mosaic (anisotropic), gaussian RMS. | -1 |
| mosaic_c | arcmin | Out-of-plane (Rotation around lattice vector c) mosaic (anisotropic), gaussian RMS. | -1 |
| recip_cell | 1 | Choice of direct/reciprocal (0/1) unit cell definition. | 0 |
| barns | 1 | Flag to indicate if \|F\|^2 from 'reflections' is in barns or fm^2. | 0 |
| ax | AA / AA^-1 | Coordinates of first (direct/recip) unit cell vector. | 0 |
| ay | AA / AA^-1 | a on y axis | 0 |
| az | AA / AA^-1 | a on z axis | 0 |
| bx | AA / AA^-1 | Coordinates of second (direct/recip) unit cell vector. | 0 |
| by | AA / AA^-1 | b on y axis | 0 |
| bz | AA / AA^-1 | b on z axis | 0 |
| cx | AA / AA^-1 | Coordinates of third (direct/recip) unit cell vector. | 0 |
| cy | AA / AA^-1 | c on y axis | 0 |
| cz | AA / AA^-1 | c on z axis | 0 |
| p_transmit | 1 | Monte Carlo probability for neutrons to be transmitted | -1 |
| sigma_abs | barns | Absorption cross-section per unit cell at 2200 m/s. | 0 |
| sigma_inc | barns | Incoherent scattering cross-section per unit cell. | 0 |
| aa | deg | Unit cell angles alpha, beta and gamma. Then uses norms of | 0 |
| bb | deg | Beta angle. | 0 |
| cc | deg | Gamma angle. | 0 |
| order | 1 | Limit multiple scattering up to given order | 0 |
| RX | m | Radius of horizontal along X lattice curvature. flat for 0. | 0 |
| RY | m | Radius of vertical lattice curvature. flat for 0. | 0 |
| RZ | m | Radius of horizontal along Z lattice curvature. flat for 0. | 0 |
| max_stored_ki |  |  | 1000 |

## Links

- [Source code](/Users/peterwillendrup/Projects/willend-McCode/mcstas-comps/contrib/Single_crystal_inelastic.comp) for `Single_crystal_inelastic.comp`.

---

*Generated on mcstas 3.99.99.*