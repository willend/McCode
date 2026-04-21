# The `NCrystal_sample` Component

*McStas: McStas sample component for the NCrystal library for thermal neutron transport
(<a href="https://github.com/mctools/ncrystal">www</a>).*

## Identification

- **Site:** 
- **Author:** NCrystal developers
- **Origin:** NCrystal Developers (European Spallation Source ERIC and DTU Nutech)
- **Date:** 2015

## Description

```text
McStas sample component using the NCrystal library for thermal neutron
transport in a single bulk material filling a single simple convex volume
(box, sphere or cylinder).

The geometrical layout of the volume is determined via the xwidth, yheight,
zdepth, and radius parameters, and the material being modelled is determined
via an NCrystal configuration string ("cfg-string").

For more information about NCrystal and cfg-strings, refer to the <a href="https://github.com/mctools/ncrystal/wiki">NCrystal wiki</a>.
In particular, browse the available datafiles at <a href="https://github.com/mctools/ncrystal/wiki/Data-library">Data-library</a> and read about the
format of the cfg-string expected in the "cfg" parameter at <a href="https://github.com/mctools/ncrystal/wiki/Using-NCrystal">Using-NCrystal</a>.

For more complicated geometries, it might be desirable to use NCrystal via the
McStas Union components instead.

Note that the physics backend of this component will be whichever NCrystal
installation is available and associated with the "ncrystal-config" command.
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| cfg | str | NCrystal material configuration string (details <a href="https://github.com/mctools/ncrystal/wiki/Using-NCrystal">on this page</a>). | "void" |
| xwidth | m | x-dimension (width) of sample, if box shape is desired | 0 |
| yheight | m | y-dimension (height) of sample, if box or cylinder shape is desired | 0 |
| zdepth | m | z-dimension (depth) of sample, if box shape is desired | 0 |
| radius | m | radius of sample, if sphere or cylinder shape is desired | 0 |
| absorptionmode | 0\|1\|2 | 0 : disable absorption. 1 : enable absorption via intensity reduction. 2 : enable absorption by terminating the tracking. | 1 |
| multscat | 0\|1 | 0 : disable multiple scattering. 1 : enable multiple scattering | 1 |

## Links

- [Source code](NCrystal_sample.comp) for `NCrystal_sample.comp`.
- The NCrystal wiki at <a href="https://github.com/mctools/ncrystal/wiki">https://github.com/mctools/ncrystal/wiki</a>.

---

*Generated on mcstas 3.99.99.*