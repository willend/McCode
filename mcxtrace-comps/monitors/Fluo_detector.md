# The `Fluo_detector` Component

*McXtrace: Detector for fluorescence, e.g. Silicon Drift Detector (SDD) or High Purity Germanium (HPGe).*

## Identification

- **Site:** 
- **Author:** E. Farhi
- **Origin:** Synchrotron SOLEIL
- **Date:** May 2025

## Description

```text
A detector that records energy spectrum from e.g. fluorescence.
This component handles:
- fluorescence detector escape  (energy shift from detector K-alpha)
- fluorescence detector pile-up (sum aka time-coincidence aka pile-up within detector dead-time)
- energy resolution (above Fano level)

The detector geometry can be a rectangle xwidth*yheight, or a disk of given 'radius'.
When the radius is given negative, a 4PI detector sphere of given radius is assumed.

The detector escape corresponds with a fluorescence excitation within the detector itself
that subtracts the K-alpha detector level from the sample scattered energy.
The level of escape peaks in set as 'escape_ratio', e.g. 1-2 %.

The detector pile-up is related to the detector dead-time, within which time coincidence
between two fluorescence photons are summed-up.
The level of pile-up is set as 'pileup_ratio', e.g. 1-2 % which can increase for high
count rates that saturate the detector.

Last, the fluorescence peak shape is broadened using an electronic noise (at E=0) and
a nominal resolution at E=resolution_energy (in keV). You may set the electronic_noise
to zero for a perfect detector (Fano limit). To use a constant resolution, set the
resolution_energy=0.

Example: Fluo_detector(xwidth=0.1, yheight=0.1,
Emin=1, Emax=50, nE=20, filename="Output.nrj")
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| radius | m | Radius of disk detector (in XY plane). When given as negative, a 4PI sphere is assumed. | 0 |
| xwidth | m | Width  of rectangle detector. | 0 |
| yheight | m | Height of rectangle detector. | 0 |
| Emin | keV | Minimum energy to detect. | 1 |
| Emax | keV | Maximum energy to detect. | 39 |
| nE | m | Number of energy channels. | 2000 |
| filename | str | Name of file in which to store the detector image. | 0 |
| restore_xray | 0/1 | If set, the monitor does not influence the x-ray state. | 0 |
| escape_ratio | 1 | Detector escape peak ratio,  e.g. 0.01-0.02. Zero inactivates. | 0.01 |
| escape_energy | keV | Detector escape peak energy, e.g. 1.739 for Si, 9.886 for Ge. | 1.739 |
| pileup_ratio | 1 | Sum aka time coincidence aka pile-up detector peak ratio, e.g. 0.01-0.02. This is e.g. the dead-time ratio. Zero inactivates. | 0.01 |
| electronic_noise | keV | Electronic noise at E=0, FWHM in keV. Use electronic_noise=0 for Fano limit. | 0.1 |
| resolution_energy | keV | Energy at which resolution is given, e.g. 5.9 keV Mn K-alpha. | 6 |
| resolution | keV | Resolution FWHM in keV at resolution_energy. | 0.2 |
| flag_lorentzian | 1 | When 1, the line shapes are assumed to be Lorentzian, else Gaussian. | 0 |

## Links

- [Source code](/Users/peterwillendrup/Projects/willend-McCode/mcxtrace-comps/monitors/Fluo_detector.comp) for `Fluo_detector.comp`.
- Fluorescence https://en.wikipedia.org/wiki/Fluorescence

---

*Generated on mcxtrace 3.99.99.*