# The `Incoherent` Component

*McStas: Incoherent sample (such as Vanadium) sample, with quasielastic component OR or global energy transfer.*

## Identification

- **Site:** 
- **Author:** Kim Lefmann and Kristian Nielsen
- **Origin:** Risoe
- **Date:** 15.4.98

## Description

```text
A Double-cylinder shaped incoherent scatterer (like Vanadium)
with both elastic and quasielastic (Lorentzian) components.
No multiple scattering (but approximation available). Absorption included.
<b>Sample focusing:</b>
The area to scatter to is a disk of radius 'focus_r' situated at the target.
This target area may also be rectangular if specified focus_xw and focus_yh
or focus_aw and focus_ah, respectively in meters and degrees.
The target itself is either situated according to given coordinates (x,y,z),
or defined with the relative target_index of the component to focus
to (next is +1).
This target position will be set to its AT position. When targeting to
centered components, such as spheres or cylinders, define an Arm component
where to focus to.
<b>Sample shape:</b>
Sample shape may be a cylinder, a sphere, a box or any other shape
box/plate:       xwidth x yheight x zdepth (thickness=0)
hollow box/plate:xwidth x yheight x zdepth and thickness>0
cylinder:        radius x yheight (thickness=0)
hollow cylinder: radius x yheight and thickness>0
sphere:          radius (yheight=0 thickness=0)
hollow sphere:   radius and thickness>0 (yheight=0)
any shape:       geometry=OFF file

The complex geometry option handles any closed non-convex polyhedra.
It computes the intersection points of the neutron ray with the object
transparently, so that it can be used like a regular sample object.
It supports the PLY, OFF and NOFF file format but not COFF (colored faces).
Such files may be generated from XYZ data using:
qhull < coordinates.xyz Qx Qv Tv o > geomview.off
or
powercrust coordinates.xyz
and viewed with geomview or java -jar jroff.jar (see below).
The default size of the object depends of the OFF file data, but its
bounding box may be resized using xwidth,yheight and zdepth.

Example: Incoherent(radius=0.05,focus_r=0.035, pack=1, target_index=1)
Incoherent(geometry="socket.off",focus_r=0.035, pack=1, target_index=1)
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| geometry | str | Name of an Object File Format (OFF) or PLY file for complex geometry. The OFF/PLY file may be generated from XYZ coordinates using qhull/powercrust | 0 |
| radius | m | Outer radius of sample in (x,z) plane | 0 |
| xwidth | m | Horiz. dimension of sample (bounding box if off file), as a width | 0 |
| yheight | m | Vert.  dimension of sample (bounding box if off file), as a height. A sphere shape is used when 0 and radius is set | 0 |
| zdepth | m | Depth of sample (bounding box if off file) | 0 |
| thickness | m | Thickness of hollow sample | 0 |
| target_x |  |  | 0 |
| target_y | m | position of target to focus at | 0 |
| target_z |  |  | 0 |
| focus_r | m | Radius of disk containing target. Use 0 for full space | 0 |
| focus_xw | m | horiz. dimension of a rectangular area | 0 |
| focus_yh | m | vert.  dimension of a rectangular area | 0 |
| focus_aw | deg | horiz. angular dimension of a rectangular area | 0 |
| focus_ah | deg | vert.  angular dimension of a rectangular area | 0 |
| target_index | 1 | Relative index of component to focus at, e.g. next is +1 | 0 |
| pack | 1 | Packing factor | 1 |
| p_interact | 1 | MC Probability for scattering the ray; otherwise transmit | 1 |
| f_QE | 1 | Fraction of quasielastic scattering (rest is elastic) | 0 |
| gamma | 1 | Lorentzian width of quasielastic broadening (HWHM) | 0 |
| Etrans | meV | Global energy-transfer, for use in inelastic settings | 0 |
| deltaE | meV | Width in energy around Etrans, for use in inelastic settings | 0 |
| sigma_abs | barns | Absorption cross section pr. unit cell at 2200 m/s | 5.08 |
| sigma_inc | barns | Incoherent scattering cross section pr. unit cell | 5.08 |
| Vc | AA^3 | Unit cell volume | 13.827 |
| concentric | 1 | Indicate that this component has a hollow geometry and may contain other components. It should then be duplicated after the inside part (only for box, cylinder, sphere) | 0 |
| order | 1 | Limit multiple scattering up to given order 0 means all (default), 1 means single, 2 means double, ... | 0 |

## Links

- [Source code](/Users/peterwillendrup/Projects/willend-McCode/mcstas-comps/samples/Incoherent.comp) for `Incoherent.comp`.
- <a href="http://www.ncnr.nist.gov/resources/n-lengths/">Cross sections for single elements</a>
- <a href="http://www.ncnr.nist.gov/resources/sldcalc.html>Cross sections for compounds</a>
- <a href="http://www.webelements.com/">Web Elements</a>
- <A HREF="http://neutron.risoe.dk/mcstas/components/tests/Incoherent/">Test
- results</A> (not up-to-date).
- The test/example instrument <a href="../examples/vanadium_example.instr">vanadium_example.instr</a>.
- The test/example instrument <a href="../examples/QENS_test.instr">QENS_test.instr</a>.
- <a href="http://www.geomview.org">Geomview and Object File Format (OFF)</a>
- Java version of Geomview (display only) <a href="http://www.holmes3d.net/graphics/roffview/">jroff.jar</a>
- <a href="http://qhull.org">qhull</a>
- <a href="http://www.cs.ucdavis.edu/~amenta/powercrust.html">powercrust</a>

---

*Generated on mcstas 3.99.99.*