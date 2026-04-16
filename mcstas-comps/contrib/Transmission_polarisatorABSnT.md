# The `Transmission_polarisatorABSnT` Component

*McStas: Transmission V-polarisator including absorption by Fe in the supermirror.*

## Identification

- **Site:** 
- **Author:** Andreas Ostermann
- **Origin:** TUM
- **Date:** 2004

## Description

```text
Transmission V-polarisator including absorption by Fe in the supermirror.

Example: Gravity_guide(w1=0.1, h1=0.1, w2=0.1, h2=0.1, l=12,
R0=0.99, Qc=0.021, alpha=6.07, m=1.0, W=0.003, k=1, d=0.0005)
Example: Transmission_polarisatorABSnT(w1=0.050, h1=0.050,
w2=0.050, h2=0.050, l=2.700,
waferD=0.0003, FeD=2.16e-06,
Si_i=0.2, Si_a=0.215,
R0=0.99, Qc=0.02174, alpha=4.25, W=0.001,
mleft=1.2, mright=1.2, mtop=1.2, mbottom=1.2,
R0_up=0.99, Qc_up=0.014, alpha_up=2.25, W_up=0.0025, mup=1.0,
R0_down=0.99, Qc_down=0.02174, alpha_down=3.8, W_down=0.00235, mdown=2.5)
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| **w1** | m | Width at the polarizer entry |  |
| **h1** | m | Height at the polarizer entry |  |
| **w2** | m | Width at the polarizer exit |  |
| **h2** | m | Height at the polarizer exit |  |
| **l** | m | length of polarizer |  |
| **waferD** | m | Thickness of Si wafer |  |
| **Si_i** | barns | Scattering cross section per atom (barns) |  |
| **Si_a** | barns | Absorption cross section per atom (barns) at 2200m/s |  |
| **FeD** | m | Thickness of Fe wafer |  |
| R0 | 1 | Low-angle reflectivity of the outer guide | 0.99 |
| Qc | AA-1 | Critical scattering vector of the outer guide | 0.02174 |
| alpha | AA | Slope of reflectivity of the outer guide | 4.25 |
| W | AA-1 | Width of supermirror cut-off of the outer guide | 0.001 |
| R0_up | 1 | Low-angle reflectivity of the Fe/Si-wafer for spin up neutrons | 0.99 |
| Qc_up | AA-1 | Critical scattering vector of the Fe/Si-wafer for spin up neutrons | 0.0109 |
| alpha_up | AA | Slope of reflectivity of the Fe/Si-wafer for spin up neutrons | 4.25 |
| W_up | AA-1 | Width of supermirror cut-off of the Fe/Si-wafer for spin up neutrons | 0.0025 |
| R0_down | 1 | Low-angle reflectivity of the Fe/Si-wafer for spin down neutrons | 0.99 |
| Qc_down | AA-1 | Critical scattering vector of the Fe/Si-wafer for spin down neutrons | 0.02174 |
| alpha_down | AA | Slope of reflectivity of the Fe/Si-wafer for spin down neutrons | 6.25 |
| W_down | AA-1 | Width of supermirror cut-off of the Fe/Si-wafer for spin down neutrons | 0.001 |
| mleft | 1 | m-value of material for left.   vert. mirror of the outer guide | -1 |
| mright | 1 | m-value of material for right.  vert. mirror of the outer guide | -1 |
| mtop | 1 | m-value of material for top.    horz. mirror of the outer guide | -1 |
| mbottom | 1 | m-value of material for bottom. horz. mirror of the outer guide | -1 |
| mup | 1 | m-value of the Fe/Si-wafer for spin up neutrons | -1 |
| mdown | 1 | m-value of the Fe/Si-wafer for spin down neutrons | -1 |

## Links

- [Source code](/Users/peterwillendrup/Projects/willend-McCode/mcstas-comps/contrib/Transmission_polarisatorABSnT.comp) for `Transmission_polarisatorABSnT.comp`.

---

*Generated on mcstas 3.99.99.*