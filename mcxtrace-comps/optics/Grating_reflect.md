# The `Grating_reflect` Component

*McXtrace: A reflective grating.*

## Identification

- **Site:** 
- **Author:** Erik B Knudsen (erkn@fysik.dtu.dk), Kristian Sorensen and Philip Smith
- **Origin:** DTU
- **Date:** June 2021

## Description

```text
A reflective grating that diffracts incident photons.
The grating is in the XZ-plane. It then reflects the incoming photon using a MC picked angle,
where the angle is picked from a uniform distribution of width d_phi, i.e. U[-d_phi/2,d_phi/2]
The Monte Carlo wight of the ray is then adjusted wrt. to the grating interference pattern, and
the diffraction pattern associated with each grating line. All lines are considered equal.
For more efficient sampling of a particular direction the centre of the d_phi may be shifted
using the parameters order or phi0. In the latter case a set angle is chosen as the centre of the
sampled interval, in the former the centre angle is computed from the specified grating order.

In an upcoming release this grating model will also include a blazed grating.

Example: Grating_reflect(
d_phi=1,order=0,rho_l=100,zdepth=102e-3,xwidth=102e-3)
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| d_phi | deg | Range of diffraction angle that is to be simulated -d_phi/2 ; d_phi/2. | 1 |
| R0 | 0-1 | Constant reflecticity of the grating [0;1]. | 1 |
| rho_l | l/mm | Number of lines pr mm of the grating. | 800 |
| order | 1 | The target order of the grating. If non-zero d_phi will be centered around this scattering line. | 0 |
| phi0 | deg | Target angle to center d_phi. If this is set to 0 the 0th (or any other chosen by the parameter order) order line will be used. | 0 |
| zdepth | m | The length of the grating. | 0.015 |
| xwidth | m | The width of the grating. | 0.136 |
| verbose | 0/1 | If non-zero, more information will be displayed. Nb. generates much output. | 0 |

## Links

- [Source code](/Users/peterwillendrup/Projects/willend-McCode/mcxtrace-comps/optics/Grating_reflect.comp) for `Grating_reflect.comp`.

---

*Generated on mcxtrace 3.99.99.*