# The `GISANS_sample` Component

*McStas: Sample for GISANS*

## Identification

- **Site:** 
- **Author:** H. Frielinghaus
- **Origin:** FZJ
- **Date:** March 2023

## Description

```text
The idea of this sample goes back to the real sample studied in the publication https://doi.org/10.1063/1.4723634
This is a sandwich of a sapphire and silicon slab through which the neutrons impinge and the sample in between where the scattering emerges from.
The sample consist of spherical polystyrene colloids in heavy water that form aligned crystallites at the solid-liquid interface,
while in the middle of the volume the crytallites are orientationally averaged in the polar angle that points in the lateral direaction.
The crystallites of the current verision are not highly realistic because they are monoclinic with a 60° angle mimicking a fraction
of a hexagonal structure with hexagonal planes stacked in the z-direction.
Inside the routine one can change between 2 or 3 different planes. Also the total crystallite size can be changed.
Especially the parallelogram with 60° angle is unrealistic because one usually would assume the crystallites to have a hexagonal shape.
However, the finite crystallites mimic the final correlation length inside the sample.
The sample works for neutrons impingin from the sapphire, the silicon at grazing angles and in transmission in the sense of a SANS sample.
If the neutrons impinge through the other layers (sample and silicon oxide) - the responses are not so realistic and need further development.
Also multiple scattering would be needed to be implemented still - but could be done.

What this sample component covers relatively well is the fact that damping of the intensity by scattering and absorption is also covered.
That means that even at larger angles than the critical angle the intensity is damped inside the sample and so only a certain near surface
layer scatters neutrons.
This effect is not covered by BornAgain.

I see this as a start for further developments.

Information extracted from malformatted docstrings follow:

the total thickness of the sandwich is zsapph+zsamp+zsilicon
the thicknesses zsampsurf and zsiliconsurf are parts of the total sample/silicon thicknesses

(scattering length densitites, reciprocal total cross section of absorption, reciprocal total cross section of incoherent scattering)
units rho... [A-2], abslen... [cm], inclen... [cm]
rhosapph,       abslensapph,       inclensapph        for sapphire
rhoD2O,         abslenD2O,         inclenD2O          for D2O as solvent in sample
rhoPS,          abslenPS,          inclenPS           for polystyrene as colloids in sample
rhosiliconsurf, abslensiliconsurf, inclensiliconsurf  for silicon surface (oxide layer)
rhosilicon,     abslensilicon,     inclensilicon      for silicon
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| xwidth | m | Width of sample volume | 0.05 |
| yheight | m | Height of sample volume | 0.15 |
| zsapph | m | Thickness of the sapphire layer on one side | 0.02 |
| zsamp | m | Thickness of the overall sample between sapphire and silicon | 0.002 |
| zsampsurf | m | Thickness from the total of zsamp on either side of sapphire/silicon that is oriented | 0.000001 |
| zsilicon | m | Thickness of the silicon layer on the other side | 0.02 |
| zsiliconsurf | m | Thickness from the total of zsilicon on the sample side (oxidization layer) | 5e-9 |
| rhosapph |  |  | 5.773e-6 |
| abslensapph |  |  | 163.708 |
| inclensapph |  |  | 49.815 |
| rhoD2O |  |  | 6.364e-6 |
| abslenD2O |  |  | 44066.347 |
| inclenD2O |  |  | 7.258 |
| rhoPS |  |  | 1.358e-6 |
| abslenPS |  |  | 114.502 |
| inclenPS |  |  | 0.24588 |
| rhosiliconsurf |  |  | 4.123e-6 |
| abslensiliconsurf |  |  | 401.051 |
| inclensiliconsurf |  |  | 169.11 |
| rhosilicon |  |  | 2.079e-6 |
| abslensilicon |  |  | 209.919 |
| inclensilicon |  |  | 9901.6 |
| phiPS | 1 | Concentration vol/vol of colloids in D2O | 0.1 |
| Rad | A | Radius of colloids in Aangstroem | 370.0 |
| phirot | rad | angle of the ordered (aligned) crytallites at the two surfaces towards sapphire/silicon | 0.0 |
| sc_aim | 1 | how much is scattered versus transmitted | 0.98 |
| sans_aim | 1 | how much goes to the small angle range versus wide angles | 0.98 |

## Links

- [Source code](/Users/peterwillendrup/Projects/willend-McCode/mcstas-comps/contrib/GISANS_sample.comp) for `GISANS_sample.comp`.

---

*Generated on mcstas 3.99.99.*