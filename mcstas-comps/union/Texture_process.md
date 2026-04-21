# The `Texture_process` Component

*McStas: Component for simulating textured powder in Union components*

## Identification

- **Site:** 
- **Author:** Victor Laliena
- **Origin:** University of Zaragoza
- **Date:** 2018-2019

## Description

```text
Part of the Union components, a set of components that work together and thus
seperates geometry and physics within McStas.
The use of this component requires other components to be used.

This component deals with the coherent elastic scattering on a textured material.
The texture is described through the coefficients of the generalized Fourier transform
of the Orientation Distribution Function (ODF).
The component expects as input two files, one containing the Fourier coefficients of the
ODF and another one with crystallographic and physical information.


Algorithm:
Described elsewhere, see e.g. <a href="https://doi.org/10.3233/JNR-190117">https://doi.org/10.3233/JNR-190117</a>
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| crystal_fn | s | Path to a file (.laz) containing crystallographic and physical information | 0 |
| fcoef_fn | s | Path to a text file containing the Fourier coefficients of the ODF. It must have five columns: l m n Real(Clmn) Imag(Clmn) | 0 |
| lmax_user | 1 | Cut-off for the Fourier series. If negative, the program uses all the coefficients provided in the file fcoef_fn | -1 |
| barns | 1 | Flag to indicate if \|F\|^2 from 'crystal_fn' is in barns or fm^2. barns=1 for laz and isotropic constant elastic scattering (reflections=NULL), barns=0 for lau type files | 0 |
| order | 1 | Limit scattering to this order | 0 |
| interact_fraction | 1 | How large a part of the scattering events should use this process 0-1 (sum of all processes in material = 1) | -1 |
| packing_factor | 1 | How dense is the material compared to optimal 0-1 | 1 |
| maxNeutronSaved | 1 | Maximum number of neutron cross sections saved for reusing | 1 |
| init | string | Name of Union_init component (typically "init", default) | "init" |

## Links

- [Source code](Texture_process.comp) for `Texture_process.comp`.
- See <a href="https://doi.org/10.3233/JNR-190117">https://doi.org/10.3233/JNR-190117</a>

---

*Generated on mcstas 3.99.99.*