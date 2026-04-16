# The `Virtual_mcnp_ss_input` Component

*McStas: This component uses a Source Surface type file of recorded neutrons from the
reactor monte carlo code MCNP as a source of particles.*

## Identification

- **Site:** 
- **Author:** <a href="mailto:esbe@dtu.dk">Esben Klinkby</a> and <a href="mailto:pkwi@dtu.dk">Peter Willendrup</a>
- **Origin:** <a href="http://www.risoe.dtu.dk/">DTU</a>
- **Date:** January, 2012

## Description

```text
This component draws neutron events from a Source Surface file created using the
MCNP Monte Carlo code and converts them to make them suitable for a McStas simulation

Note that axes orientation may be different between MCNP and McStas!
Note also that the conversion of between McStas and MCNP units and parameters
is done automatically by this component - but the user must ensure that
geometry description matches between the two Monte Carlo codes.

The verbose mode is highly recommended as it displays lots of useful informations.

This interface uses the MCNP Source Surface Read/Write format (SSW/SSR).
Infomation transfer from(to) SSW files proceeds via a set of Fortran modules
and subroutines collected in "subs.f"
For succesful compilation, it is required that these subroutines are compiled
and linked to the instrument file:

mcstas dummy.instr  -> generates dummy.c
gfortran -c subs.f  -> generates subs.f
gcc -o runme.out dummy.c subs.o -lm -lgfortran  -> generates runme.out

Note that this requires a fortran compiler (here gfortran) and gcc.

%BUGS
None known bugs so far. But surely this will change...
Caveat: when writing the header for the output wssa file, the number of histories and tracks are assumed to be that of the
input MNCP run. This is generally not the case, due to losses in the McStas simulation step.
In case of losses any subsequel MCNP run based on the McStas output, can be confused by inconsistency between
header and file content. To resolve, either ensure that NPS is lower than the actual number of events in the McStas output.
Or hardcode values of nhis & ntrk in either subs.f or Virtual_mcnp_ss_output.comp.

EXAMPLE of usage:
first a MCNP simulation is run
and at a relevant surface, a Source Surface Write card is given (e.g. for MCNP surface #1, add the line:
SSW 1
to the end of the input file.
By this a ".w" file is produced, which then serves as input to the McStas simulation.
Present version: rename *.w to rssa, and make sure to put it in the dir from which McStas is run
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| file | str | Name of the MCNP SSW neutron input file. Not active: Name assumed to be 'rssa' | "rssa" |
| verbose | 1 | Toggles debugging info on/off | 1 |

## Links

- [Source code](/Users/peterwillendrup/Projects/willend-McCode/mcstas-comps/obsolete/Virtual_mcnp_ss_input.comp) for `Virtual_mcnp_ss_input.comp`.
- <a href="http://mcnp-green.lanl.gov/index.html">MCNP</a>
- MCNP -- A General Monte Carlo N-Particle Transport Code, Version 5, Volume II: User's Guide, p177

---

*Generated on mcstas 3.99.99.*