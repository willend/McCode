# The `Abs_objects` Component

*McXtrace: Release: McXtrace 1.1

Blocks of attenuating material in off format*

## Identification

- **Site:** 
- **Author:** Erik Knudsen
- **Origin:** DTU Physics
- **Date:** Jan 24, 2011

## Description

```text
This component is a model of 1 or more off-shaped blocks attenuating the x-ray beam.
Which shapes are present and their relative positions are described in a file of the follwing format:
#objects
Material-filename  OFF-filename x y z xwidth yheight zdepth
...

An example is;
2
Be.txt  cube.off  0 0.01 0    0 0 0
Rh.txt  chess.off 0 -0.01 0   0 0 0

A xwidth etc of zero means use whatever dimensions are in the off/ply file.
If xwidth (or yheight or zdepth) is nonzero, the component scales the object
to fill that dimension. The xyz coordinates indicate the object shift.

Example: Abs_objects(objects="input_abs_objects_template.dat")
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| refraction | str | Flag to enable refraction at interfaces. | 1 |
| objects | str | Input file where the off-shapes are defined. | "input_abs_objects_template.dat" |

## Links

- [Source code](/Users/peterwillendrup/Projects/willend-McCode/mcxtrace-comps/samples/Abs_objects.comp) for `Abs_objects.comp`.

---

*Generated on mcxtrace 3.99.99.*