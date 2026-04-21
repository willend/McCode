# The `Magnon_bcc` Component

*McStas: A sample for AFM or FM magnon scattering
based on cross section expressions from Squires, Ch.8.2*

## Identification

- **Site:** 
- **Author:** Kim Lefmann
- **Origin:** KU
- **Date:** 23.10.08 - 24.07.18

## Description

```text
Single-cylinder shape.
Absorption included.
No multiple scattering.
No incoherent scattering emitted.
No attenuation from coherent scattering. No Bragg scattering.
bcc crystal n.n. and n.n.n. interactions only
Can do either FM or AFM order upon a flag
Assume J>0 for both FM and AFM. MUST BE CHANGED FOR CONSISTENCY
If AFM, the order is two-sublattice, e.g. the AFM Bragg ordering vectors are Q = (1 0 0) and equivalent.
One magnon branch only
Assume spin along z
Possible easy axis anisotropy along z
No external field

KNOWN BUGS:
Gives zero scattering for too large J values (for AFM J=0.362, h approx 1). Probably this is a malfunction of zridd or call thereof
The value of the absolute scattered intensity is clearly too high. This is probably due to unit confusion. The relative intensity scaling seems about right.

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
| **a** | AA | bcc Lattice constant |  |
| FM | 1 | Flag for whether the order if FM (0 means AFM) | 0 |
| **J1** | meV | spin-spin interaction 1 (nn) |  |
| **J2** | meV | spin-spin interaction 2 (nnn) |  |
| **D** | mev | single ion anisotropy |  |
| **s** | 1 | spin |  |
| **DW** | 1 | Debye-Waller factor |  |
| **T** | K | Temperature |  |
| target_x | m | position of target to focus at . Transverse coordinate | 0 |
| target_y | m | position of target to focus at. Vertical coordinate | 0 |
| target_z | m | position of target to focus at. Straight ahead. | 0 |
| target_index | 1 | relative index of component to focus at, e.g. next is +1 | 0 |
| F2 | 1 | magnetic form factor squared | 1 |
| focus_r | m | Radius of sphere containing target. | 0 |
| focus_xw | m | horiz. dimension of a rectangular area | 0 |
| focus_yh | m | vert.  dimension of a rectangular area | 0 |
| focus_aw | deg | horiz. angular dimension of a rectangular area | 0 |
| focus_ah | deg | vert.  angular dimension of a rectangular area | 0 |
| verbose | 1 | flag for test printing (print if verbose==1) | 0 |

## Links

- [Source code](Magnon_bcc.comp) for `Magnon_bcc.comp`.
- The test/example instrument <a href="../examples/Test_Magnon.instr">Test_Magnon.instr</a>.

---

*Generated on mcstas 3.99.99.*