# The `SANSNanodiscsWithTagsFast` Component

*McStas: A sample of monodisperse phospholipid bilayer nanodiscs in solution (water) - with
histidine tag still on the belt proteins.*

## Identification

- **Site:** 
- **Author:** Martin Cramer Pedersen (mcpe@nbi.dk)
- **Origin:** KU-Science
- **Date:** October 17, 2012

## Description

```text
A component very similar to EmptyNanodiscsWithTags.comp - however, the
scattering profile is only computed once, and linear interpolation is the used
to simulate the instrument.
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| NumberOfQBins |  | Number of points generated in inital scattering profile. | 200 |
| AxisRatio |  | Axis ratio of the bilayer patch. | 1.4 |
| NumberOfLipids |  | Number of lipids per nanodisc. | 130.0 |
| AreaPerLipidHeadgroup | AA^2 | Area per lipid headgroup - default is POPC. | 65.0 |
| HeightOfMSP | AA | Height of the belt protein - default is MSP1D1. | 24.0 |
| RadiusOfGyrationForHisTag | AA | Radius of gyration for the his-tag. | 12.7 |
| VolumeOfOneMSP | AA^3 | Volume of one belt protein - default is MSP1D1. | 26296.5 |
| VolumeOfHeadgroup | AA^3 | Volume of one lipid headgroup - default is POPC. | 319.0 |
| VolumeOfCH2Tail | AA^3 | Volume of the CH2-chains of one lipid - default is POPC. | 818.8 |
| VolumeOfCH3Tail | AA^3 | Volume of the CH3-tails of one lipid - default is POPC. | 108.6 |
| VolumeOfOneHisTag | AA^3 | Volume of one his-tag. | 2987.3 |
| ScatteringLengthOfOneMSP | cm | Scattering length of one belt protein - default is MSP1D1. | 8.8E-10 |
| ScatteringLengthOfHeadgroup | cm | Scattering length of one lipid headgroup - default is POPC. | 7.05E-12 |
| ScatteringLengthOfCH2Tail | cm | Scattering length of the CH2-chains of one lipid - default is POPC. | -1.76E-12 |
| ScatteringLengthOfCH3Tail | cm | Scattering length of the CH3-tails of one lipid - default is POPC. | -9.15E-13 |
| ScatteringLengthOfOneHisTag | cm | Scattering length of one his-tag. | 1.10E-10 |
| Roughness |  | Factor used to smear the interfaces of the nanodisc. | 5.0 |
| Concentration | mM | Concentration of sample. | 0.01 |
| RhoSolvent | cm/AA^3 | Scattering length density of solvent - default is D2O. | 6.4e-14 |
| AbsorptionCrosssection | 1/m | Absorption cross section of the sample. | 0.0 |
| **xwidth** | m | Dimension of component in the x-direction. |  |
| **yheight** | m | Dimension of component in the y-direction. |  |
| **zdepth** | m | Dimension of component in the z-direction. |  |
| **SampleToDetectorDistance** | m | Distance from sample to detector (for focusing the scattered neutrons). |  |
| **DetectorRadius** | m | Radius of the detector (for focusing the scattered neutrons). |  |
| qMin | AA^-1 | Lowest q-value, for which a point is generated in the scattering profile | 0.001 |
| qMax | AA^-1 | Highest q-value, for which a point is generated in the scattering profile | 1.0 |

## Links

- [Source code](/Users/peterwillendrup/Projects/willend-McCode/mcstas-comps/contrib/SANSNanodiscsWithTagsFast.comp) for `SANSNanodiscsWithTagsFast.comp`.

---

*Generated on mcstas 3.99.99.*