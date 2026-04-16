# The `Source_adapt` Component

*McStas: Neutron source with adaptive importance sampling*

## Identification

- **Site:** 
- **Author:** Kristian Nielsen
- **Origin:** Risoe
- **Date:** 1999

## Description

```text
Rectangular source with flat energy or wavelength distribution that
uses adaptive importance sampling to improve simulation efficiency.
Works together with the Adapt_check component.

The source divides the three-dimensional phase space of (energy,
horizontal position, horizontal divergence) into a number of
rectangular bins. The probability for selecting neutrons from each
bin is adjusted so that neutrons that reach the Adapt_check
component with high weights are emitted more frequently than those
with low weights. The adjustment is made so as to attemt to make
the weights at the Adapt_check components equal.

Focusing is achieved by only emitting neutrons towards a rectangle
perpendicular to and placed at a certain distance along the Z axis.
Focusing is only approximate (for simplicity); neutrons are also
emitted to pass slightly above and below the focusing rectangle,
more so for wider focusing.

In order to prevent false learning, a parameter beta sets a
fraction of the neutrons that are emitted uniformly, without regard
to the adaptive distribution. The parameter alpha sets an initial
fraction of neutrons that are emitted with low weights; this is
done to prevent early neutrons with rare initial parameters but
high weight to ruin the statistics before the component adapts its
distribution to the problem at hand. Good general-purpose values
for these parameters are alpha = beta = 0.25.

%VALIDATION
This component is not validated. It does not work properly with MPI.
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| N_E | 1 | Number of bins in energy (or wavelength) dimension | 20 |
| N_xpos | 1 | Number of bins in horizontal position | 20 |
| N_xdiv | 1 | Number of bins in horizontal divergence | 20 |
| xmin | m | Left edge of rectangular source | 0 |
| xmax | m | Right edge | 0 |
| ymin | m | Lower edge | 0 |
| ymax | m | Upper edge | 0 |
| xwidth | m | Width of source | 0 |
| yheight | m | Height of source | 0 |
| filename | string | Optional filename for adaptive distribution output | 0 |
| dist | m | Distance to target rectangle along z axis | 0 |
| focus_xw | m | Width of target | 0.05 |
| focus_yh | m | Height of target | 0.1 |
| E0 | meV | Mean energy of neutrons | 0 |
| dE | meV | Energy spread (energy range is from E0-dE to E0+dE) | 0 |
| lambda0 | AA | Mean wavelength of neutrons (if energy not specified) | 0 |
| dlambda | AA | Wavelength spread half width | 0 |
| flux |  | (1/(cm 2 AA st)) Absolute source flux | 1e13 |
| target_index | 1 | relative index of component to focus at, e.g. next is +1 this is used to compute 'dist' automatically. | 1 |
| alpha | 1 | Learning cut-off factor (0 < alpha <= 1) | 0.25 |
| beta | 1 | Aggressiveness of adaptive algorithm (0 < beta <= 1) | 0.25 |

## Links

- [Source code](/Users/peterwillendrup/Projects/willend-McCode/mcstas-comps/sources/Source_adapt.comp) for `Source_adapt.comp`.

---

*Generated on mcstas 3.99.99.*