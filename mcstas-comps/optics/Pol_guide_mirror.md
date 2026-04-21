# The `Pol_guide_mirror` Component

*McStas: Polarising guide with a supermirror along its diagonal.*

## Identification

- **Site:** 
- **Author:** Erik B Knudsen
- **Origin:** DTU Physics
- **Date:** July 2018

## Description

```text
Based on Pol_guide_vmirror by P. Christiansen.
Models a rectangular guide with entrance centered on the Z axis and
with one supermirror sitting on the diagonal inside.
The entrance lies in the X-Y plane.  Draws a true depiction
of the guide with mirror and trajectories.
The polarisation is handled similar to in Monochromator_pol.
The reflec functions are handled similar to Pol_mirror.
The up direction is hardcoded to be along the y-axis (0, 1, 0)

Note that this component can also be used as a frame overlap-mirror
if the up and down reflectivities are set equal. In this case the wall
reflectivity (rPar) should probably be set to 0.

Reflectivity values can either come from datafiles or from
sets of parameters to the standard analytic reflectivity function commonly
used for neutron guides:
R=R0; q<qc, R=(1-tanh((q-m qc)/W))(1-alpha(q-qc)).
If a filename is specified for e.g. rData
the datafile table overrides the analytic function.

GRAVITY: YES

%BUGS
No absorption by mirror.
The reflectivity parameters must be given as literal constants. Using variables
will result in undefined behaviour.
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| rUpPar | 1 | Mirror Parameters for spin up standard reflectivity function | {1.0, 0.0219, 4.07, 3.2, 0.003} |
| rDownPar | 1 | Mirror Parameters for spin down standard reflectivity function | {1.0, 0.0219, 4.07, 3.2, 0.003} |
| rPar | 1 | Guide Parameters for standard reflectivity function | {1.0, 0.0219, 4.07, 3.2, 0.003} |
| rData | str | Guide Reflectivity data file | "" |
| rUpData | str | Mirror Reflectivity data file for spin up | "" |
| rDownData | str | Mirror Reflectivity data file for spin down | "" |
| **xwidth** | m | Width at the guide entry |  |
| **yheight** | m | Height at the guide entry |  |
| **length** | m | length of guide |  |

## Links

- [Source code](Pol_guide_mirror.comp) for `Pol_guide_mirror.comp`.

---

*Generated on mcstas 3.99.99.*