# The `Phonon_simple` Component

*McStas: A sample for phonon scattering based on cross section expressions from Squires, Ch.3.
Possibility for adding an (unphysical) bandgap.*

## Identification

- **Site:** 
- **Author:** Kim Lefmann
- **Origin:** Risoe
- **Date:** 04.02.04

## Description

```text
Single-cylinder shape.
Absorption included.
No multiple scattering.
No incoherent scattering emitted.
No attenuation from coherent scattering. No Bragg scattering.
fcc crystal n.n. interactions only
One phonon branch only -> phonon polarization not accounted for.
Bravais lattice only. (i.e. just one atom per unit cell)

Algorithm:
0. Always perform the scattering if possible (otherwise ABSORB)
1. Choose direction within a focusing solid angle
2. Calculate the zeros of (E_i-E_f-hbar omega(kappa)) as a function of k_f
3. Choose one value of k_f (always at least one is possible!)
4. Perform the correct weight transformation
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| **radius** | m | Outer radius of sample in (x,z) plane |  |
| **yheight** | m | Height of sample in y direction |  |
| **sigma_abs** | barns | Absorption cross section at 2200 m/s per atom |  |
| **sigma_inc** | barns | Incoherent scattering cross section per atom |  |
| **a** | AA | fcc Lattice constant |  |
| **b** | fm | Scattering length |  |
| **M** | a.u. | Atomic mass |  |
| **c** | meV/AA^(-1) | Velocity of sound |  |
| **DW** | 1 | Debye-Waller factor |  |
| **T** | K | Temperature |  |
| target_x | m | position of target to focus at . Transverse coordinate | 0 |
| target_y | m | position of target to focus at. Vertical coordinate | 0 |
| target_z | m | position of target to focus at. Straight ahead. | 0 |
| target_index | 1 | relative index of component to focus at, e.g. next is +1 | 0 |
| focus_r | m | Radius of sphere containing target. | 0 |
| focus_xw | m | horiz. dimension of a rectangular area | 0 |
| focus_yh | m | vert.  dimension of a rectangular area | 0 |
| focus_aw | deg | horiz. angular dimension of a rectangular area | 0 |
| focus_ah | deg | vert.  angular dimension of a rectangular area | 0 |
| gap | meV | Bandgap energy (unphysical) | 0 |
| e_steps_low | 1 | Amount of possible intersections beneath the elastic line | 50 |
| e_steps_high | 1 | Amount of possible intersections above the elastic line | 50 |

## Links

- [Source code](/Users/peterwillendrup/Projects/willend-McCode/mcstas-comps/samples/Phonon_simple.comp) for `Phonon_simple.comp`.
- The test/example instrument <a href="../examples/Test_Phonon.instr">Test_Phonon.instr</a>.

---

*Generated on mcstas 3.99.99.*