# The `Union_make_material` Component

*McStas: Component that takes a number of Union processes and constructs a Union material*

## Identification

- **Site:** 
- **Author:** Mads Bertelsen
- **Origin:** University of Copenhagen
- **Date:** 20.08.15

## Description

```text
Part of the Union components, a set of components that work together and thus
sperates geometry and physics within McStas.
The use of this component requires other components to be used.

1) One specifies a number of processes using process components
2) These are gathered into material definitions using this component
3) Geometries are placed using Union_box/cylinder/sphere, assigned a material
4) A Union_master component placed after all of the above

Only in step 4 will any simulation happen, and per default all geometries
defined before the master, but after the previous will be simulated here.

There is a dedicated manual available for the Union_components

Algorithm:
Described elsewhere
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| process_string | string | Comma seperated names of physical processes | "NULL" |
| **my_absorption** | 1/m | Inverse penetration depth from absorption at standard energy |  |
| absorber | 0/1 | Control parameter, if set to 1 the material will have no scattering processes | 0 |
| refraction_density | g/cm3 | Density of the refracting material. density < 0 means the material is outside/before the shape. | 0 |
| refraction_sigma_coh | barn | Coherent cross section of refracting material. Use negative value to indicate a negative coherent scattering length | 0 |
| refraction_weight | g/mol | Molar mass of the refracting material | 0 |
| refraction_SLD | AA^-2 | Scattering length density of material (overwrites sigma_coh, density and weight) | -1500 |
| init | string | Name of Union_init component (typically "init", default) | "init" |

## Links

- [Source code](Union_make_material.comp) for `Union_make_material.comp`.

---

*Generated on mcstas 3.99.99.*