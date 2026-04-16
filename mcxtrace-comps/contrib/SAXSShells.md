# The `SAXSShells` Component

*McXtrace: Release: McXtrace 1.0

A sample of monodisperse shell-like particles in solution.*

## Identification

- **Site:** 
- **Author:** Martin Cramer Pedersen (mcpe@nbi.dk)
- **Origin:** KU-Science
- **Date:** May 11, 2012

## Description

```text
A simple component simulating the scattering from a box-shaped, thin solution
of monodisperse, shell-like particles.

Example: Sample1 = SAXSShells( xwidth = 0.01, yheight = 0.01, zdepth = 0.01, SampleToDetectorDistance = 0.5, DetectorRadius = 0.1, R = 50.0, Thickness = 20.0 )
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| R | AA | Average radius of the particles. | 100.0 |
| Thickness | AA | Thickness of the shell - so that the outer radius is R + Thickness and the inner is R - Thickness. | 5.0 |
| Concentration | mM | Concentration of sample. | 0.01 |
| DeltaRho | cm/AA^3 | Excess scattering length density of the particles. | 1.0e-14 |
| AbsorptionCrosssection | 1/m | Absorption cross section of the sample. | 0.0 |
| **xwidth** | m | Dimension of component in the x-direction. |  |
| **yheight** | m | Dimension of component in the y-direction. |  |
| **zdepth** | m | Dimension of component in the z-direction. |  |
| **SampleToDetectorDistance** | m | Distance from sample to detector (for focusing the scattered x-rays). |  |
| **DetectorRadius** | m | Radius of the detector (for focusing the scattered x-rays). |  |

## Links

- [Source code](/Users/peterwillendrup/Projects/willend-McCode/mcxtrace-comps/contrib/SAXSShells.comp) for `SAXSShells.comp`.

---

*Generated on mcxtrace 3.99.99.*