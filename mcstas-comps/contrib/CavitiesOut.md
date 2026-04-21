# The `CavitiesOut` Component

*McStas: Slit - sorting in channels*

## Identification

- **Site:** 
- **Author:** Henrich Frielinghaus
- **Origin:** JCNS - FZ-Juelich
- **Date:** Oct 2007

## Description

```text
This routine sorts the 'full' neutron beam (given by xw,yw)
in xc,yc channels. These can be imagined as cavities.
CavitiesOut sorts these channels back to normal coordinates.

Example: Slit(xw=0.05, yw=0.05, xc=4, yc=1)
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| xw | m | width in X-dir (full width, might be larger for trumpets) | 0.05 |
| yw | m | width in Y-dir (full width, might be larger for trumpets) | 0.05 |
| xc | 1 | Number of x-channels | 1 |
| yc | 1 | Number of y-channels | 1 |

## Links

- [Source code](CavitiesOut.comp) for `CavitiesOut.comp`.

---

*Generated on mcstas 3.99.99.*