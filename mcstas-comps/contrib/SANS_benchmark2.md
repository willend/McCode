# The `SANS_benchmark2` Component

*McStas: SANS_benchmark2 sample from FZ J&uuml;lichx*

## Identification

- **Site:** 
- **Author:** Henrich Frielinghaus
- **Origin:** FZJ
- **Date:** Apr 2013

## Description

```text
Several benchmark SANS samples are defined in this routine. The first ones are analytically defined. Higher numbers are forseen for tables.
In principle, the exact definitions can be changed freely - inside this code.
The consideration of all parameters as a routine parameter would be too much for the general purpose.
The user might decide to make single parameters routine parameters.

For the scattering simulation a high fraction of neutron paths is directed to the scattering (exact fraction is sc_aim).
The remaining paths are used for the transmitted beams. The absolute intensities are treated accordingly, and the p-parameter is set accordingly.

For the scattering probability, the integral of the scattering function between Q = 0.0001 and 1.0 AA-1 is calculated.
This is used in terms of transmisson, and of course for the scattering probability.
In this way, multiple scattering processes could be treated as well.

The typical SANS range was considered to be between 0.0001 and 1.0 AA-1.
This means that the scattered neutrons are equally distributed in this range on logarithmic Q-scales.
The Q-parameters can be changed still inside the code, if needed.

Example: SANS_benchmark(xwidth=0.01, yheight=0.01, zthick=0.001, model=1.0, dsdw_inc=0.02, sc_aim=0.97, sans_aim=0.95, singlesp = 0.0)
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| xwidth | m | width of sample volume | 0.01 |
| yheight | m | height of sample volume | 0.01 |
| zthick | m | thickness of sample volume | 0.001 |
| model |  | model no., real variable will be rounded. negative numbers interpreted as model #0, too large as #18. | 1.0 |
| dsdw_inc |  | the incoherent background from the overall sample (cm-1), should read ca. 1.0 for water, 0.5 for half D2O, half H2O, and ca. 0.02 for D2O | 0.02 |
| sc_aim |  | the fraction of neutron paths used to represent the scattered neutrons (including everything: incoherent and coherent). rest is transmission. | 0.97 |
| sans_aim |  | the fraction of neutron paths used to represent the scattered neutrons in the sans-range (up to 1.0AA-1). rest is incoherent with Q>1AA-1. | 0.95 |
| singlesp |  | switches between multiple scattering (parameter zero 0.0) and single scattering (parameter 1.0). The sc_aim directs a fraction of paths to the first scattering process accordingly. The no. of paths for the second scattering process is derived from the real probability. Up to 10 scattering processes are considered. | 0.0 |

## Links

- [Source code](/Users/peterwillendrup/Projects/willend-McCode/mcstas-comps/contrib/SANS_benchmark2.comp) for `SANS_benchmark2.comp`.

---

*Generated on mcstas 3.99.99.*