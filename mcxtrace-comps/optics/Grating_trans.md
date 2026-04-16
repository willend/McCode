# The `Grating_trans` Component

*McXtrace: Transmission grating*

## Identification

- **Site:** 
- **Author:** Erik B Knudsen (erkn@fysik.dtu.dk)
- **Origin:** DTU Physics
- **Date:** December 2016

## Description

```text
Model of a 1D rectangular transmission grating based on the theory developed in Schnopper et. al., Applied Optics, 1977.
The grating lines are assumed to be vertical. Within each period a fraction gamma is the "open" fraction.
(I.e. 1 is completely open). At present only absorption in the substrate (modelled by the thickness sdepth)
is included.

This  component is currently undergoing validation.

Example: Grating_trans(
xwidth=25e-3, yheight=25e-3, gamma=0.4, period=2000e-10, zdepth=5100e-10, max_order=3, material="Au.txt")
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| xwidth | m | Width of the grating. Defines how many lines there are in total. | 1e-3 |
| yheight | m | Height of the grating. | 1e-3 |
| period | m | Distance between grating grooves. | 1e-6 |
| gamma | 0-1 | Ratio between groove and period  aka duty cycle. 1 means fully open. | 0.5 |
| zdepth | m | Depth of grooves. | 1e-6 |
| sdepth | m | Thickness of substrate. The default is to have no substrate - i.e. rods. | 0 |
| material | str | Data file containing the material from which the grating is made. | "Au.txt" |
| substrate | str | Data file containing material data for the substrate. | "" |
| max_order | 1 | Maximum order to diffract | 2 |
| fixed_delta | 0/1 | Set delta to the given constant. Useful for debugging. | 0 |

## Links

- [Source code](/Users/peterwillendrup/Projects/willend-McCode/mcxtrace-comps/optics/Grating_trans.comp) for `Grating_trans.comp`.

---

*Generated on mcxtrace 3.99.99.*