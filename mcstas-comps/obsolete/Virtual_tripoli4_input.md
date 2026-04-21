# The `Virtual_tripoli4_input` Component

*McStas: This component reads a file of recorded neutrons from the reactor Monte Carlo
code TRIPOLI4.4 as a source of particles.*

## Identification

- **Site:** 
- **Author:** <a href="mailto:guillaume.campioni@cea.fr">Guillaume Campioni</a>
- **Origin:** <a href="http://www.serma.cea.fr/">SERMA</a>
- **Date:** Sep 28th, 2001

## Description

```text
This component generates neutron events from a file created using the
TRIPOLI4 Monte Carlo code for nuclear reactors (as MCNP). It is used to
calculate flux exiting from hot or cold neutron sources.
Neutron position and velocity is set from the file. The neutron time is
left at zero.
Storage files from TRIPOLI4.4 contain several batches of particules, all
of them having the same statictical weight.

Note that axes orientation may be different between TRIPOLI4.4 and McStas.
The component has the ability to center and orient the neutron beam to the Z-axis.
It also changes the coordinate system from the Tripoli frame to the McStas one.
The verbose mode is highly recommended as it displays lots of useful informations,
including the absolute intensity normalisation factor. All neutron fluxes in the
instrument should be multiplied by this factor. Such a renormalization is done
when 'autocenter' contains the word 'rescale'.
The source total intensity is 1.054e18 for LLB/Saclay (14 MW) and 4.28e18 for
ILL/Grenoble (58 MW).

Format of TRIPOLI4.4 event files is :

NEUTRON energy position_X position_Y position_Z dir_X dir_Y dir_Z weight

energy is in Mega eV
positions are in cm and the direction vector is normalized to 1.

%BUGS
We recommend NOT to use parallel execution (MPI) with this component. If you
need to, set parameter 'smooth=1'.

EXAMPLE:
To create a 'source' from a Tripoli4 simulation event file for the ILL:
COMPONENT source = Virtual_tripoli4_input(
filename = "ILL_SFH.dat", intensity=4.28e18,
verbose = 1, autocenter="translate rotate rescale")
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| filename | str | Name of the Tripoli4.4 neutron input file. Empty string "" unactivates component | 0 |
| autocenter | str | String which may contain following keywords. "translate" or "center"  to center the beam area AT (0,0,0) "rotate" or "orient" to center the beam velocity along Z "rescale" to adapt intensity to abs. units. Other words are ignored. | 0 |
| repeat_count | 1 | Number of times the source must be generated. 0 unactivates the component | 1 |
| verbose | 0\|1 | Displays additional informations if set to 1 | 0 |
| intensity | n/s | Initial total Source integrated intensity | 1 |
| T4_ANALYSE | 1 | Number of neutron events to read for file pre-analysis. Use 0 to analyze them all. | 10000 |
| radius | m | In the case the Tripoli4 batch file is a point, you may specify a disk emission area for the source. | 0 |
| T4_ANALYSE_EMIN | meV | Minimal energy to use for file pre-analysis | 0 |
| T4_ANALYSE_EMAX | meV | Maximal energy to use for file pre-analysis | 0 |
| smooth | 0/1 | Smooth sparsed event files for file repetitions. | 1 |

## Links

- [Source code](Virtual_tripoli4_input.comp) for `Virtual_tripoli4_input.comp`.
- <a href="http://www.nea.fr/html/dbprog/tripoli-abs.html">Tripoli</a>
- Virtual_tripoli4_output
- CAMPIONI Guillaume, Etude et Modelisation des Sources Froides de Neutrons, These de Doctorat, CEA Saclay/UJF (2004)

---

*Generated on mcstas 3.99.99.*