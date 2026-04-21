# The `Sqw_monitor` Component

*McStas: Monitor outputting S(q,w)*

## Identification

- **Site:** 
- **Author:** Peter Willendrup
- **Origin:** DTU
- **Date:** November, 2020

## Description

```text
The assumption is that the "current" neutron represents the final state, whereas the incoming state
is found by restoring the neutron state "index" components earlier.

Example: Sqw_monitor(filename="output", Emin=0,Emax=5,nE=11,nq=100,nqb=100,qmin=0,qmax=1,index=-2)
AT (0,0,0) RELATIVE sample
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| qmin | AA^-1 | Defines interval (qmin,qmax) where monitor measures in nq bins | 0 |
| qmax | AA^-1 | Defines interval (qmin,qmax) where monitor measures in nq bins | 2 |
| Emin | meV | Defines the energy-transfer [Emin,Emax] window to monitor in nE bins | 0 |
| Emax | meV | Defines the energy-transfer [Emax,Emax] window to monitor in nE bins | 5 |
| nq | int | Number of bins in q | 90 |
| nE | int | Number of energy slices | 90 |
| filename | string | Base filename to use, nE+1 files will be output | 0 |
| nowritefile | 1 | If set, monitor will skip writing to disk | 0 |
| vix | string | Points to instrument-level USERVAR for reading an earlier x-velocity | "" |
| viy | string | Points to instrument-level USERVAR for reading an earlier y-velocity | "" |
| viz | string | Points to instrument-level USERVAR for reading an earlier z-velocity | "" |
| radius | m | Cylinder radius (optional) | 0 |
| yheight | m | Cylinder height  (optional) | 0 |

## Links

- [Source code](Sqw_monitor.comp) for `Sqw_monitor.comp`.

---

*Generated on mcstas 3.99.99.*