# The `SANSQMonitor` Component

*McStas: A circular detector measuring the radial average of intensity as a function
of the momentum transform in the sample.*

## Identification

- **Site:** 
- **Author:** S&oslash;ren Kynde (kynde@nbi.dk) and Martin Cramer Pedersen (mcpe@nbi.dk)
- **Origin:** KU-Science
- **Date:** October 17, 2012

## Description

```text
A simple component simulating the scattering from a box-shaped, thin solution
of monodisperse, spherical particles.
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| NumberOfBins |  | Number of bins in the r (and q). | 100 |
| RFilename |  | File used for storing I(r). | "RDetector" |
| qFilename |  | File used for storing I(q). | "QDetector" |
| **RadiusDetector** | m | Radius of the detector (in the xy-plane). |  |
| **DistanceFromSample** | m | Distance from the sample to this component. |  |
| LambdaMin | AA | Max sensitivity in lambda - used to compute the highest possible value of momentum transfer, q. | 1.0 |
| Lambda0 |  | If lambda is given, the momentum transfers of all rays are computed from this value. Otherwise, instrumental effects are neglected. | 0.0 |
| restore_neutron |  | If set to 1, the component restores the original neutron. | 0 |

## Links

- [Source code](SANSQMonitor.comp) for `SANSQMonitor.comp`.

---

*Generated on mcstas 3.99.99.*