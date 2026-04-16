# The `Lens_CRL_RTM` Component

*McXtrace: 1D CRL stack based on RTM formalism*

## Identification

- **Site:** 
- **Author:** Erik Knudsen
- **Origin:** DTU Physics
- **Date:** Jan '21

## Description

```text
A CRL stack component based on the formalism presented by Simons et.al. J. Synch. Rad.
2017, vol. 24.
We model a 1D lens stack focusing in the y-direction. I.e. invariant along x.

Example: Lens_CRL_RTM(
r=0.5e-3, N=10, fast=1, yheight=0, d=0.1e-3,xwidth=1e-4, zdepth=4e-4)
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| r | m | Radius of curavature at the lens apex. | 0.5e-3 |
| d | m | Thickness of a single lens | 0.1e-3 |
| material | str | Datafile containing f1 constants | "Be.txt" |
| N | m | Number of lenslets in the stack. | 1 |
| zdepth | m | Thickness of a single lenslet. | 2e-3 |
| yheight | m | Height of lens opening. If zero this is set by the lens thickness. | 1e-3 |
| xwidth | m | Width of the lenslets. | 1.2e-3 |
| fast | m | Use fast calculation - should be off for better display with mxdisplay | 1 |

## Links

- [Source code](/Users/peterwillendrup/Projects/willend-McCode/mcxtrace-comps/optics/Lens_CRL_RTM.comp) for `Lens_CRL_RTM.comp`.

---

*Generated on mcxtrace 3.99.99.*