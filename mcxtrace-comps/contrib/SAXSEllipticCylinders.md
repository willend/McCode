# The `SAXSEllipticCylinders` Component

*McXtrace: A sample of monodisperse cylindrical particles with elliptic cross section in
solution.*

## Identification

- **Site:** 
- **Author:** Martin Cramer Pedersen (mcpe@nbi.dk)
- **Origin:** KU-Science
- **Date:** May 2, 2012

## Description

```text
A component simulating the scattering from a box-shaped, thin solution
of monodisperse, cylindrical particles with elliptic cross section.

Example: SAXSEllipticCylinders( xwidth = 0.01, yheight = 0.01, zdepth = 0.01, SampleToDetectorDistance = 0.48, DetectorRadius = 0.1 )
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| R1 | AA | First semiaxis of the cross section of the elliptic cylinder. | 20.0 |
| R2 | AA | Second semiaxis of the cross section of the elliptic cylinder. | 40.0 |
| Height | AA | Height of the cylinder. | 100.0 |
| Concentration | mM | Concentration of sample. | 0.01 |
| DeltaRho | cm/AA^3 | Excess scattering length density of the particles. | 1.0e-14 |
| AbsorptionCrosssection | 1/m | Absorption cross section of the sample. | 0.0 |
| **xwidth** | m | Dimension of component in the x-direction. |  |
| **yheight** | m | Dimension of component in the y-direction. |  |
| **zdepth** | m | Dimension of component in the z-direction. |  |
| **SampleToDetectorDistance** | m | Distance from sample to detector (for focusing the scattered x-rays). |  |
| **DetectorRadius** | m | Radius of the detector (for focusing the scattered x-rays). |  |

## Links

- [Source code](/Users/peterwillendrup/Projects/willend-McCode/mcxtrace-comps/contrib/SAXSEllipticCylinders.comp) for `SAXSEllipticCylinders.comp`.

---

*Generated on mcxtrace 3.99.99.*