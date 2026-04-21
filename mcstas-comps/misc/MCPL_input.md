# The `MCPL_input` Component

*McStas: Source-like component that reads neutron state parameters from an mcpl-file.*

## Identification

- **Site:** 
- **Author:** Erik B Knudsen
- **Origin:** DTU Physics
- **Date:** Mar 2016

## Description

```text
Source-like component that reads neutron state parameters from a binary mcpl-file.

MCPL is short for Monte Carlo Particle List, and is a new format for sharing events
between e.g. MCNP(X), Geant4 and McStas.

When used with MPI, the --ncount given on the commandline is overwritten by
#MPI nodes x #events in the file.

Example: MCPL_input(filename=voutput,verbose=1,repeat_count=1,v_smear=0.1,pos_smear=0.001,dir_smear=0.01)
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| filename | str | Name of neutron mcpl file to read | 0 |
| polarisationuse |  | If !=0 read polarisation vectors from file | 1 |
| verbose |  | Print debugging information for first 10 particles read | 1 |
| Emin | meV | Lower energy bound. Particles found in the MCPL-file below the limit are skipped | 0 |
| Emax | meV | Upper energy bound. Particles found in the MCPL-file above the limit are skipped | FLT_MAX |
| repeat_count | 1 | Repeat contents of the MCPL file this number of times. NB: When running MPI, repeating is implicit and is taken into account by integer division. MUST be combined with _smear options! | 1 |
| v_smear | 1 | When repeating events, make a Gaussian MC choice within v_smear*V around particle velocity V | 0 |
| pos_smear | m | When repeating events, make a flat MC choice of position within pos_smear around particle starting position | 0 |
| dir_smear | deg | When repeating events, make a Gaussian MC choice of direction within dir_smear around particle direction | 0 |
| preload |  | Load particles during INITIALIZE. On GPU preload is forced | 0 |

## Links

- [Source code](MCPL_input.comp) for `MCPL_input.comp`.

---

*Generated on mcstas 3.99.99.*