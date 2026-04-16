# The `ZonePlate` Component

*McXtrace: Release: McXtrace 1.4

Zone plate based on Monte Carlo sampling of the Fresnel-Kirchhoff integral*

## Identification

- **Site:** 
- **Author:** Erik B Knudsen
- **Origin:** DTU Physics
- **Date:** June 16, 2009

## Description

```text
A component which models a zone plate by consierding the plate a secondary source
and then by means of Monte Carlo sampling, evaluating the Fresnel-Kirchhoff integral
implicitly by resampling the beam in a window defined by the focus_xw,focus_yh parameters.

Caveat emptor I: this is a computationally heavy component to run.
Caveat emptor II: for correct modelling of phase-interference phenomena, detectors used after the ZonePlate
should be of the <strong>"PSD_monitor_coh"</strong> type.

The zone plate can be either circular or linear. In the linear case, the "slits" are
along the x-axis.

Example: ZonePlate(radius=0.00015, L=0.15, lambda0=1, focus_xw=300e-9, focus_yh = 300e-9, focus_x0 = 0.0, focus_y0 = 0.0, dist=1)
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| radius | m | The outer radius of the zone plate. Triggers a circular zone plate. Takes precedence over xwidth,yheight. | 0 |
| xwidth | m | Width of linear zone plate. | 0 |
| yheight | m | Height of linear zone plate | 0 |
| **L** | m | Focal length. |  |
| **lambda0** | AA | The nominal wavelength that the zone plate is designed to focus. |  |
| focus_x0 | m | Offset of resampling window along the x-axis. | 0 |
| focus_y0 | m | Offset of resampling window along the y-axis. | 0 |
| **focus_xw** | m | Width of the resampling window. |  |
| **focus_yh** | m | Height of the resampling window. |  |
| **dist** | m | Distance along the z-axis from zone plate to the resampling window. |  |

## Links

- [Source code](/Users/peterwillendrup/Projects/willend-McCode/mcxtrace-comps/optics/ZonePlate.comp) for `ZonePlate.comp`.

---

*Generated on mcxtrace 3.99.99.*