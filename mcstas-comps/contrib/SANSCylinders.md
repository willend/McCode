# The `SANSCylinders` Component

*McStas: A sample of monodisperse cylindrical particles in solution.*

## Identification

- **Site:** 
- **Author:** Martin Cramer Pedersen (mcpe@nbi.dk)
- **Origin:** KU-Science
- **Date:** October 17, 2012

## Description

```text
A component simulating the scattering from a box-shaped, thin solution
of monodisperse, cylindrical particles.
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| R | AA | Semiaxis of the cross section of the cylinder. | 40.0 |
| Height | AA | Height of the cylinder. | 100.0 |
| Concentration | mM | Concentration of sample. | 0.01 |
| DeltaRho | cm/AA^3 | Excess scattering length density of the particles. | 1.0e-14 |
| AbsorptionCrosssection | 1/m | Absorption cross section of the sample. | 0.0 |
| **xwidth** | m | Dimension of component in the x-direction. |  |
| **yheight** | m | Dimension of component in the y-direction. |  |
| **zdepth** | m | Dimension of component in the z-direction. |  |
| **SampleToDetectorDistance** | m | Distance from sample to detector (for focusing the scattered neutrons). |  |
| **DetectorRadius** | m | Radius of the detector (for focusing the scattered neutrons). |  |

## Links

- [Source code](/Users/peterwillendrup/Projects/willend-McCode/mcstas-comps/contrib/SANSCylinders.comp) for `SANSCylinders.comp`.

---

*Generated on mcstas 3.99.99.*