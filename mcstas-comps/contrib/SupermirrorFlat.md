# The `SupermirrorFlat` Component

*McStas: Model of flat supermirror with parallel mirror surfaces*

## Identification

- **Site:** 
- **Author:** Wai Tung Lee
- **Origin:** ESS
- **Date:** September 2024

## Description

```text
Calculate the neutron reflection and transmission of a flat supermirror with parallel mirror surfaces.
The following can be specified:
1. reflection from either mirror coating or substrate surface, mirror coating can be single-side, double-side,
2. absorber coating:  beneath mirror coating, single-side coated, double-side coated, or uncoated,
3. refraction and total reflection at substrate surface,
4. attenuation and internal reflection inside substrate.

note: supermirror name is case-sensitive
text entries of parameters below are not sensitive to case
default regional spelling is UK, but some paramters accept other reginal spelling


INITIALISATION parameters:


STEP 1: Specify supermirror shape, supermirror coating, absorber and substrate material
In this step, supermirror is standing vertically, mirror coating = yz plane with long side along +z.

SUPERMIRROR SHAPE -------------------------------------------------
1. +x: "top" mirror surface normal, horizontal transverse to beam;
+y: vertical up, parallel to  mirror surface;
+z: longitudinal to beam, parallel to mirror surface;
2. top and bottom mirrors' surface normals are +x and -x, respectively;
3. entrance-side edge normal is -z, exit-side edge normal is +z (beam direction);
3. normals of and points on the remaining edge surfaces at +y and -y are user-specified,

Mirror shape is specified by length, thickness, and the normals of and points on the edge surfaces at +y and -y sides.

The two side-edges at +y and -y are taken to be symmetric about the xz-plane, only one needs to be specified.
Use InitialiseStdSupermirrorFlat_detail if not symmetric.

SUPERMIRROR COATING -------------------------------------------------
Mirror reflectivity parameters are specified by name to look up 6 parameters {R0, Qc, alpha, m, W, beta}.

If name = SubstrateSurface, reflectivity is calculated by
R = R0 (when q<=Qc), R0*( (q - (q^2 - Qc^2)^1/2) / (q + (q^2 - Qc^2)^1/2) )^2 (when q>Qc), with Qc=sqrt(16 Pi SLD).
with Qc = Qc_sub defined in SubstrateSurfaceParameters and SLD defined in SubstrateParameters,
otherwise reflectivity is calculated by
R = R0 (when q<=Qc), R = R0*0.5*(1-tanh((q - m*Qc)/W))*(1-alpha*(q-Qc)+beta*(q-Qc)*(q-Qc)) (when q>Qc).

specified mirror material name matching one of those defined in "Supermirror_reflective_coating_materials.txt".
If the mirror is non-polarising, specify the same name and parameters for spin plus and spin minus.

ABSORBER LAYER -------------------------------------------------
Absorber parameters are either specified by name or by parameters L_abs, L_inc and the coating thickness.


SUBSTRATE -------------------------------------------------
Substrate parameters are specified by name to look up 3 parameters {L_abs, L_inc, SLD}.

specify substrate material name matching one of those defined in "Supermirror_substrate_materials.txt".



STEP 2: Orient and position the as-defined supermirror in the McStas module XYZ coordinates.

1. Specify initially a location on the front side of the mirror (see parameter "initial_placement_at_origin" below).
The supermirror is shifted so that the selected point coincides with the origin of the McStas module XYZ coordinates
2. Then the orientation and position of the supermirror are specified by the movements in sequence as
1st, tilting about an axis in +y direction at a selected location (see parameters "tilt_y_axis_location" and "tilt_about_y_first_in_degree" below),
2nd, translation,
3rd, rotation about the z-axis of the McStas module XYZ coordinates.



OUTPUT:
Supermirror struct with all parameter values entered and initialised
User declares "Supermirror supermirror;" or its equivalence,
then passes pointer "&supermirror" to function.



End INITIALISATION parameters




RAY-TRACING parameters

FUNCTION IntersectStdSupermirrorFlat
INPUT:
neutron parameters: w_sm=p, t_sm=t, p_sm=coords_set(x,y,z), v_sm=coords_set(vx,vy,vz), s_sm=coords_set(sx,sy,sz)
last_exit_time			[s]       time of last exit from a supermirror, use F_INDETERMINED if not determined. (F_INDETERMINED defined in this file)
last_exit_point			[m,m,m]   position of last exit from a supermirror, use coords_set(F_INDETERMINED,F_INDETERMINED,F_INDETERMINED) if not determined.
last_exit_plane			[1]       plane of last exit from a supermirror, use I_INDETERMINEDif not determined.
sm:						[struct]  Supermirror structure
OUTPUT:
num_intersect:          [1]		number of intersects through supermirror
First intersect time, point, plane if there is intersect.
User declare one or more parameters, e.g. "int num_intersect; double first_intersect_time; Coords first_intersect_point; int first_intersect_plane;",
then passes pointers "&num_intersect, &first_intersect_time, &first_intersect_point, &first_intersect_plane" to function.
Pass 0 as pointer if not needed.
first_intersect_dtime:  [s]		time difference from neutron to first intersect
first_intersect_dpoint: [m,m,m]	position difference from neutron to point of first intersect
first_intersect_time:   [s]		time of first intersect
first_intersect_point:  [m,m,m]	point of first intersect
first_intersect_plane:  [1]		plane of first intersect
RETRUN:
sm_Intersected, sm_Missed. sm_Error


FUNCTION StdSupermirrorFlat
INPUT:
sm						[struct]  Supermirror structure
INPUT & OUTPUT:
neutron parameters: w_sm=p, t_sm=t, p_sm=coords_set(x,y,z), v_sm=coords_set(vx,vy,vz), s_sm=coords_set(sx,sy,sz)
last_exit_time			[s]       time of last exit from a supermirror, use F_INDETERMINED if not determined. (F_INDETERMINED defined in this file)
last_exit_point			[m,m,m]   position of last exit from a supermirror, use coords_set(F_INDETERMINED,F_INDETERMINED,F_INDETERMINED) if not determined.
last_exit_plane			[1]       plane of last exit from a supermirror, use I_INDETERMINEDif not determined.
RETRUN:
sm_Exited, sm_Absorbed. sm_Error
sm:	[struct Supermirror]  Supermirror structure


End RAY-TRACING parameters
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| side_edge_normal | 1,1,1 | Normal vector of one of the two side-edge surface, use Coords structure, doesn't need to be normalised | {0,+1,0} |
| side_edge_point | m,m,m | A point on one of the two side-edge surface with its normal specified above, use Coords structure | {0,+0.1,0} |
| length | m | Supermirror length | 0.5 |
| thickness_in_mm | mm | Substrate thickness in mm | 0.3 |
| mirror_coated_side | string | Sequential keywords combinations of position and surface property. position: "Both", "Top", "Bottom"; surface property: "Coated", "SubstrateSurface", "NoReflection"; Note: "NotCoated"="Empty"="SubstrateSurface", e.g. "BothCoated", "BottomCoatedTopSubstrate" (case-insensitive.) | "BothCoated" |
| mirror_spin_plus_material_name | string | mirror spin+ material name in "Supermirror_reflective_coating_materials.txt". (case-insensitive) | "FeSiPlus" |
| mirror_spin_plus_m | 1 | mirror spin+ m-value, -1=use default value | 3.5 |
| mirror_spin_minus_material_name | string | mirror spin- material name in "Supermirror_reflective_coating_materials.txt". (case-insensitive) | "FeSiMinus" |
| mirror_spin_minus_m | 1 | mirror spin- m-value, -1=use default value (useful for spin-) | -1 |
| substrate_material_name | string | substrate material name in "Supermirror_substrate_materials.txt". (Material name is case-insensitive) | "Glass" |
| absorber_coated_side | string | "BothNotCoated", "BothCoated", "TopCoated", "BottomCoated". | "BothNotCoated" |
| absorber_material_name | string | absorber material name in "Supermirror_absorber_coating_materials.txt" or "Empty", 0="Empty", | "Gd" |
| absorber_thickness_in_micron | micrometer | absorber coating thickness in micrometer | 100 |
| initial_placement_at_origin |  |  | "FrontSubstrateCentre" |
| tilt_y_axis_location |  |  | "FrontSubstrateCentre" |
| tilt_about_y_first_in_degree |  |  | 1.5 |
| translation_second_x |  |  | 0 |
| translation_second_y |  |  | 0 |
| translation_second_z |  |  | 0 |
| rot_about_z_third_in_degree |  |  | 0 |
| tracking |  |  | "DetailTracking" |

## Links

- [Source code](/Users/peterwillendrup/Projects/willend-McCode/mcstas-comps/contrib/SupermirrorFlat.comp) for `SupermirrorFlat.comp`.

---

*Generated on mcstas 3.99.99.*