# The `Source_extended` Component

*McXtrace: Release: McXtrace 1.4

A plane source emitting x-rays to emulate a distant extended source, such as a
nebula or galaxy*

## Identification

- **Site:** 
- **Author:** Arne 'S Jegers
- **Origin:** Technical University of Denmark
- **Date:** May 6, 2019

## Description

```text
A rectangular x-ray source that samples ray intensity from an image, and
deflects the emitted ray to reflect having been emitted from the sampled part
of the extended source. Rays that are sampled from the same point on the image
are collimated, but can be emitted from anywhere on the rectangular source.
The image should be provided as a 2D-ascii table, whose header includes the
following entries:

w_pixels and h_pixels: The width and height of the image in pixels
x_ref and y_ref: x and y reference values of the FITS image
r_max: The maximum distance from the point (x_ref, y_ref) to any corner of the image
iCD11, iCD12, iCD21 and iCD22: The values of the FITS image's CD matrix
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| spectrum_file |  |  | NULL |
| yheight | m | Height of rectangle in (x,y,0) plane where x-rays | 0 |
| xwidth | m | Width of rectangle in (x,y,0) plane where x-rays | 0 |
| dist |  |  | 0 |
| E0 | keV | Mean energy of xrays. | 0 |
| dE | keV | Energy half spread of x-rays (flat or gaussian sigma). | 0 |
| lambda0 | AA | Mean wavelength of x-rays. | 0 |
| dlambda | AA | Wavelength half spread of x-rays. | 0 |
| flux | pht/s | total flux radiated from the source | 0 |
| gauss | 1 | Gaussian (1) or Flat (0) energy/wavelength distribution | 0 |
| incoherent |  | Source is fully incoherent | 1 |
| phase |  | Set phase to something given. | 0 |
| image_path | string | Path to file containing the heat map of the source | "" |

## Links

- [Source code](/Users/peterwillendrup/Projects/willend-McCode/mcxtrace-comps/astrox/Source_extended.comp) for `Source_extended.comp`.

---

*Generated on mcxtrace 3.99.99.*