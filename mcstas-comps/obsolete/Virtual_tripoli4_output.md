# The `Virtual_tripoli4_output` Component

*McStas: Detector-like component that writes neutron state parameters into a
'virtual source' neutron file when neutrons come from the source :
Virtual_tripoli4_input.comp*

## Identification

- **Site:** 
- **Author:** <a href="mailtoguillaume.campioni@cea.fr">Guillaume Campioni</a>
- **Origin:** <a href="http://www.cea-llb.fr">LLB</a>
- **Date:** Sep 28th, 2001

## Description

```text
Detector-like component writing neutron state parameters to a
virtual source neutron file when neutron are coming from a
Virtual_tripoli4_input.comp.
The component geometry is the full plane, and saves the neutron state as
it exits from the previous component.
Format is the one used by TRIPOLI4.4 stock files :

NEUTRON energy position_X position_Y position_Z dir_X dir_Y dir_Z weight

energy is in [Mega eV]
positions are in [cm] and the direction vector is normalized to 1.

%BUGS
This component will NOT work with parallel execution (MPI/GPU).

EXAMPLE:
To create a file collecting all neutron states with TRIPOLI4 format
COMPONENT T4output = Virtual_tripoli4_output(
filename = "exit_guide_result.dat", batch = 1 )
at the position where will be the Virtual_tripoli4_input when reading the file.
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| filename | str | Name of the Tripoli4 neutron output file, | 0 |
| batch | 1 | Index of the Tripoli batch to generate, when no | 1 |

## Links

- [Source code](Virtual_tripoli4_output.comp) for `Virtual_tripoli4_output.comp`.
- <a href="http://www.nea.fr/html/dbprog/tripoli-abs.html">Tripoli</a>
- Virtual_tripoli4_input

---

*Generated on mcstas 3.99.99.*