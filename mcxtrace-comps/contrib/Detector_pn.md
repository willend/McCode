# The `Detector_pn` Component

*McXtrace: Version: McXtrace 1.2

Block of a attenuating material*

## Identification

- **Site:** 
- **Author:** Maria Thomsen (mariath@fys.ku.dk)
- **Origin:** NBI, KU
- **Date:** Jan 24, 2011

## Description

```text
A scintillator detector model taking photoabsorption efficiency into account. As such it consitututes a
more physical version of the PSD_monitor. Only direct absorption is taken into account.

Example: Detector_pn(restore_xray=restore_flag,filename="detector_Si", material_datafile="Si.txt", xwidth=1e-2, yheight=1e-2,zdepth=1e-5)
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| material_datafile | str | File where the material parameters for the scintillator may be found. Format is similar to what may be found off the NIST website. | "Be.txt" |
| nx | m | Number of pixel columns. | 90 |
| ny | m | Number of pixel rows. | 90 |
| filename | str | Name of file in which to store the detector image. | "" |
| restore_xray |  | If set, the monitor does not influence the xray state. | 0 |
| xwidth | m | Width of block. | 1e-2 |
| yheight | m | Height of block. | 1e-2 |
| zdepth | m | Thickness of block. | 1e-6 |

## Links

- [Source code](/Users/peterwillendrup/Projects/willend-McCode/mcxtrace-comps/contrib/Detector_pn.comp) for `Detector_pn.comp`.
- material datafile obtained from http://physics.nist.gov/cgi-bin/ffast/ffast.pl

---

*Generated on mcxtrace 3.99.99.*