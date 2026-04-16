# The `FlatEllipse_finite_mirror` Component

*McStas: Date: 2022-2023

NMO (nested mirror optic) modules*

## Identification

- **Site:** 
- **Author:** Christoph Herb, TUM
- **Origin:** TUM
- **Date:** 2022-2023

## Description

```text
Simulates NMO (nested mirror optic) modules as concevied by B&ouml;ni et al., see
Christoph Herb et al., Nucl. Instrum. Meth. A 1040, 1671564 (1-18) 2022.

The component relies on an updated version of conic.h from MIT.
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| sourceDist | m | Distance used for calculating the spacing of the mirrors | 0 |
| LStart | m | Left focal point | 0.6 |
| LEnd | m | Right focal point | 0.6 |
| lStart | m | z-Value of the mirror start | 0.0 |
| lEnd | m | z-Value of the mirror end | 0.0 |
| r_0 | m | distance to the mirror at lStart | 0.02076 |
| nummirror | 1 | number of mirrors | 9 |
| mf |  | mvalue of the inner side of the coating, m>10 results in perfect reflections | 4 |
| mb |  | mvalue of the outer side of the coating, m>10 results in perfect reflections | 0 |
| R0 | 1 | Low-angle reflectivity | 0.99 |
| Qc | AA-1 | critical scattering vector | 0.021 |
| W | AA-1 | width of supermirror cutoff | 0.003 |
| alpha | AA | Slope of reflectivity | 6.07 |
| mirror_width | m | width of the individual mirrors | 0.003 |
| mirror_sidelength | m | side length of the individual mirrors | 1 |
| doubleReflections | 1 | binary value determining whether the mirror backside is reflective | 0 |
| rfront_inner_file | str | file of distances to the optical axis of the individual mirrors | "NULL" |

## Links

- [Source code](/Users/peterwillendrup/Projects/willend-McCode/mcstas-comps/contrib/FlatEllipse_finite_mirror.comp) for `FlatEllipse_finite_mirror.comp`.
- Christoph Herb et al., Nucl. Instrum. Meth. A 1040, 1671564 (1-18) 2022.

---

*Generated on mcstas 3.99.99.*