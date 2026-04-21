# The `Derotator` Component

*McStas: The counterpart of the Rotator component.*

## Identification

- **Site:** 
- **Author:** Emmanuel Farhi
- **Origin:** <a href="http://www.ill.fr">ILL</a>
- **Date:** June 20th 2013

## Description

```text
A component which stops the rotative frame set by the Rotator component.
Its position should better coincide with the Rotator instance.
Components preceding the Derotator are rotating, all following are steady.

Example:
R=Rotator(nu=14, phase=0)
...
DR=Derotator(rotator="R")
AT (0,0,0) RELATIVE R
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| **rotator** | string | the name of the Rotator component used to initiate the rotation |  |

## Links

- [Source code](Derotator.comp) for `Derotator.comp`.

---

*Generated on mcstas 3.99.99.*