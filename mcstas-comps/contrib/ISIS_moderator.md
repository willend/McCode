# The `ISIS_moderator` Component

*McStas: ISIS Moderators*

## Identification

- **Site:** 
- **Author:** S. Ansell and D. Champion
- **Origin:** ISIS
- **Date:** AUGUST 2005

## Description

```text
Produces a TS1 or TS2 ISIS moderator distribution.  The Face argument determines which moderator
is to be sampled. Each face uses a different Etable file (the location of which is determined by
the MCTABLES environment variable).  Neutrons are created having a range of energies
determined by the Emin and Emax arguments.  Trajectories are produced such that they pass
through the moderator face (defined by modXsixe and yheight) and a focusing rectangle
(defined by xh,focus_yh and dist).  Please download the documentation for precise instructions for use.

Example:   ISIS_moderator(Face ="water", Emin = 49.0,Emax = 51.0, dist = 1.0, focus_xw = 0.01,
focus_yh = 0.01, xwidth = 0.074, yheight = 0.074, CAngle = 0.0,SAC= 1)
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| Face | word | Name of the face - TS2=groove,hydrogen,narrow,broad - | "hydrogen" |
| Emin | meV | Lower edge of energy distribution | 49.0 |
| Emax | meV | Upper edge of energy distribution | 51.0 |
| dist | m | Distance from source to the focusing rectangle | 1.0 |
| focus_xw | m | Width of focusing rectangle | 0.01 |
| focus_yh | m | Height of focusing rectangle | 0.01 |
| xwidth | m | Moderator vertical size | 0.074 |
| yheight | m | Moderator Horizontal size | 0.074 |
| CAngle | radians | Angle from the centre line | 0.0 |
| SAC | boolean | Apply solid angle correction or not (1/0) | 1 |
| Lmin | meV | Lower edge of wavelength distribution | 0 |
| Lmax | meV | Upper edge of wavelength distribution | 0 |
| target_index | 1 | relative index of component to focus at, e.g. next is +1 | 1 |
| verbose | boolean | Echo status information at everu 1e5'th neutron | 0 |

## Links

- [Source code](ISIS_moderator.comp) for `ISIS_moderator.comp`.
- Further <A HREF="http://www.isis.rl.ac.uk/Computing/Software/MC/index.htm">information</A> should be
- downloaded from the ISIS MC website.
- *******************************************************************************/

---

*Generated on mcstas 3.99.99.*