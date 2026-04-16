# The `SANSEllipticCylinders` Component

*McStas: A sample of monodisperse cylindrical particles with elliptic cross section in
solution.*

## Identification

- **Site:** 
- **Author:** Martin Cramer Pedersen (mcpe@nbi.dk)
- **Origin:** KU-Science
- **Date:** October 17, 2012

## Description

```text
A component simulating the scattering from a box-shaped, thin solution
of monodisperse, cylindrical particles with elliptic cross section.
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| R1 | AA | First semiaxis of the cross section of the | 20.0 |
| R2 | AA | Second semiaxis of the cross section of the | 40.0 |
| Height | AA | Height of the elliptic cylinder. | 100.0 |
| Concentration | mM | Concentration of sample. | 0.01 |
| DeltaRho | cm/AA^3 | Excess scattering length density of the | 1.0e-14 |
| AbsorptionCrosssection | 1/m | Absorption cross section of the sample. | 0.0 |
| **xwidth** | m | Dimension of component in the x-direction. |  |
| **yheight** | m | Dimension of component in the y-direction. |  |
| **zdepth** | m | Dimension of component in the z-direction. |  |
| **SampleToDetectorDistance** | m | Distance from sample to detector (for |  |
| **DetectorRadius** | m | Radius of the detector (for focusing the |  |

## Links

- [Source code](/Users/peterwillendrup/Projects/willend-McCode/mcstas-comps/contrib/SANSEllipticCylinders.comp) for `SANSEllipticCylinders.comp`.

---

*Generated on mcstas 3.99.99.*