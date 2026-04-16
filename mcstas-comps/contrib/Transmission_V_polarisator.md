# The `Transmission_V_polarisator` Component

*McStas: Transmission V-polarisator including absorption by Fe in the supermirror. Experimentally benchmarked.*

## Identification

- **Site:** 
- **Author:** Andreas Ostermann (additions from Michael Schneider, SNAG)
- **Origin:** TUM
- **Date:** 2024

## Description

```text
Transmission V-polarisator including absorption by Fe in the supermirror.

Example: Transmission_V_polarisator(w1=0.050, h1=0.050,
w2=0.050, h2=0.050, l=2.700,
waferD=0.0003, FeD=2.16e-06,
Si_i=0.2, Si_a=0.215,
R0=0.99, Qc=0.02174, alpha=4.25, W=0.001,
mleft=1.2, mright=1.2, mtop=1.2, mbottom=1.2,
reflectUP="measured_up_q.dat",reflectDW="measured_dw_q.dat")
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| reflectUP | str | Reflectivity profile of the FeSi-wafer for spin-up neutrons; columns [q,R] | 0 |
| reflectDW | str | Reflectivity profile of the FeSi-wafer for spin-down neutrons; columns [q,R] | 0 |
| **w1** | m | Width at the polarizer entry |  |
| **h1** | m | Height at the polarizer entry |  |
| **w2** | m | Width at the polarizer exit |  |
| **h2** | m | Height at the polarizer exit |  |
| **l** | m | length of polarizer |  |
| **waferD** | m | Thickness of Si wafer |  |
| **Si_i** | barns | Scattering cross section per atom (barns) |  |
| **Si_a** | barns | Absorption cross section per atom (barns) at 2200m/s |  |
| **FeD** | m | Thickness of Fe in supermirror, Ti is neglected |  |
| R0 | 1 | Low-angle reflectivity of the outer guide | 0.99 |
| Qc | AA-1 | Critical scattering vector of the outer guide | 0.02174 |
| alpha | AA | Slope of reflectivity of the outer guide | 4.25 |
| W | AA-1 | Width of supermirror cut-off of the outer guide | 0.001 |
| mleft | 1 | m-value of material for left.   vert. mirror of the outer guide | -1 |
| mright | 1 | m-value of material for right.  vert. mirror of the outer guide | -1 |
| mtop | 1 | m-value of material for top.    horz. mirror of the outer guide | -1 |
| mbottom | 1 | m-value of material for bottom. horz. mirror of the outer guide | -1 |

## Links

- [Source code](/Users/peterwillendrup/Projects/willend-McCode/mcstas-comps/contrib/Transmission_V_polarisator.comp) for `Transmission_V_polarisator.comp`.
- P. B&ouml;ni, W. M&uuml;nzer and A. Ostermann: <a href="https://doi.org/10.1016/j.physb.2009.06.031">Physica B: Condensed Matter Volume 404, Issue 17, 1 September 2009, Pages 2620-2623</a>

---

*Generated on mcstas 3.99.99.*