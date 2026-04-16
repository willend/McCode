# The `SANSLiposomes` Component

*McStas: A sample of polydisperse liposomes in solution (water).*

## Identification

- **Site:** 
- **Author:** Martin Cramer Pedersen (mcpe@nbi.dk)
- **Origin:** KU-Science
- **Date:** October 17, 2012

## Description

```text
A component simulating the scattering from a box-shaped, thin solution (water)
of liposomes described by a pentuple-shell model.
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| Radius | AA | Average thickness of the liposomes. | 800.0 |
| Thickness | AA | Thickness of the bilayer. | 38.89 |
| SigmaRadius |  | Relative Gaussian deviation of the radius in the distribution of liposomes. | 0.20 |
| VolumeOfHeadgroup | AA^3 | Volume of one lipid headgroup - default is POPC. | 319.0 |
| VolumeOfCH2Tail | AA^3 | Volume of the CH2-chains of one lipid - default is POPC. | 818.8 |
| VolumeOfCH3Tail | AA^3 | Volume of the CH3-tails of one lipid - default is POPC. | 108.6 |
| ScatteringLengthOfHeadgroup | cm | Scattering length of one lipid headgroup - default is POPC in D2O. | 7.05E-12 |
| ScatteringLengthOfCH2Tail | cm | Scattering length of the CH2-chains of one lipid - default is POPC in D2O. | -1.76E-12 |
| ScatteringLengthOfCH3Tail | cm | Scattering length of the CH3-tails of one lipid - default is POPC in D2O. | -9.15E-13 |
| Concentration | mM | Concentration of sample. | 0.01 |
| RhoSolvent | cm/AA^3 | Scattering length density of solvent - default is D2O. | 6.4e-14 |
| AbsorptionCrosssection | 1/m | Absorption cross section of the sample. | 0.0 |
| **xwidth** | m | Dimension of component in the x-direction. |  |
| **yheight** | m | Dimension of component in the y-direction. |  |
| **zdepth** | m | Dimension of component in the z-direction. |  |
| **SampleToDetectorDistance** | m | Distance from sample to detector (for focusing the scattered neutrons). |  |
| **DetectorRadius** | m | Radius of the detector (for focusing the scattered neutrons). |  |

## Links

- [Source code](/Users/peterwillendrup/Projects/willend-McCode/mcstas-comps/contrib/SANSLiposomes.comp) for `SANSLiposomes.comp`.

---

*Generated on mcstas 3.99.99.*