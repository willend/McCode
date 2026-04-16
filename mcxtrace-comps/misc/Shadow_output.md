# The `Shadow_output` Component

*McXtrace: Release: McXtrace 0.1

Write x-ray state parameters to SHADOW x-ray event file.*

## Identification

- **Site:** 
- **Author:** Andrea Prodi
- **Origin:** Risoe/ILL
- **Date:** November 21, 2011

## Description

```text
Detector-like component writing x-ray state parameters to a
SHADOW x-ray file. Used to interface McXtrace components or
simulations into SHADOW. Each photon is 104 bytes.

Note that when standard output is used, as is the default, no
monitors or other components that produce terminal output must be
used, or the x-ray output from this component will become
corrupted.

Example: Shadow_output(file="MySource.vit", bufsize = 10000, progress = 1)
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| file | string | Filename of x-ray file to write. Default is standard output | "" |
| bufsize | records | Size of x-ray output buffer | 1000 |
| progress | flag | If not zero, output dots as progress indicator | 0 |

## Links

- [Source code](/Users/peterwillendrup/Projects/willend-McCode/mcxtrace-comps/misc/Shadow_output.comp) for `Shadow_output.comp`.

---

*Generated on mcxtrace 3.99.99.*