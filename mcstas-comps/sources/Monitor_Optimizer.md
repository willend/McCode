# The `Monitor_Optimizer` Component

*McStas: To be used after the <b>Source_Optimizer</b> component*

## Identification

- **Site:** 
- **Author:** <a href="mailto:farhi@ill.fr">Emmanuel Farhi</a>
- **Origin:** <a href="http://www.ill.fr">ILL (France)</a>
- **Date:** 17 Sept 1999

## Description

```text
A component that optimizes the neutron flux passing through the
<b>Source_Optimizer</b> in order to have the maximum flux at the
Monitor_Optimizer position(s).
<b>Source_optimizer</b> should be placed just after the source.
Monitor_Optimizer should be placed at the position to optimize.
I prefer to put one just before the sample.

See <a href="Source_Optimizer.html">Source_Optimizer</a> for
usage example and additional informations.
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| **optim_comp** | str | name of the Source_Optimizer component in the instrument definition. Do not use quotes (no quotes) |  |
| xmin | m | Lower x bound of monitor opening | -0.1 |
| xmax | m | Upper x bound of monitor opening | 0.1 |
| ymin | m | Lower y bound of monitor opening | -0.1 |
| ymax | m | Upper y bound of monitor opening | 0.1 |
| xwidth | m | Width of monitor. Overrides xmin,xmax. | 0 |
| yheight | m | Height of monitor. Overrides ymin,ymax. | 0 |

## Links

- [Source code](/Users/peterwillendrup/Projects/willend-McCode/mcstas-comps/sources/Monitor_Optimizer.comp) for `Monitor_Optimizer.comp`.
- <a href="Source_Optimizer.html">Source_Optimizer</a>

---

*Generated on mcstas 3.99.99.*