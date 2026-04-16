# The `SAXSLiposomes` Component

*McXtrace: A sample of polydisperse liposomes in solution (water).*

## Identification

- **Site:** 
- **Author:** Martin Cramer Pedersen (mcpe@nbi.dk)
- **Origin:** KU-Science
- **Date:** May 2, 2012

## Description

```text
A component simulating the scattering from a box-shaped, thin solution (water)
of liposomes described by a pentuple-shell model.

Example: SAXSLiposomes( xwidth = 0.01, yheight = 0.01, zdepth = 0.01, SampleToDetectorDistance = 0.48, DetectorRadius = 0.1 )
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| Radius | AA | Average thickness of the liposomes. | 800.0 |
| Thickness | AA | Thickness of the bilayer. | 38.89 |
| SigmaRadius |  | Relative Gaussian deviation of the radius in the distribution of liposomes. | 0.20 |
| nRadius |  | Number of bins in Radius for polydisperse distribution. | 100 |
| VolumeOfHeadgroup | AA^3 | Volume of one lipid headgroup - default is POPC. | 319.0 |
| VolumeOfCH2Tail | AA^3 | Volume of the CH2-chains of one lipid - default is POPC. | 818.8 |
| VolumeOfCH3Tail | AA^3 | Volume of the CH3-tails of one lipid - default is POPC. | 108.6 |
| ScatteringLengthOfHeadgroup | cm | Scattering length of one lipid headgroup - default is POPC. | 4.62E-11 |
| ScatteringLengthOfCH2Tail | cm | Scattering length of the CH2-chains of one lipid - default is POPC. | 6.71E-11 |
| ScatteringLengthOfCH3Tail | cm | Scattering length of the CH3-tails of one lipid - default is POPC. | 5.08E-12 |
| Concentration | mM | Concentration of sample. | 0.01 |
| AbsorptionCrosssection | 1/m | Absorption cross section of the sample. | 0.0 |
| **xwidth** | m | Dimension of component in the x-direction. |  |
| **yheight** | m | Dimension of component in the y-direction. |  |
| **zdepth** | m | Dimension of component in the z-direction. |  |
| **SampleToDetectorDistance** | m | Distance from sample to detector (for focusing the scattered x-rays). |  |
| **DetectorRadius** | m | Radius of the detector (for focusing the scattered x-rays). |  |

## Links

- [Source code](/Users/peterwillendrup/Projects/willend-McCode/mcxtrace-comps/contrib/SAXSLiposomes.comp) for `SAXSLiposomes.comp`.

---

*Generated on mcxtrace 3.99.99.*