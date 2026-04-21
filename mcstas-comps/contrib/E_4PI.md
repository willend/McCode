# The `E_4PI` Component

*McStas: Spherical Energy-sensitive detector*

## Identification

- **Site:** 
- **Author:** Duc Le
- **Origin:** ISIS
- **Date:** 2000s

## Description

```text
Example: E_4PI(filename="e4pi.dat",ne=200,Emin=0,Emax=E*2)
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| ne | 1 | Number of energy bins | 50 |
| Emin | meV | Minimum energy measured | 0 |
| Emax | meV | Maximum energy measured | 5 |
| filename | string | Name of file in which to store the output data | 0 |
| radius | m | Radius of detector (m) | 1 |
| restore_neutron | 1 | If set, the monitor does not influence the neutron state | 0 |

## Links

- [Source code](E_4PI.comp) for `E_4PI.comp`.
- <A HREF="http://neutron.risoe.dk/mcstas/components/tests/powder/">Test
- results</A> (not up-to-date).

---

*Generated on mcstas 3.99.99.*