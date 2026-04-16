# The `Vitess_input` Component

*McStas: Read neutron state parameters from VITESS neutron filename.*

## Identification

- **Site:** 
- **Author:** Kristian Nielsen
- **Origin:** Risoe/ILL
- **Date:** June 6, 2000

## Description

```text
Source-like component reading neutron state parameters from a
VITESS neutron filename. Used to interface McStas components or
simulations into VITESS. Each neutron is 104 bytes.

Example: Vitess_input(filename="MySource.vit", bufsize = 10000, repeat_count = 2)

%BUGS
We recommend NOT to use parallel execution (MPI) with this component.
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| filename | string | Filename of neutron file to read. Default (NULL) is standard input. Empty string "" unactivates component | 0 |
| bufsize | records | Size of neutron input buffer | 10000 |
| repeat_count | 1 | Number of times to repeat each neutron read | 1 |

## Links

- [Source code](/Users/peterwillendrup/Projects/willend-McCode/mcstas-comps/obsolete/Vitess_input.comp) for `Vitess_input.comp`.

---

*Generated on mcstas 3.99.99.*