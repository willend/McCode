# The `SAXSQMonitor` Component

*McXtrace: Release: McXtrace 1.0

A circular detector measuring the radial average of intensity as a function
of the momentum transform in the sample.*

## Identification

- **Site:** 
- **Author:** Martin Cramer Pedersen (mcpe@nbi.dk)
- **Origin:** KU-Science
- **Date:** May 2, 2012

## Description

```text
A circular detector measuring the radial average of intensity as a function
of the momentum transform in the sample. The q-range is set up to
qMax = 4 * PI * sin(TwoThetaMax / 2.0) / LambdaMin;

Example: SAXSQMonitor( RadiusDetector = 0.1, DistanceFromSample = 0.5, LambdaMin = 1, Lambda0 = 1.54, NumberOfBins = 2000 )
Example: SAXSQMonitor( RadiusDetector = 0.1, qMax = 5, Lambda0 = 1.54, NumberOfBins = 2000 )
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| RFilename | str | File used for storing I(r). | "RDetector" |
| qFilename | str | File used for storing I(q). | "QDetector" |
| NumberOfBins | 1 | Number of bins in the r (and q). | 100 |
| restore_xray |  | If set to 1, the component restores the original x-ray. | 0 |
| **RadiusDetector** | m | Radius of the detector (in the xy-plane). |  |
| **DistanceFromSample** | m | Distance from the sample to this component. |  |
| LambdaMin | AA | Max sensitivity in lambda - used to compute the highest possible value of momentum transfer, q. | 1.0 |
| Lambda0 | Angs | If given, the momentum transfers of all rays are computed from this value. Otherwise, instrumental effects are negated Lambda0=2PI/k. | 0.0 |
| qMax | Angs-1 | Max momentum for the Q-monitor. use either qMax or LambdaMin. | 0 |

## Links

- [Source code](/Users/peterwillendrup/Projects/willend-McCode/mcxtrace-comps/contrib/SAXSQMonitor.comp) for `SAXSQMonitor.comp`.

---

*Generated on mcxtrace 3.99.99.*