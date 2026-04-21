# The `MCPL_output` Component

*McStas: Detector-like component that writes neutron state parameters into an mcpl-format
binary, virtual-source neutron file.*

## Identification

- **Site:** 
- **Author:** Erik B Knudsen
- **Origin:** DTU Physics
- **Date:** Mar 2016

## Description

```text
Detector-like component that writes neutron state parameters into an mcpl-format
binary, virtual-source neutron file.

MCPL is short for Monte Carlo Particle List, and is a new format for sharing events
between e.g. MCNP(X), Geant4 and McStas.

When used with MPI, the component will output #MPI nodes individual MCPL files that
can be merged using the mcpltool.

MCPL_output allows a few flags to tweak the output files:
1. If use_polarisation is unset (default) the polarisation vector will not be stored (saving space)
2. If doubleprec is unset (default) data will be stored as 32 bit floating points, effectively cutting the output file size in half.
3. Extra information may be attached to each ray in the form of a userflag, a user-defined variable wich is packed into 32 bits. If
the user variable does not fit in 32 bits the value will be truncated and likely garbage. If more than one variable is to be attached to
each neutron this must be packed into the 32 bits.

These features are set this way to keep file sizes as manageable as possible.

Example: MCPL_output( filename="voutput", verbose=1, userflag="flag", userflagcomment="Neutron Id" )
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| filename | str | Name of neutron file to write. If not given, the component name will be used. | 0 |
| weight_mode | 1 | weight_mode=1: record initial ray count in MCPL stat:sum entry and rescale particle weights. weight_mode=2: classical (deprecated) mode of outputting particle weights directly. | -1 |
| verbose | 1 | If 1) Print summary information for created MCPL file. 2) Also print summary of first 10 particles information stored in the MCPL file. >2) Also print information for first 10 particles as they are being stored by McStas | 0 |
| polarisationuse | 1 | Enable storing the polarisation state of the neutron. | 0 |
| doubleprec | 1 | Use double precision storage | 0 |
| userflag | 1 | Extra variable to attach to each neutron. The value of this variable will be packed into a 32 bit integer. | "" |
| userflagcomment | str | String variable to describe the userflag. If this string is empty (the default) no userflags will be stored. | "" |
| buffermax | 1 | Maximal number of events to save ( <= MAXINT), GPU/OpenACC only | 0 |

## Links

- [Source code](MCPL_output.comp) for `MCPL_output.comp`.

---

*Generated on mcstas 3.99.99.*