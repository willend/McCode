# The `Source_lab` Component

*McXtrace: Laboratory x-ray source.*

## Identification

- **Site:** 
- **Author:** Erik Bergbaeck Knudsen
- **Origin:** Kgs. Lyngby
- **Date:** May 2012

## Description

```text
Model of a laboratory x-ray tube, generating x-rays by bombarding a target by electrons.
Given a input energy E0 of the electron beam, x-rays are emitted from the accessible emission lines
The geometry of the tube is assumed to be:
# The electron beam hits a slab of surface material surface at a right angle illuminating an area of width by height,
# where width is measured along the component X-axis.
# The centre of the electron beam at the anode surface is the origin of the component.
# The Z-axis of the component points at the centre of the exit window (focus_xw by focus yh)
placed at a distance dist from the origin.
# The angle between the Z-axis and the anode surface is the take_off angle.
For a detailed sketch of the geometry see the componnent manual.

The Bremsstrahlung emitted is modelled using the model of Kramer (1923) as restated in International
Tables of Crystallography C 4.1
Characteristic radiation is modelled by Lorentzian (default) or Gaussian energy profiles with
line-energies from Bearden (1967), widths from Krause (1979) and intensity from Honkimäki (1990) and x-ray data booklet.
Absoprtion of emitted x-rays while travelling through the target anode is included.

Example: Source_lab(material_datafile="Cu.txt",Emin=1, E0=80)
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| material_datafile | string | Name of datafile which describes the target material. | "Cu.txt" |
| width | m | Width of electron beam impinging on the anode. | 1e-3 |
| height | m | Height of electron beam impinging on the anode. | 1e-3 |
| thickness | m | Thickness of the anode material slab. | 100e-6 |
| E0 | kV | Acceleration voltage of xray tube. | 20 |
| Emax | keV | Maximum energy to sample. Default (Emax=0) is to set it to E0. | 0 |
| Emin | keV | Minimum energy to sample. | 1 |
| focus_xw | m | Width of exit window. | 5e-3 |
| focus_yh | m | Height of exit window. | 5e-3 |
| take_off | deg | Take off angle of beam centre. | 6 |
| dist | m | Distance between centre of illuminated target and exit window. | 1 |
| tube_current | A | Electron beam current. | 1e-3 |
| frac | 0-1 | Fraction of statistic to use for Bremsstrahlung. | 0.1 |
| lorentzian | 0/1 | If nonzero Lorentzian (more correct) line profiles are used. | 1 |
| xwidth | m | Width of the anode material slab. | 0 |
| yheight | m | Height of the anode material slab. | 0 |
| exit_window_refpt | m | If set, the AT position and exit window will coincide (legacy behaviour). | 0 |

## Links

- [Source code](/Users/peterwillendrup/Projects/willend-McCode/mcxtrace-comps/sources/Source_lab.comp) for `Source_lab.comp`.

---

*Generated on mcxtrace 3.99.99.*