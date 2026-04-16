# The `SNS_source_analytic` Component

*McStas: A source that produces a time and energy distribution from
parameterized SNS moderator files*

## Identification

- **Site:** 
- **Author:** F. X. Gallmeier
- **Origin:** SNS Oak Ridge National Laboratory
- **Date:** October 18, 2010

## Description

```text
Produces a time-of-flight spectrum from SNS moderator files
moderator files can be obtained from the author
<strong>IMPORTANT: The output units of this component are N/pulse</strong>
<strong>IMPORTANT: The component needs a FULL PATH to the source input file</strong>
Notes:
(1) the raw moderator files are per Sr.  The parameters focus_xw focus_yh and dist
provide the solid angle with which the beam line is served.
The best practice is to set focus_xw and focus_yh to the width and height of the
closest beam component, and dist as the distance from the moderator
location to this component.
(2) Be sure that Emin and Emax are within the limits of 1e-5 to 100 eV
(3) the proton pulse length T determines short- and long-pulse mode

Beamport definitions:
BL11: a1Gw2-11-f5_fit_fit.dat
BL14: a1Gw2-14-f5_fit_fit.dat
BL17: a1Gw2-17-f5_fit_fit.dat
BL02: a1Gw2-2-f5_fit_fit.dat
BL05: a1Gw2-5-f5_fit_fit.dat
BL08: a1Gw2-8-f5_fit_fit.dat
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| **filename** |  | Filename of source data |  |
| xwidth | m | width of moderator (default 0.1 m) | 0.10 |
| yheight | m | height of moderator (default 0.12 m) | 0.12 |
| **dist** | m | Distance from source to the focusing rectangle (no default) |  |
| **focus_xw** | m | Width of focusing rectangle (no default) |  |
| **focus_yh** | m | Height of focusing rectangle (no default) |  |
| Emin | meV | minimum energy of neutrons (default 0.01 meV) | 0.01 |
| Emax | meV | maximum energy of neutrons (default 1e5 meV) | 1.0e5 |
| tinmin | us | minimum time of neutrons (default 0 us) | 0.0 |
| tinmax | us | maximum time of neutrons (default 2000 us) | 2000.0 |
| sample_E |  | sample energy from:  (default 0) | 0 |
| sample_t |  | sample t from:  (default 0) | 0 |
| proton_T | us | proton pulse length  (0 us) | 0.0 |
| p_power | MW | proton power (default 2 MW) | 2.0 |
| n_pulses |  | number of pulses (default 1) | 1.0 |

## Links

- [Source code](/Users/peterwillendrup/Projects/willend-McCode/mcstas-comps/contrib/SNS_source_analytic.comp) for `SNS_source_analytic.comp`.

---

*Generated on mcstas 3.99.99.*