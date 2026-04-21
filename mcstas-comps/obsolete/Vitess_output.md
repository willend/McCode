# The `Vitess_output` Component

*McStas: Write neutron state parameters to VITESS neutron filename.*

## Identification

- **Site:** 
- **Author:** Kristian Nielsen
- **Origin:** Risoe/ILL
- **Date:** June 6, 2000

## Description

```text
Detector-like component writing neutron state parameters to a
VITESS neutron filename. Used to interface McStas components or
simulations into VITESS. Each neutron is 104 bytes.

Note that when standard output is used, as is the default, no
monitors or other components that produce terminal output must be
used, or the neutron output from this component will become
corrupted.

Example: Vitess_output(filename="MySource.vit", bufsize = 10000, progress = 1)

%BUGS
This component will NOT work with parallel execution (MPI).
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| filename | string | Filename of neutron file to write. Default is standard output | 0 |
| bufsize | records | Size of neutron output buffer | 10000 |
| progress | flag | If not zero, output dots as progress indicator | 0 |

## Links

- [Source code](Vitess_output.comp) for `Vitess_output.comp`.

---

*Generated on mcstas 3.99.99.*