# The `SANS_spheres2` Component

*McStas: Sample for Small Angle Neutron Scattering - hard spheres in thin solution, mono disperse.*

## Identification

- **Site:** 
- **Author:** P. Willendrup, derived from H. Frielinghaus SANS_benchmark2
- **Origin:** DTU
- **Date:** 16.12.2019

## Description

```text
Sample for Small Angle Neutron Scattering - hard spheres in thin solution, mono disperse.

For the scattering simulation a high fraction of neutron paths is directed to the scattering (exact fraction is sc_aim).
The remaining paths are used for the transmitted beams. The absolute intensities are treated accordingly, and the p-parameter is set accordingly.

For the scattering probability, the integral of the scattering function between Q = 0.0001 and 1.0 AA-1 is calculated.
This is used in terms of transmisson, and of course for the scattering probability.
In this way, multiple scattering processes could be treated as well.

The typical SANS range was considered to be between 0.0001 and 1.0 AA-1.
This means that the scattered neutrons are equally distributed in this range on logarithmic Q-scales.

Example: SANS_spheres2(xwidth=0.01, yheight=0.01, zthick=0.001, model=1.0, dsdw_inc=0.02, sc_aim=0.97, sans_aim=0.95, R-150)
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| xwidth | m | Width of sample volume | 0.01 |
| yheight | m | Height of sample volume | 0.01 |
| zthick | m | Thickness of sample volume | 0.001 |
| dsdw_inc | cm^-1 | The incoherent background from the overall sample, should read ca. 1.0 for water, 0.5 for half D2O, half H2O, and ca. 0.02 for D2O | 0.02 |
| sc_aim | 1 | The fraction of neutron paths used to represent the scattered neutrons (including everything: incoherent and coherent). rest is transmission. | 0.97 |
| sans_aim | 1 | The fraction of neutron paths used to represent the scattered neutrons in the sans-range (up to 1.0AA-1). rest is incoherent with Q>1AA-1. | 0.95 |
| R | AA | Radius of dilute, monodisperse spheres | 150 |
| phi | 1 | Volume-ratio of the spheres wrt. solution | 1e-3 |
| drho | cm^-2 | Scattering length density | 6e10 |
| singlesp | 1 | Switches between multiple scattering (parameter zero 0.0) and single scattering (parameter 1.0). The sc_aim directs a fraction of paths to the first scattering process accordingly. The no. of paths for the second scattering process is derived from the real probability. Up to 10 scattering processes are considered. | 1 |
| Qmind | AA^-1 | Lower limit of "SANS" scattering | 0.0001 |
| Qmaxd | AA^-1 | Upper limit of "SANS" scattering | 2.1544346900319 |

## Links

- [Source code](/Users/peterwillendrup/Projects/willend-McCode/mcstas-comps/samples/SANS_spheres2.comp) for `SANS_spheres2.comp`.

---

*Generated on mcstas 3.99.99.*