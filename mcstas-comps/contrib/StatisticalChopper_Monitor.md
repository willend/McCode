# The `StatisticalChopper_Monitor` Component

*McStas: Monitor designed to compute the autocorrelation signal for the Statistical Chopper*

## Identification

- **Site:** 
- **Author:** C. Monzat/E. Farhi
- **Origin:** ILL
- **Date:** 2009

## Description

```text
This component is a time sensitive monitor which calculates the cross
correlation between the pseudo random sequence of a statistical chopper
and the signal received. It mainly uses fonctions of component Monitor_nD.
It is possible to use the various options of the Monitor_nD but the user MUST NOT
specify "time" in the options. Auto detection of the time limits is possible if the
user chooses tmin=>tmax.

StatisticalChopper_Monitor(options ="banana bins=500, abs theta limits=[5,105],bins=1000")
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| **comp** | StatisticalChopper | quoted name of the component monitored |  |
| tmin | s | minimal time of detection | 0.0 |
| tmax | s | maximal time of detection | 0.0 |

## Links

- [Source code](StatisticalChopper_Monitor.comp) for `StatisticalChopper_Monitor.comp`.
- R. Von Jan and R. Scherm. The statistical chopper for neutron time-of-flight spectroscopy. Nuclear Instruments and Methods, 80 (1970) 69-76.

---

*Generated on mcstas 3.99.99.*