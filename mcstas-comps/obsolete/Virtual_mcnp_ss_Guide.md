# The `Virtual_mcnp_ss_Guide` Component

*McStas: Neutron guide initiated using Virtual_mcnp_ss_input.comp, and replacing Virtual_mcnp_ss_output.comp  - see examples//Test_SSR_SSW_Guide.instr*

## Identification

- **Site:** 
- **Author:** Esben klinkby and Peter Willendrup
- **Origin:** Risoe-DTU
- **Date:** Marts 2012

## Description

```text
Based on Kristian Nielsens Guide.comp
Models a rectangular guide tube centered on the Z axis. The entrance lies
in the X-Y plane.
The component must be initiated after Virtual_mcnp_ss_input.comp,
and replaces Virtual_mcnp_ss_output.comp  - see examples/Test_SSR_SSW_Guide.instr.
The basic idea is, that rather than discarding unreflected (i.e. absorbed)
neutrons at the guide mirrors, these neutron states are stored on disk.
Thus, after the McStas simulation a MCNP simulation can be performed based
on the un-reflected neutrons - intended for shielding studies.
(details: we don't deal with actual neutrons, so what is transferred between
simulations suites is neutron state parameters: pos,mom,time,weight. The latter is
whatever remains after reflection.

For details on the geometry calculation see the description in the McStas
reference manual.
The reflectivity profile may either use an analytical mode (see Component
Manual) or a 2-columns reflectivity free text file with format
[q(Angs-1) R(0-1)].

Example: Virtual_mcnp_ss_Guide(w1=0.1, h1=0.1, w2=0.1, h2=0.1, l=2.0,
R0=0.99, Qc=0.021, alpha=6.07, m=2, W=0.003

%VALIDATION
Upcomming in 2012 based on ESS shielding
Validated by: D. Ene & E. Klinkby

%BUGS
This component does not work with gravitation on. Use component Guide_gravity then
(doesn't work with SSR/SSW unfortunately)
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| reflect | str | Reflectivity file name. Format <q(Angs-1) R(0-1)> | 0 |
| **w1** | m | Width at the guide entry |  |
| **h1** | m | Height at the guide entry |  |
| **w2** | m | Width at the guide exit |  |
| **h2** | m | Height at the guide exit |  |
| **l** | m | length of guide |  |
| R0 | 1 | Low-angle reflectivity | 0.99 |
| Qc | AA-1 | Critical scattering vector | 0.0219 |
| alpha | AA | Slope of reflectivity | 6.07 |
| m | 1 | m-value of material. Zero means completely absorbing. | 2 |
| W | AA-1 | Width of supermirror cut-off | 0.003 |

## Links

- [Source code](/Users/peterwillendrup/Projects/willend-McCode/mcstas-comps/obsolete/Virtual_mcnp_ss_Guide.comp) for `Virtual_mcnp_ss_Guide.comp`.

---

*Generated on mcstas 3.99.99.*