# The `Single_crystal` Component

*McXtrace: Mosaic single crystal with multiple scattering vectors, optimised for speed
with large crystals and many reflections.*

## Identification

- **Site:** 
- **Author:** Kristian Nielsen
- **Origin:** Risoe
- **Date:** December 1999

## Description

```text
Single crystal with mosaic. Delta-D/D option for finite-size effects.
Rectangular geometry. Multiple scattering and secondary extinction included.
The mosaic may EITHER be specified isotropic by setting the mosaic input
parameter, OR anisotropic by setting the mosaic_a, mosaic_b, and mosaic_c
parameters.
If you get strange results, check the mosaicity and delta(d)/d parameters, as this
component is not suited for ideal/perfect mosaic crystals.
The crystal lattice can be bent locally, keeping the external geometry unchanged.
Curvature is spherical along vertical and horizontal axes.

<b>Speed/stat optimisation using SPLIT</b>
In order to dramatically improve the simulation efficiency, we recommend to
use a SPLIT keyword on this component (or prior to it), as well as to disable
the multiple scattering handling by setting order=1. This is especially powerful
for large reflection lists such as with macromolecular proteins. When an incoming
particle is identical to the preceeding, reciprocal space initialisation is
skipped, and a Monte Carlo choice is done on available reflections from the last
repciprocal space calculation! To assist the user in choosing a "relevant" value
of the SPLIT, a rolling average of the number of available reflections is
calculated and presented in the component output.

<b>Mosacitiy modes</b>
The component features three independent ways of parametrising mosaicity:
a) The original algorithm where mosaicity is implemented by extending each
reflection by a Gaussian "cigar" in reciprocal space, characterised by
the parameters mosaic and delta_d_d.
(Also known as "isotropic mosaicity").
b) A similar mode where mosaicities can be non-isotropic and given as the
parameters mosaic_a, mosaic_b and mosaic_c, around the unit cell axes.
(Also known as "anisotropic mosaicity").
c) Given two "macroscopically"/experimentally measured width/mosaicities
of two independent reflections, parametrised by the list
mosaic_AB = {mos_a, mos_b, a_h, a_k, a_l, b_h, b_k, b_l}, a set of
microscopic mosaicities as in b) are estimated (internally) and applied.
(Also known as "phenomenological mosaicity").

<b>Powder-mode</b>
When the powder mode is used (powder=0-1), a randomised transformation
of the particle direction is made before and after scattering, thereby letting
the single crystal behave as a crystallite of either a powder (crystallite
orientation fully randomised).

<b>Curved crystal mode</b>
The component features a method to curve the lattice planes slightly with respect
to the outer geometry of the crystal. The method is implemented as a transformation
on the particle direction vector, and should be used only in cases where:
a) The reflection lattice vector is ~ orthogonal to the crystal surface.
b) The modelled curvarture is "small" with respect to the crystal surface.

<b>Sample shape</b>
Sample shape may be a cylinder, a sphere, a box or any other shape:
box/plate:       xwidth x yheight x zdepth
cylinder:        radius x yheight
sphere:          radius (yheight=0)
any shape:       geometry=OFF/PLY file

The complex geometry option handles any closed non-convex polyhedra.
It computes the intersection points of the photon ray with the object
transparently, so that it can be used like a regular sample object.
It supports the PLY, OFF and NOFF file format but not COFF (colored faces).
Such files may be generated from XYZ data using:
qhull < coordinates.xyz Qx Qv Tv o > geomview.off
or
powercrust coordinates.xyz
and viewed with geomview or java -jar jroff.jar (see below).
The default size of the object depends on the OFF/PLY file data, but its
bounding box may be resized using xwidth,yheight and zdepth.

<b>Crystal definition file format</b>
Crystal structure is specified with an ascii data file. Each line contains
4 or more numbers, separated by white spaces:

h k l ... F2

The first three numbers are the (h,k,l) indices of the reciprocal lattice
point, and the 7-th number is the value of the structure factor |F|**2, in
barns. The rest of the numbers are not used; the file is in the format
output by the Crystallographica program.
The reflection list should be ordered by decreasing d-spacing values.
Lines begining by '#' are read as comments (ignored). Most sample parameters
may be defined from the data file header, following the same mechanism as
PowderN.

Current data file header keywords include, for data format specification:
#column_h <index of the Bragg Qh column>
#column_k <index of the Bragg Qk column>
#column_l <index of the Bragg Ql column>
#column_F2 <index of the squared str. factor '|F|^2' column [b]>
#column_F  <index of the structure factor norm '|F|' column>
and for material specification:
#sigma_inc <value of incoherent cross section [barns]>
#Delta_d/d <value of Delta_d/d width for all lines>
#lattice_a <value of the a lattice parameter [Angs]>
#lattice_b <value of the b lattice parameter [Angs]>
#lattice_c <value of the c lattice parameter [Angs]>
#lattice_aa <value of the alpha lattice angle [deg]>
#lattice_bb <value of the beta  lattice angle [deg]>
#lattice_cc <value of the gamma lattice angle [deg]>

Last, CIF, FullProf and ShelX files can be read, and converted to F2(hkl) lists
when 'cif2hkl' is installed. The CIF2HKL env variable can be used to point to a
proper executable, else the McCode or the system installed versions are used.

<b>Satellite Bragg peaks - surface crystal truncation rods (CTR)</b>
It is known that scattering from a finite crystal introduces a broadening of
Bragg peaks, seen in surface diffraction at grazing angle [Robinson and Tweet,
Rep. Prog. Phys. 55 (1992) 599)]. The CTR is specified as two vectors, which
hold the squared Fourier transform of the crystal geometry, for instance:
bulk:       Dirac peak      (FT of infinity)
half-bulk:  Dirac+1/k^2     (FT of half plane, k in rlu)
layer:      sinc(PI*k*d)^2  (FT of a top-hat, thickness 'd')
These vectors are given as 'surf_k' [in 1/Angs] and 'surf_FT2', both of length
'surf_size'. The CTR is to be applied along vector 'surf_dir' which indicates
the surface normal {nx,ny,nz} in real space. When surf_size=-1, the component
sets the proper truncation function (only for thin box and disk shapes).
This feature is an approximation of the real surface scattering, and does not
handle complex geometries (clusters, wetting, multi-layers, ...). It may be
used as well to describe over-structure satellite peaks.

Example: Single_crystal(xwidth=0.01, yheight=0.01, zdepth=0.01, mosaic = 5,
reflections="Si.lau")

A diamond crystal plate, cut for (002) reflections
Single_crystal(xwidth = 0.002, yheight = 0.1, zdepth = 0.1,
mosaic = 5, delta_d_d=3e-4, reflections = "C-diamond.lau",
ax=0,      ay=2.14,   az=-1.24,
bx = 0,    by = 0,    bz =  2.47,
cx = 6.71, cy = 0,    cz =  0)

A adrenaline protein
Single_crystal(xwidth=0.005, yheight=0.005, zdepth=0.005,
mosaic = 5, reflections="adrenaline.lau")

Also, always use a non-zero value of delta_d_d.

This sample component can advantageously benefit from the SPLIT feature, e.g.
SPLIT COMPONENT sx = Single_crystal(...)
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| reflections | string | File name containing structure factors of reflections (LAZ LAU CIF, FullProf, ShelX). Use empty ("") or NULL for incoherent scattering only | 0 |
| geometry | str | Name of an Object File Format (OFF) or PLY file for complex geometry. The OFF/PLY file may be generated from XYZ coordinates using qhull/powercrust | 0 |
| mosaic_AB | arc_minutes, arc_minutes,1, 1, 1, 1, 1, 1 | In-plane mosaic rotation and plane vectors (anisotropic), mosaic_A, mosaic_B, A_h,A_k,A_l, B_h,B_k,B_l. Puts the crystal in the in-plane mosaic state. Vectors A and B define plane in which the crystal roation is defined, and mosaic_A, mosaic_B, denotes the resp. mosaicities (gaussian RMS) with respect to the two reflections chosen by A and B (Miller indices). | {0,0, 0,0,0, 0,0,0} |
| xwidth | m | Width of crystal | 0 |
| yheight | m | Height of crystal | 0 |
| zdepth | m | Depth of crystal (no extinction simulated) | 0 |
| radius | m | Outer radius of sample in (x,z) plane | 0 |
| delta_d_d | 1 | Lattice spacing variance, gaussian RMS (longitudinal mosaic) e.g. 1e-4 to 1e-3. | 1e-3 |
| mosaic | arc minutes | Crystal mosaic (isotropic), gaussian RMS. Puts the crystal in the isotropic mosaic model state, thus disregarding other mosaicity parameters, e.g. 1-10. | -1 |
| mosaic_a | arc minutes | Horizontal (rotation around lattice vector a) mosaic (anisotropic), gaussian RMS. Put the crystal in the anisotropic crystal vector state. i.e. model mosaicity through rotation around the crystal lattice vectors. Has precedence over in-plane mosaic model. | -1 |
| mosaic_b | arc minutes | Vertical (rotation around lattice vector b) mosaic (anisotropic), gaussian RMS. | -1 |
| mosaic_c | arc minutes | Out-of-plane (Rotation around lattice vector c) mosaic (anisotropic), gaussian RMS | -1 |
| recip_cell | 1 | Choice of direct/reciprocal (0/1) unit cell definition | 0 |
| barns | 1 | Flag to indicate if \|F\|^2 from 'reflections' is in barns or fm^2. barns=1 for laz/cif and isotropic constant elastic scattering (reflections=NULL), barns=0 for lau type files | 0 |
| ax | AA or AA^-1 | Coordinates of first (direct/recip) unit cell vector | 0 |
| ay | AA or AA^-1 | a on y axis | 0 |
| az | AA or AA^-1 | a on z axis | 0 |
| bx | AA or AA^-1 | Coordinates of second (direct/recip) unit cell vector | 0 |
| by | AA or AA^-1 | b on y axis | 0 |
| bz | AA or AA^-1 | b on z axis | 0 |
| cx | AA or AA^-1 | Coordinates of third (direct/recip) unit cell vector | 0 |
| cy | AA or AA^-1 | c on y axis | 0 |
| cz | AA or AA^-1 | c on z axis | 0 |
| p_transmit | 1 | Monte Carlo probability for photons to be transmitted without any scattering. Used to improve statistics from weak reflections | 0.001 |
| sigma_inc | barns | Incoherent scattering cross-section per unit cell (uniform). Fully isotropic and constant. Use -1 to inactivate | 0 |
| aa | deg | Unit cell angles alpha, beta and gamma. Then uses norms of vectors a,b and c as lattice parameters | 0 |
| bb | deg | Beta angle | 0 |
| cc | deg | Gamma angle | 0 |
| order | 1 | Limit multiple scattering up to given order (0: all, 1: first, 2: second, ...) | 1 |
| extra_order | 1 | When using order, allow additional multiple scattering without coherent scattering, sensible with very large unit cells (0: disable, 1: one extra, 2: two extra, ...) | 0 |
| RX | m | Radius of horizontal along X lattice curvature. flat for 0 | 0 |
| RY | m | Radius of vertical   along Y lattice curvature. flat for 0 | 0 |
| powder | 1 | Flag to indicate powder mode, for simulation of Debye-Scherrer cones via random crystallite orientation. A powder texture can be approximated with powder within 0-1 | 0 |
| deltak | AA-1 | Equality-threshold for use in SPLIT settings. If difference between all ki_{x,y,z} are less than deltak from previous particle, the two are considered alike enough to jump directly to the MC choice between 'active' reflections | 1e-6 |
| material_datafile | Be.txt | File where the material parameters for the absorption may be found. Format is similar to what may be found off the NIST website. | "Si.txt" |
| surf_size | 1 | Length of the surf_k and surf_FT vectors. When set as -1, CTR is automatically set for the box/thin disk geometry. | 0 |
| surf_k | 1/Angs | Momentum 'k' distribution around 0 for the CTR, length 'surf_size'. | NULL |
| surf_FT2 | 1 | Intensity \|FT(real space)\|^2 distribution as CTR of a single Bragg peak, length 'surf_size'. | NULL |

## Links

- [Source code](/Users/peterwillendrup/Projects/willend-McCode/mcxtrace-comps/samples/Single_crystal.comp) for `Single_crystal.comp`.
- See <a href="http://icsd.ill.fr">ICSD</a> Inorganic Crystal Structure Database
- <a href="http://www.webelements.com/">Web Elements</a>
- <a href="http://www.ill.eu/sites/fullprof/index.html">Fullprof</a> powder refinement
- <a href="http://www.crystallographica.com/">Crystallographica</a> software
- <a href="http://www.geomview.org">Geomview and Object File Format (OFF)</a>
- Java version of Geomview (display only) <a href="http://www.holmes3d.net/graphics/roffview/">jroff.jar</a>
- <a href="http://qhull.org">qhull</a>
- <a href="http://www.cs.ucdavis.edu/~amenta/powercrust.html">powercrust</a>
- material datafile obtained from http://physics.nist.gov/cgi-bin/ffast/ffast.pl
- cif2hkl https://gitlab.com/soleil-data-treatment/soleil-software-projects/cif2hkl

---

*Generated on mcxtrace 3.99.99.*