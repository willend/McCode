# The `Shadow_input` Component

*McXtrace: Release: McXtrace 0.1

Read x-ray state parameters from SHADOW x-ray event file.*

## Identification

- **Site:** 
- **Author:** Andrea Prodi
- **Origin:** Risoe/ILL
- **Date:** November 21, 2011

## Description

```text
Source-like component reading x-ray state parameters from a
SHADOW x-ray event file. Used to interface McXtrace components or
simulations into SHADOW.

Example: Shadow_input(file="MySource.00", bufsize = 10000, repeat_count = 2)
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| file | string | Filename of x-ray file to read. Default (NULL) is standard input. Empty string "" unactivates component | "" |
| bufsize | records | Size of x-ray input buffer | 10000 |
| repeat_count | 1 | Number of times to repeat each x-ray read | 1 |

## Links

- [Source code](/Users/peterwillendrup/Projects/willend-McCode/mcxtrace-comps/misc/Shadow_input.comp) for `Shadow_input.comp`.

---

*Generated on mcxtrace 3.99.99.*