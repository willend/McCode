# The `NCrystal_process` Component

*McStas: NCrystal_process component for the Union framework.*

## Identification

- **Site:** 
- **Author:** NCrystal developers, converted to a Union component by Mads Bertelsen
- **Origin:** NCrystal Developers (European Spallation Source ERIC and DTU Nutech)
- **Date:** 20.08.15

## Description

```text
This process uses the NCrystal library as a Union process, see user documentation
for the NCrystal_sample.comp component for more information. The process only
uses the physics, as the Union components has a separate geometry system.
Absorption is also handled by Union, so any absorption output from NCrystal
is ignored.

Part of the Union components, a set of components that work together and thus
sperates geometry and physics within McStas.
The use of this component requires other components to be used.

1) One specifies a number of processes using process components like this one
2) These are gathered into material definitions using Union_make_material
3) Geometries are placed using Union_box / Union_cylinder, assigned a material
4) A Union_master component placed after all of the above

Only in step 4 will any simulation happen, and per default all geometries
defined before the master, but after the previous will be simulated here.

There is a dedicated manual available for the Union_components


Original header text for NCrystal_sample.comp:
McStas sample component for the NCrystal scattering library. Find more
information at <a href="https://github.com/mctools/ncrystal/wiki">the NCrystal
wiki</a>. In particular, browse the available datafiles at <a
href="https://github.com/mctools/ncrystal/wiki/Data-library">Data-library</a>
and read about format of the configuration string expected in the "cfg"
parameter at <a href="https://github.com/mctools/ncrystal/wiki/Using-NCrystal">Using-NCrystal</a>.

<p/>NCrystal is available under the <a href="http://www.apache.org/licenses/LICENSE-2.0">Apache 2.0 license</a>. Depending
on the configuration choices, optional NCrystal modules under different
licenses might be enabled - see <a
href="https://github.com/mctools/ncrystal/wiki/About">About</a> for more
details.

Algorithm:
Described elsewhere
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| cfg | str | NCrystal material configuration string (details <a href="https://github.com/mctools/ncrystal/wiki/Using-NCrystal">on this page</a>). | "" |
| packing_factor | 1 | Material packing factor | 1 |
| interact_fraction | 1 | How large a part of the scattering events should use this process 0-1 (sum of all processes in material = 1) | -1 |
| init | string | Name of Union_init component (typically "init", default) | "init" |

## Links

- [Source code](/Users/peterwillendrup/Projects/willend-McCode/mcstas-comps/union/NCrystal_process.comp) for `NCrystal_process.comp`.

---

*Generated on mcstas 3.99.99.*