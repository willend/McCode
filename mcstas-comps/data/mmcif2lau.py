#!/usr/bin/env python3
"""Neutron |F|^2 reflection list (.lau, for Single_crystal) from a PDB or mmCIF model.

Usage: python mmcif2lau.py model.{pdb,cif} [dmin_Angs=1.5] > model.lau
Needs gemmi (conda-forge). Uses the atoms as given: add H/D to the model first,
X-ray models usually have none and neutron intensities depend strongly on them.
"""
import sys
import gemmi


def main(path, dmin=1.5, out=sys.stdout):
    st = gemmi.read_structure(path)
    st.setup_entities()
    cell, sg = st.cell, st.find_spacegroup()
    if sg is None:
        sys.exit(f"mmcif2lau: no space group in {path}")
    calc = gemmi.StructureFactorCalculatorN(cell)  # Neutron92 b_coh in fm
    hkls = gemmi.make_miller_array(cell, sg, dmin, unique=False)
    print(f"# {st.name} from {path}, neutron |F|^2 [fm^2] by gemmi {gemmi.__version__}, dmin={dmin} Angs\n"
          f"# SPCGRP {sg.hm} ({sg.number})", file=out)
    for k, v in zip(("a", "b", "c", "aa", "bb", "cc"),
                    (cell.a, cell.b, cell.c, cell.alpha, cell.beta, cell.gamma)):
        print(f"# lattice_{k} {v}", file=out)
    print("# column_h 1\n# column_k 2\n# column_l 3\n# column_F2 4", file=out)
    for h, k, l in hkls.tolist():
        f = calc.calculate_sf_from_model(st[0], [h, k, l])
        print(h, k, l, f"{abs(f) ** 2:.6g}", file=out)


if __name__ == "__main__":
    if len(sys.argv) < 2:
        sys.exit(__doc__)
    main(sys.argv[1], *map(float, sys.argv[2:3]))
