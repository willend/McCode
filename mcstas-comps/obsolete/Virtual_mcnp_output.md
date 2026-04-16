# The `Virtual_mcnp_output` Component

*McStas: Detector-like component that writes neutron state parameters into a
'virtual source' neutron file with MCNP/PTRAC format.*

## Identification

- **Site:** 
- **Author:** <a href="mailto hennanec@ensimag.fr">Chama Hennane</a> and E. Farhi
- **Origin:** <a href="http://www.ill.fr/">ILL</a>
- **Date:** July 7th, 2006

## Description

```text
Detector-like component writing neutron state parameters to a
virtual source neutron file with MCNP/PTRAC format.
The component geometry is the full plane, and saves the neutron state as
it exits from the previous component.
Format is the one used by MCNP 5 files :

position_X position_Y position_Z dir_X dir_Y dir_Z energy weight time

energy is in Mega eV
positions are in cm and the direction vector is normalized to 1.

%BUGS
This component will NOT work with parallel execution (MPI).

EXAMPLE:
To create a file collecting all neutron states with MCNP5 format
COMPONENT fichier_sortie = Virtual_mcnp_output(
filename = "exit_guide_result.dat")
at the position where will be the Virtual_mcnp_input.
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| filename | str | name of the MCNP5 neutron output file, | 0 |

## Links

- [Source code](/Users/peterwillendrup/Projects/willend-McCode/mcstas-comps/obsolete/Virtual_mcnp_output.comp) for `Virtual_mcnp_output.comp`.
- <a href="http://mcnp-green.lanl.gov/index.html">MCNP</a>
- MCNP -- A General Monte Carlo N-Particle Transport Code, Version 5, Volume II: User's Guide, p177

---

*Generated on mcstas 3.99.99.*