# The `Sapphire_Filter` Component

*McStas: Sapphire filter at 300K*

## Identification

- **Site:** 
- **Author:** Jonas Okkels Birk (based upon Filteg_Graphite by Thomas C Hansen (2000))
- **Origin:** PSI
- **Date:** 6 December 2006

## Description

```text
ESCRIPTION

This sapphire filter, defined by two identical rectangular opening apertures,
is based upon an absorption function absorp=exp(L*A+C*(exp(-(B/L^2+D/L^4))))
decribed by Freund (1983) Nucl. Instrum. Methods, A278, 379-401. The
defaultvalues is for Sapphire at 300K as found by measurement by (Mildner &
Lamaze (1998) J. Appl. Cryst. 31,835-840
( http://journals.iucr.org/j/issues/1998/06/00/hw0070/hw0070bdy.html#BB4)). It
is possble to ajust the formular to other materials or temperatures by typing in
other parameters.
The transmission in sapphire is only lightly demependt on temperature, but
The formular is only cheked at wavelenths between 0.5 and 14 AA (0.4 meV 0.3
eV).
The filter is for example used in the Eiger beamline at PSI to cut of high
energies.
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| xmin | m | Lower x bound | -0.16 |
| xmax | m | Upper x bound | 0.16 |
| ymin | m | Lower y bound | -0.16 |
| ymax | m | Upper y bound | 0.16 |
| len | m | Thickness of filter | 0.1 |
| A | m^-1 AA^-1 |  | 0.8116 |
| B | AA^2 |  | 0.1618 |
| C | m^-1 |  | 21.24 |
| D | AA^4 |  | 0.1291 |

## Links

- [Source code](Sapphire_Filter.comp) for `Sapphire_Filter.comp`.

---

*Generated on mcstas 3.99.99.*