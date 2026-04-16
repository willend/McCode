# The `Shell_p` Component

*McXtrace: Single parabolic shell as part of a Wolter optic.*

## Identification

- **Site:** 
- **Author:** Erik B Knudsen and Desiree D. M. Ferreira
- **Origin:** DTU Physics, DTU Space
- **Date:** Feb. 2016

## Description

```text
A single shell is simulated. The top and bottom are curved cylindrically
azimuthally. The sagital profile is defined by a parabola, which passes through the radii raidus_m
at z=0, and radius_p at zentry (<0).

To intersect the Wolter I plates we take advatage of the azimuthal symmetry and only consider the radial component
of the photon's wavevector.

Imperfect mirrors may be modelled using one of 4 models. In all cases the surface normal of the mirror
at the ideal mirror intersection point is perturbed before the exit vector is computed.
1. Longitudinal 1D. A perturbation angle is chosen from a uniform distribution with width waviness.
2. Isotropic 2D. The surface normal is perturbed by choosing an angle on a disc with radius waviness
3. Externally measured/computed data. We interpolate in a data-file consisting of blocks of dtheta/theta
with 1 block per energy. dtheta is a sampled angle offset from the nominal Fresnel grazing angle
theta.
4. Double gaussian. dtheta is chosen from one of two gaussian distributions. Either specular or off-specular, where the
widths (sigmas) are given by the tables in the file "wave_file". If the off-specular case the behaviour is similar
to 2D uniform case.

In the case of 3, the format of the data file should be:
#e_min=0.1
#e_max=15
#e_step=0.01
#theta_min=0.01
#theta_max=1.5
#theta_step=0.01
#dtheta_min=-0.02
#dtheta_max=0.02
#dtheta_step=0.001
1.0  0.9  0.8  0.75  ...
0.99 0.89 0.79 0.749 ...
...
#block 2 (energy data point 2)
1.0  0.9  0.8  0.75  ...
0.99 0.89 0.79 0.749 ...
...

I.e. one 2D data block per energy data point where rows represent the steps in nominal incident angle, and columns
represent the sampled granularity of the off-specular scattering.

Example: Shell_p( radius_p=0.535532, radius_m=0.533113, zdepth=0.5, Z0=12, yheight=1e-2, R_d=1)
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| **radius_p** | m | Ring radius of the upper (reflecting) plate of the shell at the edge furthest away from the focal point. |  |
| **radius_m** | m | Ring radius of the upper (reflecting) plate of the shell at the intersection with the hyperbolic section. |  |
| **Z0** | m | Distance between optics centre plane and focal spot (essentially focal length). |  |
| **yheight** | m | Height of the shell. |  |
| chamferwidth | m | Width of side walls. | 0 |
| gap | m | Gap between the plate and the intersection plane with the hyperbolic section. | 0 |
| zdepth |  |  | 0 |
| mirror_reflec |  | Data file containing reflectivities of the reflector surface (TOP). | "" |
| bottom_reflec |  | Data file containing reflectivities of the bottom surface (BOTTOM). | "" |
| wave_file |  |  | "" |
| R_d |  | Default reflectivity value to use if no reflectivity file is given. Useful f.i. is one surface is reflecting and the others absorbing. | 1 |
| wave_model |  | Flag to choose waviness model. 1. longitudinal uniform, 2. 2D-uniform, 3. lorentzian sagittal, 4. double gaussian sagittal. See above for details. | 0 |
| waviness | rad | Waviness of the pore reflecting surface. The slope error is assumed to be uniformly distributed in the interval "[-waviness:waviness]". | 0 |
| verbose |  | If !=0 output extra info during simulation. | 0 |

## Links

- [Source code](/Users/peterwillendrup/Projects/willend-McCode/mcxtrace-comps/astrox/Shell_p.comp) for `Shell_p.comp`.

---

*Generated on mcxtrace 3.99.99.*