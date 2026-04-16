# The `File` Component

*McStas: File.comp - allows to generate instrument/component input-files
from METADATA blocks*

## Identification

- **Site:** 
- **Author:** Greg Tucker
- **Origin:** ESS
- **Date:** 2024

## Description

```text
File.comp - allows to generate instrument/component input-files
from METADATA blocks - see test_File.instr for an example.
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| filename | string | Filename for output-file generated from metadata block | 0 |
| **metadatakey** | string | METADATA-key for looking up file content (may belong to File instance or another comp) |  |
| keep | 1 | Flag to indicate if file should be kept post-simulation | 0 |

## Links

- [Source code](/Users/peterwillendrup/Projects/willend-McCode/mcstas-comps/misc/File.comp) for `File.comp`.

---

*Generated on mcstas 3.99.99.*