# The `SANSSpheresPolydisperse` Component

*McStas: A sample of mono- or polydisperse spherical particles in solution.*

## Identification

- **Site:** 
- **Author:** Linda Udby (udby@nbi.dk) - modified from SANSSpheres by Martin Cramer Pedersen (mcpe@nbi.dk)
- **Origin:** KU-Science
- **Date:** October 17, 2012

## Description

```text
A simple component simulating the scattering from a box-shaped, thin solution
of monodisperse, spherical particles.
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| R | AA | Radius of the spherical particles. | 100.0 |
| dR | AA | Variance of the radius of spherical particles. Default 0 (monodisperse spheres) | 0.0 |
| Concentration | mM | Concentration of sample. | 0.01 |
| DeltaRho | cm/AA^3 | Excess scattering length density of the | 1.0e-14 |
| AbsorptionCrosssection | 1/m | Absorption cross section of the sample. | 0.0 |
| **xwidth** | m | Dimension of component in the x-direction. |  |
| **yheight** | m | Dimension of component in the y-direction. |  |
| **zdepth** | m | Dimension of component in the z-direction. |  |
| **SampleToDetectorDistance** | m | Distance from sample to detector (for |  |
| **DetectorRadius** | m | Radius of the detector (for focusing the |  |

## Links

- [Source code](SANSSpheresPolydisperse.comp) for `SANSSpheresPolydisperse.comp`.

---

*Generated on mcstas 3.99.99.*