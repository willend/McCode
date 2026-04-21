# The `IncoherentPhonon_process` Component

*McStas: A component to simulate inelastic scattering in the incoherent approximation
Takes into account one, two, and three phonon scattering explicitly,
and multi-phonon scattering (with n>4) via the saddle point method*

## Identification

- **Site:** 
- **Author:** Victor Laliena
- **Origin:** University of Zaragoza
- **Date:** 06.11.2018

## Description

```text
Part of the Union components, a set of components that work together and thus
expects geometry and physics within McStas.
The use of this component requires other components to be used.

1) One specifies a number of processes using process components like this one
2) These are gathered into material definitions using Union_make_material
3) Geometries are placed using Union_box / Union_cylinder, assigned a material
4) A Union_master component placed after all of the above


Algorithm:
Described elsewhere, see e.g. <a href="https://doi.org/10.3233/JNR-190117">https://doi.org/10.3233/JNR-190117</a>
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| T | K | Temperature | 394 |
| density | g/cm3 | Material density | 6.0 |
| M | amu | ion mass | 50.94 |
| sigmaCoh | barns | Coherent scattering cross section | 0.0184 |
| sigmaInc | barns | Incoherent scattering cross section | 5.08 |
| DOSfn | string | Path to the file that contains the DoS | NULL |
| nphe_exact | 1 | Number of terms in the phonon expansion taken exact. Has to be between 1 and 3. | 1 |
| nphe_approx | 1 | Number of terms in the phonon expansion taken approximate. | 0 |
| approx | 1 | Approximation type: 0 gaussian, 1 saddle point | 0 |
| mph_resum | 0/1 | Resumate the remaining terms of the phonon expansion via a saddle point: 0 No, 1 Yes | 0 |
| nxs | 1 | Number of energy points at which the total cross sections are precomputed | 1000 |
| kabsmin | A^-1 | Lower cut-off for the neutron wave-vector k | 0.1 |
| kabsmax | A^-1 | Higher cut-off for the neutron wave-vector k | 25 |
| interact_fraction | 1 | How large a part of the scattering events should use this process 0-1 (sum of all processes in material = 1) | -1 |
| init | string | Name of Union_init component (typically "init", default) | "init" |

## Links

- [Source code](IncoherentPhonon_process.comp) for `IncoherentPhonon_process.comp`.
- See <a href="https://doi.org/10.3233/JNR-190117">https://doi.org/10.3233/JNR-190117</a>

---

*Generated on mcstas 3.99.99.*