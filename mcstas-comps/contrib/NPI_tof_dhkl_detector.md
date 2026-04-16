# The `NPI_tof_dhkl_detector` Component

*McStas: Release: McStas 2.5
Last update: 30/11/2018

NPI detector for estimating dhkl from tof*

## Identification

- **Site:** 
- **Author:** Jan Saroun, saroun@ujf.cas.cz
- **Origin:** NPI
- **Date:** July 1, 2017

## Description

```text
A cylindrical detector which converts time-of-flight data (x,y,z,time) to a 1D diffractogram in dhkl.
The detector model includes finite detection depth, spatial and time resolution. Optionally, the component
exports position and time coordinates of detection events in an ASCII file.

The component can also handle setups employing a modulation chopper for peak multiplexing at a long pulse source,
as proposed for the diffractometer BEER@ESS. In this case, the component requires chopper parameters
(modulation period, width of the primary unmodulated pulse), and a file with estimated dhkl values.
The component then estimates valid regions on the angle/tof map, excluding areas assumed to be empty
or with overlaping lines. This map is exported together with the diffractogram.

Tips for usage:
1) Centre the detector at the sample axis, keep z-axis parallel to the incident beam.
2) Set the radius equal to the distance from the sample axis to the front face of the detection volume.
3) Linst-Lc is used to determine "instrumental" wavelength as lambda = h/m_n*time/(Linst-Lc);
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| filename | str | Name of file in which to store the detector data. | 0 |
| radius | m | Radius of detector. | 2 |
| yheight | m | Height of detector. | 0.3 |
| zdepth | m | Thickness of the detection volume. | 0.01 |
| amin | deg | minimum of scattering angle to be detected. | 75 |
| amax | deg | maximum of scattering angle to be detected. | 105 |
| nd |  | Number of bins for dhkl in the 1D diffractograms. | 200 |
| na |  | Number of bins for scattering angles in the 2D maps. | 800 |
| nt |  | Number of bins for time of flight in the 2D maps. | 800 |
| nev |  | Number of detection events to export in "events.dat" (only modulation mode, set 1 for no export) | 1 |
| d_min | AA | minimum of inter-planar spacing to be detected. | 1 |
| d_max | AA | maximum of inter-planar spacing to be detected. | 3 |
| **time0** | s | Time delay of the wavelength definition chopper with respect to the source pulse. |  |
| **Linst** | m | Distance from the source to the detector. |  |
| **Lc** | m | Distance from the source to the pulse chopper (set 0 for a short pulse source). |  |
| res_x | m | Spatial resolution along x (Gaussian FWHM). | 0 |
| res_y | m | Spatial resolution along y (Gaussian FWHM). | 0 |
| res_t | s | Time resolution (Gaussian FWHM). Readout only, path to capture is accounted for by the tracing code. | 0 |
| mu | 1/cm/AA | Capture coefficient for the detection medium. | 1.0 |
| mod_shift | float | Relative shift of the modulation pattern (delta_d/d, constant for all reflections). | 0 |
| modulation | 1\|0 | Switch on/off the modulation regime (BEER multiplexing technique). | 0 |
| mod_dt | s | Modulation period. | 0 |
| mod_twidth | s | Width of the primary source pulse. | 0 |
| mod_d0_table | str | Name of a file with the list of dhkl estimates (one per line). | 0 |
| verbose | 1\|0 | Switch for extended reporting. | 0 |
| restore_neutron | 1\|0 | Switch for restoring of previous neutron state. | 1 |

## Links

- [Source code](/Users/peterwillendrup/Projects/willend-McCode/mcstas-comps/contrib/NPI_tof_dhkl_detector.comp) for `NPI_tof_dhkl_detector.comp`.

---

*Generated on mcstas 3.99.99.*