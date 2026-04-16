# The `Lens_elliptical` Component

*McXtrace: X-ray compound refractive lens (CRL) with an elliptic profile*

## Identification

- **Site:** 
- **Author:** Jana Baltser and Erik Knudsen
- **Origin:** NBI
- **Date:** August 2010

## Description

```text
A simple X-ray compound refractive lens (CRL) with an elliptic profile simulates the photons' movement on passing through it.
Attenuation coefficient mu is taken from the NIST database and Be.txt
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| material_datafile | Be.txt | File where the material parameters for the filter may be found. Format is similar to what may be found off the NIST website. | "Be.txt" |
| r1 | m | Radius of the profile along the X axis | 0.42e-3 |
| r2 | m | Radius of the profile along the Y axis | 0.8e-3 |
| w | m | Parabola parameter, constraining it along the propagation axis | 0.46e-3 |
| d | m | Distance between two surfaces of the lens along the propagation axis | 0.2e-4 |
| Transmission |  |  | 1 |
| N | 1 | Amount of single lenses in a stack | 1 |

## Links

- [Source code](/Users/peterwillendrup/Projects/willend-McCode/mcxtrace-comps/optics/Lens_elliptical.comp) for `Lens_elliptical.comp`.
- material datafile obtained from http://physics.nist.gov/cgi-bin/ffast/ffast.pl

---

*Generated on mcxtrace 3.99.99.*