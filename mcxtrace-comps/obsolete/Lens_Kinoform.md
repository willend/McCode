# The `Lens_Kinoform` Component

*McXtrace: A model of a specific kinoform used by the BNL*

## Identification

- **Site:** 
- **Author:** Jana Baltser and Erik Knudsen
- **Origin:** NBI
- **Date:** January 2012

## Description

```text
KINOFORM. A model of a specific kinoform used by the BNL team during the APS beamtime.
z: [0 0.002033m]
xmin=-0.0002634
xmax=0.0002634
the principles of the kinoform's operation are described here: http://neutrons.ornl.gov/workshops/nni_05/presentations/min050616_xray_evans-lutterodt_ken_nni05.pdf

You may as well use a kinoform with:
Lens_parab_Cyl(r=.5e-3,yheight=1.3e-3,xwidth=1.3e-3,d=.1e-3,N=21,
material_datafile="Be.txt")
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| datafile |  |  | "kinoform.txt" |
| material_datafile |  |  | "Si.txt" |
| yheight | m | height of the lens. | 1e-2 |
| xwidth | m | width of the lens | 5.268e-4 |
| deltaN |  |  | 0 |

## Links

- [Source code](/Users/peterwillendrup/Projects/willend-McCode/mcxtrace-comps/obsolete/Lens_Kinoform.comp) for `Lens_Kinoform.comp`.

---

*Generated on mcxtrace 3.99.99.*