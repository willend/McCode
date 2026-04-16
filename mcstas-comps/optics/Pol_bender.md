# The `Pol_bender` Component

*McStas: Polarising bender.*

## Identification

- **Site:** 
- **Author:** Peter Christiansen
- **Origin:** RISOE
- **Date:** August 2006

## Description

```text
Based on Guide_curved written by Ross Stewart.
Models a rectangular curved guide tube with entrance centered on the Z axis.
The entrance lies in the X-Y plane.  Draws a true depiction
of the guide with multiple slits (but without spacers), and trajectories.
It relies on similar physics as the Monochromator_pol.
The reflec function and parameters are passed to this component to
give a bigger freedom.
The up direction is hardcoded to be along the y-axis (0, 1, 0)

The guide is asummed to have half a spacer on each side:
slit1  slit2  slit3
|+     ++     ++     +|
|+     ++     ++     +|
<---------------------> xwidth
<------> xwidth/nslit (nslit=3)
<> d

The reflection functions and parameters defaults as follows:
Bot defaults to Top, Left defaults to Top, Right defaults to left.
Down defaults to down and up defaults to up for all functions and
Top(Up and Down) defaults to StdReflecFunc and {0.99,0.0219,6.07,2.0,0.003}
which stands for {R0, Qc, alpha, m, W}.

Example:
Pol_bender(xwidth = 0.08, yheight = 0.08, length = 1.0, radius= 10.0,
nslit=5, d=0.0, endFlat=0, drawOption=2,
rTopUpPar={0.99, 0.0219, 6.07, 3.0, 0.003},
rTopDownPar={0.99, 0.0219, 6.07, 1.0, 0.003})

See also the example instruments Test_Pol_Bender and
Test_Pol_Bender_Vs_Guide_Curved (under tests).

%BUGS
This component has been against tested Guide_curved and found to
give the same intensities. Gravity option has not been tested.

GRAVITY: YES (when gravity is along y-axis)
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| **xwidth** | m | Width at the guide entry |  |
| **yheight** | m | Height at the guide entry |  |
| **length** | m | length of guide along center |  |
| **radius** | m | Radius of curvature of the guide (+:curve left/-:right) |  |
| G | m/s^2 | Gravitational constant | 9.8 |
| nslit | 1 | Number of slits | 1 |
| d | m | Width of spacers (subdividing absorbing walls) | 0.0 |
| debug | 1 | if debug > 0 print out some internal parameters | 0 |
| endFlat | 1 | If endflat>0 then entrance and exit planes are parallel. | 0 |
| rTopUpPar | 1 | Top mirror Parameters for spin up standard reflectivity function | {0.99,0.0219,6.07,2.0,0.003} |
| rTopDownPar | 1 | Top mirror Parameters for spin down standard reflectivity function | {0.99,0.0219,6.07,2.0,0.003} |
| rBotUpPar | 1 | Bottom mirror Parameters for spin up standard reflectivity function | {0.99,0.0219,6.07,2.0,0.003} |
| rBotDownPar | 1 | Bottom mirror Parameters for spin down standard reflectivity function | {0.99,0.0219,6.07,2.0,0.003} |
| rLeftUpPar | 1 | Left mirror Parameters for spin up standard reflectivity function | {0.99,0.0219,6.07,2.0,0.003} |
| rLeftDownPar | 1 | Left mirror Parameters for spin down standard reflectivity function | {0.99,0.0219,6.07,2.0,0.003} |
| rRightUpPar | 1 | Right mirror Parameters for spin up standard reflectivity function | {0.99,0.0219,6.07,2.0,0.003} |
| rRightDownPar | 1 | Right mirror Parameters for spin down standard reflectivity function | {0.99,0.0219,6.07,2.0,0.003} |
| rTopUpData | 1 | Reflectivity file for top mirror, spin up | "" |
| rTopDownData | 1 | Reflectivity file for top mirror, spin down | "" |
| rBotUpData | 1 | Reflectivity file for bottom mirror, spin up | "" |
| rBotDownData | 1 | Reflectivity file for bottom mirror, spin down | "" |
| rLeftUpData | 1 | Reflectivity file for left mirror, spin up | "" |
| rLeftDownData | 1 | Reflectivity file for left mirror, spin down | "" |
| rRightUpData | 1 | Reflectivity file for right mirror, spin up | "" |
| rRightDownData | 1 | Reflectivity file for right mirror, spin down | "" |

## Links

- [Source code](/Users/peterwillendrup/Projects/willend-McCode/mcstas-comps/optics/Pol_bender.comp) for `Pol_bender.comp`.

---

*Generated on mcstas 3.99.99.*