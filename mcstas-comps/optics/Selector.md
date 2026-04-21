# The `Selector` Component

*McStas: velocity selector (helical lamella type) such as <b>V_selector</b> component*

## Identification

- **Site:** 
- **Author:** Peter Link, <a href="mailto:Andreas.Ostermann@frm2.tum.de">Andreas Ostermann</a>
- **Origin:** Uni. Gottingen (Germany)
- **Date:** MARCH 1999

## Description

```text
Velocity selector consisting of rotating Soller-like blades
defining a helically twisted passage.
Geometry is defined by two identical apertures at 12 o'clock position,
The origin is at the ENTRANCE of the selector.

Example: Selector(xmin=-0.015,  xmax=0.015,  ymin=-0.025, ymax=0.025, length=0.25,
nslit=72,d=0.0004, radius=0.12, alpha=48.298, nu=500)
These are values for the D11@ILL Dornier 'Dolores' Velocity Selector (NVS 023)

%VALIDATION
Jun 2005: extensive external test, one minor problem
Jan 2006: problem solved (for McStas-1.9.1)
Validated by: K. Lieutenant

%BUGS
for transmission calculation, each neutron is supposed to be in the guide centre
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| xmin | m | Lower x bound of entry aperture | -0.015 |
| xmax | m | Upper x bound of entry aperture | 0.015 |
| ymin | m | Lower y bound of entry aperture | -0.025 |
| ymax | m | Upper y bound of entry aperture | 0.025 |
| length | m | rotor length | 0.25 |
| xwidth | m | Width of entry. Overrides xmin,xmax. | 0 |
| yheight | m | Height of entry. Overrides ymin,ymax. | 0 |
| nslit | 1 | number of absorbing subdivinding spokes/lamella | 72 |
| d | m | width of spokes at beam-center | 0.0004 |
| radius | m | radius of beam-center | 0.12 |
| alpha | deg | angle of torsion | 48.298 |
| nu | Hz | frequency of rotation, which is ideally 3956*alpha*DEG2RAD/2/PI/lambda/length | 500 |

## Links

- [Source code](Selector.comp) for `Selector.comp`.
- See also Additional notes <a href="http://mcstas.risoe.dk/pipermail/neutron-mc/1999q1/000134.html">March 1999</a> and <a href="http://mcstas.risoe.dk/pipermail/neutron-mc/1999q2/000136.html">Jan 2000</a>.

---

*Generated on mcstas 3.99.99.*