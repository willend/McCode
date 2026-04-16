# The `Filter_graphite` Component

*McStas: Pyrolytic graphite filter (analytical model)*

## Identification

- **Site:** 
- **Author:** <a href="mailto:hansen@ill.fr">Thomas C Hansen</a>
- **Origin:** <a href="http://www.ill.fr">ILL</a>
- **Date:** 07 March 2000

## Description

```text
ESCRIPTION

This rectangular pyrolytic graphite filter uses an analytical model
with linear interpolation on the neutron wavelength
This type of filter is e.g. used to supress higher harmonics, such as
the 1.2 AA contribution to the 2.4 AA obtained by a highly oriented
pyrolytic graphite (HOPG) monochromator.

Example: Filter_graphite(xmin=-.05, xmax=.05, ymin=-.05, ymax=.05, length=1.0)
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| xmin | m | Lower x bound | -0.16 |
| xmax | m | Upper x bound | 0.16 |
| ymin | m | Lower y bound | -0.16 |
| ymax | m | Upper y bound | 0.16 |
| length | m | Thickness of graphite plate | 0.05 |
| xwidth | m | Width of filter. Overrides xmin,xmax. | 0 |
| yheight | m | Height of filter. Overrides ymin,ymax. | 0 |

## Links

- [Source code](/Users/peterwillendrup/Projects/willend-McCode/mcstas-comps/contrib/Filter_graphite.comp) for `Filter_graphite.comp`.

---

*Generated on mcstas 3.99.99.*