# The `FluoPowder` Component

*McXtrace: Release:    McXtrace 3.5

Sample model handling absorption, fluorescence, Compton, Rayleigh scattering and powder diffraction.*

## Identification

- **Site:** 
- **Author:** Emmanuel Farhi (emmanuel.farhi.synchrotron-soleil.fr)
- **Origin:** Synchrotron SOLEIL
- **Date:** April 2025

## Description

```text
Sample that models multiple photon-matter interactions:
- absorption          (photon excites an electron and creates a hole)
- fluorescence        (excited electrons emit light while falling into lower states)
- Compton scattering  (inelastic, incoherent)
- Rayleigh scattering (elastic,   coherent)
- powder diffraction  (elastic,   coherent)

The 'material' specification is given as a chemical formulae, e.g. "LaB6". It
may also be given as a file name (CIF/LAU/LAZ/FullProf format) in which case
the formulae is guessed (but may be approximative), and the powder
diffraction is computed, following same options as the <b>PowderN</b>
sample component. The fluorescence is handled for atoms from Z=5 to Z=90.

By setting the 'order' to 1, the absorption along the scattered path is handled.
A higher 'order' will handle multiple scattering events, and final absorption.
For instance, a value order>=2 handles e.g. fluorescence iterative cascades
in the material. Leaving 'order=0' handles the single scattering only.

Example: FluoPowder(material="LaB6.cif",
xwidth=0.001,yheight=0.001,zdepth=0.0001, p_interact=0.99,
target_index=1, focus_xw=0.0005, focus_yh=0.0005)

<b>Sample shape:</b>
Sample shape may be a cylinder, a sphere, a box or any other shape
box/plate:       xwidth x yheight x zdepth (thickness=0)
hollow box/plate:xwidth x yheight x zdepth and thickness>0
cylinder:        radius x yheight (thickness=0)
hollow cylinder: radius x yheight and thickness>0
sphere:          radius (yheight=0 thickness=0)
hollow sphere:   radius and thickness>0 (yheight=0)
any shape:       geometry=OFF file

The complex geometry option handles any closed non-convex polyhedra.
It computes the intersection points of the photon ray with the object
transparently, so that it can be used like a regular sample object.
It supports the OFF, PLY and NOFF file format but not COFF (colored faces).
Such files may be generated from XYZ data using:
qhull < coordinates.xyz Qx Qv Tv o > geomview.off
or
powercrust coordinates.xyz
and viewed with geomview or java -jar jroff.jar (see below).
The default size of the object depends of the OFF file data, but its
bounding box may be resized using xwidth,yheight and zdepth.

<b>Concentric components:</b>
This component has the ability to contain other components when used in
hollow cylinder geometry (namely sample environment, e.g. cryostat and
furnace structure). Such component 'shells' should be split into input and
output side surrounding the 'inside' components. First part must then use
'concentric=1' flag to enter the inside part. The component itself must be
repeated to mark the end of the concentric zone. The number of concentric
shells and number of components inside is not limited.

COMPONENT F_in = FluoPowder(material="Al", concentric=1, ...)
AT (0,0,0) RELATIVE sample_position

COMPONENT something_inside ... // e.g. the sample itself or other materials

COMPONENT F_out = COPY(F_in)(concentric=0)
AT (0,0,0) RELATIVE sample_position

<b>Enhancing computation efficiency:</b>
An important option to enhance statistics is to set 'p_interact' to, say,
30 percent (0.3) in order to force a fraction of the beam to scatter. This
will result on a larger number of scattered events, retaining intensity.

In addition, it may be desirable to define a 'target' for the fluorescence
processes via e.g. the 'target_index' and the 'focus_xw / focus_yh' options.
This target should e.g. be the SDD area.
The powder scattering can be focused along an horizontal tore via the
'd_phi' and 'tth_sign' options. To get a vertical tore, rotate
the sample by 90 deg around Z.

This sample component can advantageously benefit from the SPLIT feature, e.g.
SPLIT COMPONENT sample = FluoPowder(...)

The fluorescence is computed via the XRayLib (apt install libxrl-dev) https://github.com/tschoonj/xraylib.
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| geometry | str | Name of an Object File Format (OFF) or PLY file for complex geometry. The OFF/PLY file may be generated from XYZ coordinates using qhull/powercrust. | 0 |
| radius | m | Outer radius of sample in (x,z) plane. cylinder/sphere. | 0 |
| thickness | m | Thickness of hollow sample Negative value extends the hollow volume outside of the box/cylinder. | 0 |
| xwidth | m | Width for a box sample shape. | 0 |
| yheight | m | Height of sample in vertical direction for box/cylinder shapes. | 0 |
| zdepth | m | Depth for a box sample shape. | 0 |
| concentric | 1 | Indicate that this component has a hollow geometry and may contain other components. It should then be duplicated after the inside part (only for box, cylinder, sphere). | 0 |
| material | str | A CIF/LAZ/LAU file e.g. "LaB6.cif" to handle diffraction or chemical formulae, e.g. "Pb2SnO4" (no diffraction). | "LaB6.cif" |
| packing_factor | 1 | How dense is the material compared to bulk 0-1. | 0 |
| density | g/cm^3 | Density of material. V_rho=density/weight/1e24*N_A at/Angs^3. | 0 |
| weight | g/mol | Atomic/molecular weight of material. | 0 |
| p_interact | 1 | Force a given fraction of the beam to scatter, keeping intensity right, to enhance small signals (-1 inactivate). | 0 |
| target_x | m | Position of target to focus at, along X (for fluorescence). | 0 |
| target_y | m | Position of target to focus at, along Y (for fluorescence). | 0 |
| target_z | m | Position of target to focus at, along Z (for fluorescence). | 0 |
| focus_r | m | Radius of disk containing target. Use 0 for full space (for fluorescence). | 0 |
| focus_xw | m | Horiz. dimension of a rectangular area (for fluorescence). | 0 |
| focus_yh | m | Vert.  dimension of a rectangular area (for fluorescence). | 0 |
| focus_aw | deg | Horiz. angular dimension of a rectangular area (for fluorescence). | 0 |
| focus_ah | deg | Vert.  angular dimension of a rectangular area (for fluorescence). | 0 |
| target_index | 1 | Relative index of component to focus at, e.g. next is +1 (for fluorescence). | 0 |
| flag_compton | 1 | When 0, the Compton  scattering is ignored. | 1 |
| flag_rayleigh | 1 | When 0, the Rayleigh scattering is ignored. | 1 |
| flag_lorentzian | 1 | When 1, the fluorescence line shapes are assumed to be Lorentzian, else Gaussian. | 0 |
| flag_powder | 1 | When 0, the powder diffraction is ignored. | 1 |
| flag_kissel | 1 | When 1 (slower), handle M-lines XRF from Kissel for Z>=52 Te (else only K and L-lines). | 0 |
| powder_refl | str | A CIF/LAZ/LAU reflection file as for PowderN. When not given, 'material' is used. Specify it when 'material' is a chemical formula. | "" |
| powder_format | {} | List of structure file column indexes. See the PowderN component. | {0,0,0,0,0,0,0,0} |
| Vc | AA^3 | Volume of unit cell=nb atoms per cell/density of atoms. | 0 |
| delta_d_d | AA | Global relative difraction Delta_d/d spreading when the 'w' column is not available, e.g. 1e-4 to 1e-3. Use 0 if ideal. | 0 |
| DW | 1 | Global difraction Debye-Waller factor when the 'DW' column is not available. Use 1 if included in F2. | 0 |
| d_phi | deg | Angle corresponding to the difraction vertical angular range to focus to, e.g. detector height. 0 for no focusing. You may as well define focus_ah or focus_yh and target. | 0 |
| nb_atoms | 1 | Number of sub-unit per unit cell, that is ratio of sigma for chemical formula to sigma per unit cell. | 1 |
| barns | 1 | Flag to indicate if \|F\|^2 from 'material' is in barns or fm^2, (barns=1 for laz/cif, barns=0 for lau type files). | 1 |
| tth_sign | 1 | Sign of the diffraction angle. If 0, the sign is chosen randomly (left and right). | 0 |

## Links

- [Source code](/Users/peterwillendrup/Projects/willend-McCode/mcxtrace-comps/samples/FluoPowder.comp) for `FluoPowder.comp`.
- The XRayLib https://github.com/tschoonj/xraylib http://dx.doi.org/10.1016/j.sab.2011.09.011
- Fluorescence https://en.wikipedia.org/wiki/Fluorescence
- Rayleigh https://en.wikipedia.org/wiki/Rayleigh_scattering
- Compton https://en.wikipedia.org/wiki/Compton_scattering
- X-ray absorption edges http://skuld.bmsc.washington.edu/scatter/AS_periodic.html
- X-ray fluorescence spectra http://www.xrfresearch.com/xrf-spectra/
- X-ray edges and fluo lines https://physics.nist.gov/PhysRefData/XrayTrans/Html/search.html

---

*Generated on mcxtrace 3.99.99.*