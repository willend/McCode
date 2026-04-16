# The `SANSShells` Component

*McStas: A sample of monodisperse shell-like particles in solution.*

## Identification

- **Site:** 
- **Author:** Martin Cramer Pedersen (mcpe@nbi.dk)
- **Origin:** KU-Science
- **Date:** October 17, 2012

## Description

```text
A simple component simulating the scattering from a box-shaped, thin solution
of monodisperse, shell-like particles.
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
| **SampleToDetectorDistance** | m | Distance from sample to detector (for focusing the scattered neutrons). |  |
| **DetectorRadius** | m | Radius of the detector (for focusing the scattered neutrons). |  |

## Links

- [Source code](/Users/peterwillendrup/Projects/willend-McCode/mcstas-comps/contrib/SANSShells.comp) for `SANSShells.comp`.

---

*Generated on mcstas 3.99.99.*