# The `PolAnalyser_ideal` Component

*McStas: (Unphysical) ideal analyzer.*

## Identification

- **Site:** 
- **Author:** Erik Knudsen
- **Origin:** Risoe
- **Date:** June 2010

## Description

```text
This is an ideal model of a polarization analyser device. Given a polarization vector
it "lets through" a scaled neutron weight. An imperfect analyzer could be modelled by an
analysis vector M with |M|<1.

Example: PolAnalyser_ideal(mx=0, my=1, mz=0)
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| mx | 1 | X-component of polarisation analysis vector -1<mx<1 | 0 |
| my | 1 | Y-component of polarisation analysis vector -1<my<1 | 0 |
| mz | 1 | Z-component of polarisation analysis vector -1<mz<1 | 0 |

## Links

- [Source code](PolAnalyser_ideal.comp) for `PolAnalyser_ideal.comp`.

---

*Generated on mcstas 3.99.99.*