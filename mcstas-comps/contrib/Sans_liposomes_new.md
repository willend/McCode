# The `Sans_liposomes_new` Component

*McStas: Release: McStas 1.12

SANS sample, spherical shells in thin solution with gaussian size distribution*

## Identification

- **Site:** 
- **Author:** P. Willendrup, K. Lefmann, L. Arleth, L. Udby
- **Origin:** Risoe
- **Date:** 19.12.2003

## Description

```text
Sample for Small Angle Neutron Scattering - spherical shells in thin solution with gaussian size distribution
The shape of the sample may be a cylinder of given radius or a box with dimensions
xwidth, yheight, zthick. qmax defines a cutoff in q.

Example: Sans_spheres(R = 100, dR = 5, dbilayer=35, Phi = 1e-3, Delta_rho = 0.6, sigma_a = 50, qmax = 0.3 ,xwidth=0.01, yheight=0.01, zthick=0.005)

%BUGS
This component does NOT simulate absolute intensities. This latter depends on the detector parameters.
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| R | AA | Radius of scattering hard spheres | 100 |
| dR |  |  | 0.0 |
| Phi | 1 | Particle volume fraction | 1e-3 |
| Delta_rho | fm/AA^3 | Excess scattering length density | 0.6 |
| sigma_a | m^-1 | Absorption cross section density at 2200 m/s | 0.50 |
| dist | m | Distance from sample to detector | 6 |
| Rdet | m | Detector (disk-shaped) radius | 0.5 |
| xwidth | m | horiz. dimension of sample, as a width | 0.01 |
| yheight | m | vert . dimension of sample, as a height | 0.01 |
| zthick | m | thickness of sample | 0.005 |
| qmax | AA^-1 | Maximum momentum transfer | 0 |
| dbilayer | AA | Thickness of shell | 35 |

## Links

- [Source code](Sans_liposomes_new.comp) for `Sans_liposomes_new.comp`.
- The test/example instrument <a href="../examples/SANS.instr">SANS.instr</a>.

---

*Generated on mcstas 3.99.99.*