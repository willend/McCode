# The `Collimator_radial` Component

*McStas: A radial Soller collimator.*

## Identification

- **Site:** 
- **Author:** Emmanuel Farhi <farhi@ill.fr>
- **Origin:** ILL
- **Date:** July 2005

## Description

```text
Radial Soller collimator with rectangular opening and specified length.
The collimator is made of many rectangular channels stacked radially.
Each channel is a set of transmitting layers (nslit), separated by an absorbing
material (infinitely thin), the whole stuff is inside an absorbing housing.

When specifying the number of channels (nchan), each channel has a total
entrance width=radius*fabs(theta_max-theta_min)/nchan, but only the central
portion 'xwidth' accepts neutrons. When xwidth=0, it is set to the full
apperture so that all neutrons enter the channels (all walls are infinitely thin).

When using zero as the number of channels (nchan), the collimator is continuous,
whithout shadowing effect.

The component should be positioned at the radius center.
The component can be made oscillating (usual on diffractometers and TOF
machines) with the 'roc' parameter.
The neutron beam outside the collimator angular area is transmitted unaffected.

When used as a focusing collimator, the focusing parameter should be set to 1.

An example of a instrument that uses this collimator can be found in the SALSA instrument,
in the example folder

Example:
Channelled radial collimator with shadow parts
Collimator_radial(xwidth=0.015, yheight=.3, length=.35, divergence=40,transmission=1, theta_min=5, theta_max=165, nchan=128, radius=0.9)
A continuous radial collimator
Collimator_radial(yheight=.3, length=.35, divergence=40,transmission=1, theta_min=5, theta_max=165, radius=0.9)
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| xwidth | m | Soller  window width, filled with nslit slits. Use 0 value for continuous collimator. | 0 |
| yheight | m | Collimator height. If  yheight_inner is specified, then this is the outer cylinders height | .3 |
| length | m | Length/Distance between inner and outer slits. | .35 |
| divergence | min of arc | Divergence angle. May also be specified with the nslit parameter. A zero value unactivates component. | 0 |
| transmission | 1 | Maximum transmission of Soller (0<=t<=1). | 1 |
| theta_min | deg | Minimum Theta angle for the radial setting. | 5 |
| theta_max | deg | Maximum Theta angle for the radial setting. | 165 |
| nchan | 1 | Number of Soller channels in the theta range. Use 0 value for continuous collimator. | 0 |
| radius | m | Radius of the collimator (to entry window). | 1.3 |
| nslit | 1 | Number of blades composing each Soller. Overrides the divergence parameter. | 0 |
| roc | deg | Amplitude of oscillation of collimator. 0=fixed. | 0 |
| verbose |  | Gives additional information. | 0 |
| approx |  | Use Soller triangular transmission approximation. | 0 |
| focusing | 1 | When set allows you to use the collimators for focusing, rather than dispersing. | 0 |
| yheight_inner | 1 | Defines the inner height of the collimator | 0 |

## Links

- [Source code](Collimator_radial.comp) for `Collimator_radial.comp`.

---

*Generated on mcstas 3.99.99.*