# The `Multilayer_Sample` Component

*McStas: Multilayer Reflecting sample using matrix Formula, v2 with 'nrepeats' for repeating multilayer structure.*

## Identification

- **Site:** 
- **Author:** Robert Dalgliesh
- **Origin:** ISIS
- **Date:** June 2010

## Description

```text
in order to get this to compile you need to link against
the gsl and gslcblas libraries.

to do this automatically edit
/usr/local/lib/mcstas/tools/perl/mcstas_config.perl

add -lgsl and -lgslcblas to the CFLAGS line

Horizontal reflecting substrate defined by SLDs,Thicknesses, roughnesses
The superphase may also be determined

Example: Multilayer_Sample(xmin=-0.1, xmax=0.1,zmin=-0.1, zmax=0.1, nlayer=1,sldPar={0.0,2.0e-6,0.0e-6},dPar={20.0}, sigmaPar={5.0,5.0})

Example: d1 500: sld1 (air) 0.0: sld2 (Si) 2.07e-6: sldf1(film Ni) 9.1e-6
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| xwidth | m | Width of substrate | 0.2 |
| zlength | m | Length of substrate | 0.2 |
| nlayer | 1 | Number of film layers | 1 |
| nrepeats | 1 | Number of repeats of the block of layers appart from the superphase and substrate | 1 |
| sldPar | AA^-2 | Scattering length Density's of layers | {0.0,2.0e-6,0.0e-6} |
| dPar | AA | Thicknesses of film layers | {20.0} |
| sigmaPar | AA | r.m.s roughnesses of the interfaces | {5.0,5.0} |
| frac_inc | 1 | Fraction of statistics to assign to incoherent scattering | 0 |
| ythick | m | Thickness of substrate | 0 |
| mu_inc | m^-1 | Incoherent scattering length | 5.62 |
| target_index | 1 | Used in combination with focus_xw and focus_yh to indicate solid angle for incoherent scattering. | 0 |
| focus_xw | m | Used in combination with target_index and focus_yh to indicate solid angle for incoherent scattering. | 0 |

## Links

- [Source code](Multilayer_Sample.comp) for `Multilayer_Sample.comp`.

---

*Generated on mcstas 3.99.99.*