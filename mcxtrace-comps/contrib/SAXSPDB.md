# The `SAXSPDB` Component

*McXtrace: Release: McXtrace 1.0

A sample describing a thin solution of proteins. This components must be compiled
with the -lgsl and -lgslcblas flags (and possibly linked to the appropriate
libraries).*

## Identification

- **Site:** 
- **Author:** Martin Cramer Pedersen (mcpe@nbi.dk) and Søren Kynde (kynde@nbi.dk)
- **Origin:** KU-Science
- **Date:** May 2, 2012

## Description

```text
This components expands the formfactor amplitude of the protein on spherical
harmonics and computes the scattering profile using these. The expansion is
done on amino-acid level and does not take hydration layer into account.
The component must have a valid .pdb-file as an argument.

This component is very slow. You should rather use the SAXSPDBFast sample component.
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| RhoSolvent | AA | Scattering length density of the buffer. | 9.4e-14 |
| Concentration | mM | Concentration of sample. | 0.01 |
| AbsorptionCrosssection | 1/m | Absorption cross section of the sample. | 0.0 |
| **xwidth** | m | Dimension of component in the x-direction. |  |
| **yheight** | m | Dimension of component in the y-direction. |  |
| **zdepth** | m | Dimension of component in the z-direction. |  |
| **SampleToDetectorDistance** | m | Distance from sample to detector (for focusing the scattered x-rays). |  |
| **DetectorRadius** | m | Radius of the detector (for focusing the scattered x-rays). |  |
| PDBFilepath |  | Path to the file describing the high resolution structure of the protein. | "PDBfile.pdb" |

## Links

- [Source code](/Users/peterwillendrup/Projects/willend-McCode/mcxtrace-comps/contrib/SAXSPDB.comp) for `SAXSPDB.comp`.

---

*Generated on mcxtrace 3.99.99.*