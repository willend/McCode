# The `Powder1` Component

*McStas: General powder sample with a single scattering vector.*

## Identification

- **Site:** 
- **Author:** E.M.Lauridsen, N.B.Christensen, A.B.Abrahamsen
- **Origin:** Risoe
- **Date:** 4.2.98

## Description

```text
General powder sample with a single scattering vector. No multiple ,
scattering, no incoherent scattering, no secondary extinction.
The shape of the sample may be a cylinder of given radius or a box with
dimensions xwidth, yheight, zdepth.
The efficient is highly improved when restricting the vertical scattering
range on the Debye-Scherrer cone (with 'd_phi').
You may use PowderN to use N scattering lines defined in a file.

Example: Powder1(radius=0.015,yheight=0.05,q =1.8049,d_phi=0.07,pack=1,
j=6,DW=1,F2=56.8,Vc=85.0054,sigma_abs=0.463)
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| radius | m | Radius of sample in (x,z) plane | 0.01 |
| yheight | m | Height of sample y direction | 0.05 |
| xwidth | m | horiz. dimension of sample, as a width | 0 |
| zdepth | m | depth of box sample | 0 |
| q | AA^-1 | Scattering vector of reflection | 1.8049 |
| d | AA | d-spacing for sample, overrides 'q' | 0 |
| d_phi | deg,0-180 | Angle corresponding to the vertical angular range to focus to, e.g. detector height. 0 for no focusing | 0 |
| pack | 1 | Packing factor | 1 |
| j | 1 | Multiplicity of reflection | 6 |
| DW | 1 | Debye-Waller factor of reflection | 1 |
| F2 | barns | Structure factor of reflection | 56.8 |
| Vc | AA^3 | Volume of unit cell | 85.0054 |
| sigma_abs | barns | Absorption cross section per unit cell at 2200 m/s | 0.463 |

## Links

- [Source code](Powder1.comp) for `Powder1.comp`.
- <A HREF="http://neutron.risoe.dk/mcstas/components/tests/powder/">
- Test results</A> (not up-to-date).
- See also: Powder1, Powder2 and PowderN

---

*Generated on mcstas 3.99.99.*