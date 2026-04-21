# The `Fermi_chop2a` Component

*McStas: SNS Fermi Chopper as used in SNS_ARCS*

## Identification

- **Site:** 
- **Author:** Garrett Granroth
- **Origin:** SNS Oak Ridge,TN
- **Date:** 6 Feb 2005

## Description

```text
Models an SNS Fermi Chopper, used in the SNS_ARCS instrument model.
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| **len** | m | slit package length |  |
| **w** | m | slit package width |  |
| **nu** | Hz | frequency |  |
| **delta** | sec | time from edge of chopper to center Phase angle |  |
| **tc** | sec | time when desired neutron is at the center of the chopper |  |
| **ymin** | m | Lower y bound |  |
| **ymax** | m | Upper y bound |  |
| **nchan** | 1 | number of channels in chopper |  |
| **bw** | m | blade width |  |
| **blader** | m | blade radius |  |

## Links

- [Source code](Fermi_chop2a.comp) for `Fermi_chop2a.comp`.

---

*Generated on mcstas 3.99.99.*