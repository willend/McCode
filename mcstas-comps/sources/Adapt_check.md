# The `Adapt_check` Component

*McStas: Optimization specifier for the Source_adapt component.*

## Identification

- **Site:** 
- **Author:** Kristian Nielsen
- **Origin:** Risoe
- **Date:** 1999

## Description

```text
This components works together with the Source_adapt component, and
is used to define the criteria for selecting which neutrons are
considered "good" in the adaptive algorithm. The name of the
associated Source_adapt component in the instrument definition is
given as parameter. The component is special in that its position
does not matter; all neutrons that have not been absorbed prior to
the component are considered "good".

Example: Adapt_check(source_comp="MySource")
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| **source_comp** | string | The name of the Source_adapt component in the instrument definition. |  |

## Links

- [Source code](Adapt_check.comp) for `Adapt_check.comp`.

---

*Generated on mcstas 3.99.99.*