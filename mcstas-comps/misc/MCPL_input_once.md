# The `MCPL_input_once` Component

*McStas: Source-like component that reads neutron state parameters from a MCPL-file one time.*

## Identification

- **Site:** 
- **Author:** Gregory S Tucker
- **Origin:** European Spallation Source ERIC
- **Date:** Sep 2024

## Description

```text
Source-like component that reads neutron state parameters from a MCPL-file one time.

MCPL is short for Monte Carlo Particle List, and is a format for sharing events
between e.g. MCNP(X), Geant4 and McStas.

When used with MPI, the file contents are shared between workers with each accessing
approximately (#events in the file) / (#MPI nodes)

%BUGS
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| filename | str | Name of neutron mcpl file to read. | 0 |
| polarisationuse |  | If !=0 read polarisation vectors from file. | 1 |
| Emin | meV | Lower energy bound. Particles found in the MCPL-file below the limit are skipped. | 0 |
| Emax | meV | Upper energy bound. Particles found in the MCPL-file above the limit are skipped. | FLT_MAX |
| v_smear | 1 | Relative fraction for randomness in replayed particle velocity v *= (1 + v_smear * randpm1()) | 0 |
| pos_smear | m | Maximum extent of random position for replayed particles | 0 |
| dir_smear | deg | Maximum deviation of random direction for replayed particles | 0 |
| always_smear |  | Finite values force particle property smearing for all particles | 0 |
| preload |  | Load particles during INITIALIZE. On GPU preload is forced. | 0 |
| verbose |  | Finite values may cause extra output (at some point in the future) | 0 |

## Links

- [Source code](/Users/peterwillendrup/Projects/willend-McCode/mcstas-comps/misc/MCPL_input_once.comp) for `MCPL_input_once.comp`.

---

*Generated on mcstas 3.99.99.*