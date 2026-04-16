# The `Attenuating_mask` Component

*McXtrace: Attenuating_mask*

## Identification

- **Site:** 
- **Author:** Matteo Busi, Erik B Knudsen
- **Origin:** DTU Physics
- **Date:** November 2017

## Description

```text
This component models a mask of energy dependent attenuation. This consists of a rectangular grid of size
"xwidth*yheight", composed of multiple disks of finite thickness "zdepth" of an attenuating material "att_file",
width "blocks_width" and period "blocks_dist"(i.e. distance between the center of each disk).
If holed_mask mode is turned the model of the component is the opposite, i.e. the mask is composed of an
attenuating slab of finite thickness and of size "xwidth*yheight", with apertures of desired width and period.
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| att_file | ".txt" | File that contains the object information. (Default: "W.txt") | "W.txt" |
| xwidth | m | Horizontal width of the mask. (Default: 1e-1) | 1e-1 |
| yheight | m | Vertical height of the mask. (Default: 1e-1) | 1e-1 |
| zdepth | m | Thickness of the absorbing mask. (Default: 3e-3) | 10e-6 |
| blocks_xwidth | m | Width of the absorbing blocks in the x-direction. (Default: 3e-3) | 1e-3 |
| blocks_xdist | m | Distance between absorbing blocks in the x-direction. (Default: 10e-3) | 2.5e-3 |
| blocks_yheight | m | Height of the absorbing blocks in the y-direction. (Default: 3e-3) | 1e-3 |
| blocks_ydist | m | Distance between absorbing blocks in the y-direction. (Default: 10e-3) | 2.5e-2 |
| holed_mask | 1 | Set to 1 if the mask is a holed grid. (Default: 0) | 0 |

## Links

- [Source code](/Users/peterwillendrup/Projects/willend-McCode/mcxtrace-comps/contrib/Attenuating_mask.comp) for `Attenuating_mask.comp`.

---

*Generated on mcxtrace 3.99.99.*