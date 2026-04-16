# The `SAXSNanodiscs` Component

*McXtrace: A sample of monodisperse phospholipid bilayer nanodiscs in solution (water).*

## Identification

- **Site:** 
- **Author:** Martin Cramer Pedersen (mcpe@nbi.dk)
- **Origin:** KU-Science
- **Date:** May 2, 2012

## Description

```text
A component simulating the scattering from a box-shaped, thin solution (water)
of monodisperse phospholipid bilayer nanodiscs.

Example: SAXSNanodiscs( xwidth = 0.01, yheight = 0.01, zdepth = 0.01, SampleToDetectorDistance = 0.48, DetectorRadius = 0.1 )
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| AxisRatio |  | Axis ratio of the bilayer patch. | 1.4 |
| NumberOfLipids |  | Number of lipids per nanodisc. | 130.0 |
| AreaPerLipidHeadgroup | AA^2 | Area per lipid headgroup - default is POPC. | 65.0 |
| HeightOfMSP | AA | Height of the belt protein - default is MSP1D1. | 24.0 |
| VolumeOfOneMSP | AA^3 | Volume of one belt protein - default is MSP1D1. | 26296.5 |
| VolumeOfHeadgroup | AA^3 | Volume of one lipid headgroup - default is POPC. | 319.0 |
| VolumeOfCH2Tail | AA^3 | Volume of the CH2-chains of one lipid - default is POPC. | 818.8 |
| VolumeOfCH3Tail | AA^3 | Volume of the CH3-tails of one lipid - default is POPC. | 108.6 |
| ScatteringLengthOfOneMSP | cm | Scattering length of one belt protein - default is MSP1D1. | 3.34E-9 |
| ScatteringLengthOfHeadgroup | cm | Scattering length of one lipid headgroup - default is POPC. | 4.62E-11 |
| ScatteringLengthOfCH2Tail | cm | Scattering length of the CH2-chains of one lipid - default is POPC. | 6.71E-11 |
| ScatteringLengthOfCH3Tail | cm | Scattering length of the CH3-tails of one lipid - default is POPC. | 5.08E-12 |
| Roughness |  | Factor used to smear the interfaces of the nanodisc. | 3.5 |
| Concentration | mM | Concentration of sample. | 0.01 |
| AbsorptionCrosssection | 1/m | Absorption cross section of the sample. | 0.0 |
| **xwidth** | m | Dimension of component in the x-direction. |  |
| **yheight** | m | Dimension of component in the y-direction. |  |
| **zdepth** | m | Dimension of component in the z-direction. |  |
| **SampleToDetectorDistance** | m | Distance from sample to detector (for focusing the scattered x-rays). |  |
| **DetectorRadius** | m | Radius of the detector (for focusing the scattered x-rays). |  |

## Links

- [Source code](/Users/peterwillendrup/Projects/willend-McCode/mcxtrace-comps/contrib/SAXSNanodiscs.comp) for `SAXSNanodiscs.comp`.

---

*Generated on mcxtrace 3.99.99.*