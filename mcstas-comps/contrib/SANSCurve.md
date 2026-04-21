# The `SANSCurve` Component

*McStas: A component mimicking the scattering from a given I(q)-curve by using
linear interpolation between the given points.*

## Identification

- **Site:** 
- **Author:** Søren Kynde (kynde@nbi.dk)
- **Origin:** KU-Science
- **Date:** October 17, 2012

## Description

```text
A box-shaped component simulating the scattering from any given I(q)-curve.
The component uses linear interpolation to generate the points necessary to
compute the scattering of any given neutron.
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| DeltaRho | cm/AA^3 | Excess scattering length density of the particles. | 1.0e-14 |
| Volume | AA^3 | Volume of the particles. | 1000.0 |
| Concentration | mM | Concentration of sample. | 0.01 |
| AbsorptionCrosssection | 1/m | Absorption cross section of the sample. | 0.0 |
| **xwidth** | m | Dimension of component in the x-direction. |  |
| **yheight** | m | Dimension of component in the y-direction. |  |
| **zdepth** | m | Dimension of component in the z-direction. |  |
| **SampleToDetectorDistance** | m | Distance from sample to detector (for focusing the scattered neutrons). |  |
| **DetectorRadius** | m | Radius of the detector (for focusing the scattered neutrons). |  |
| FileWithCurve |  | Datafile with the given I(q). | "Curve.dat" |

## Links

- [Source code](SANSCurve.comp) for `SANSCurve.comp`.

---

*Generated on mcstas 3.99.99.*