# The `Sqq_w_monitor` Component

*McStas: Monitor outputting a series of energy-planes in a subset of reciprocal space, spanned by
scattering vectors qa(x,z) and qb(x,z) in the component x-z plane.*

## Identification

- **Site:** 
- **Author:** Peter Willendrup
- **Origin:** DTU
- **Date:** June-July, 2018

## Description

```text
Cylindrical monitor on the x-z plane outputting a series of energy-planes in a subset of reciprocal
space, spanned by scattering vectors qa(x,z) and qb(x,z).

The radius and yheight parameters are not used for propagation, but only to define the outgoing divergence
limit considered when estimating k_f

The assumption is that the "current" neutron represents the final state, whereas the incoming state
is found by restoring the neutron state "index" components earlier.

Example: Sqq_w_monitor(filename="output",radius=1, yheight=0.05, Emin=0,Emax=5,nE=11,nqa=100,nqb=100,qamin=1,qamax=10,qbmin=1qbmax=10, vix="vix", viy="viy", viz="viz")
AT (0,0,0) RELATIVE sample
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| radius | m | Cylinder radius | 1 |
| yheight | m | Cylinder height | 0.05 |
| qax | 1 | x-component of 1st q-vector | 1 |
| qaz | 1 | z-component of 1st q-vector | 0 |
| qbx | 1 | x-component of 2nd q-vector | 0 |
| qbz | 1 | z-component of 2nd q-vector | 1 |
| qamin | AA^-1 | Defines interval (qamin,qamax) where monitor measures in nqa bins | 0 |
| qamax | AA^-1 | Defines interval (qamin,qamax) where monitor measures in nqa bins | 2 |
| qbmin | AA^-1 | Defines interval (qbmin,qbmax) where monitor measures in nqb bins | 0 |
| qbmax | AA^-1 | Defines interval (qbmin,qbmax) where monitor measures in nqb bins | 2 |
| Emin | meV | Defines the energy-transfer [Emin,Emax] window to monitor in nE bins | 0 |
| Emax | meV | Defines the energy-transfer [Emax,Emax] window to monitor in nE bins | 5 |
| nqa | int | Number of bins along qa direction | 90 |
| nqb | int | Number of bins along qb direction | 90 |
| nE | int | Number of energy slices | 10 |
| filename | string | Base filename to use, nE+1 files will be output | 0 |
| nowritefile | 1 | If set, monitor will skip writing to disk | 0 |
| nosum | 1 | If set, monitor will skip writing the energy-summed array to disk | 0 |
| vix | string | Points to instrument-level USERVAR for reading an earlier x-velocity | "" |
| viy | string | Points to instrument-level USERVAR for reading an earlier y-velocity | "" |
| viz | string | Points to instrument-level USERVAR for reading an earlier z-velocity | "" |

## Links

- [Source code](Sqq_w_monitor.comp) for `Sqq_w_monitor.comp`.

---

*Generated on mcstas 3.99.99.*