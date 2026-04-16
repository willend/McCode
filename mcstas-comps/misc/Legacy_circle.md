# The `Legacy_circle` Component

*McStas: A geometric shape without effect on neutron, for instrument display purpose.*

## Identification

- **Site:** 
- **Author:** E. Farhi
- **Origin:** ILL
- **Date:** June 23rd 2009

## Description

```text
An inactive geometrical shape, for drawing purposes only.
It does not propagate neutron, nor interact.
<b>Shape:</b>
Geometric shape may be a cylinder, a sphere, a box or any other shape
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
It supports the OFF and NOFF file format but not COFF (colored faces).
Such files may be generated from XYZ data using qhull/powercrust, and
viewed with geomview
The default size of the object depends of the OFF file data, but its
bounding box may be resized using xwidth,yheight and zdepth.

Example: Shape(radius=0.05, yheight=0.1)
Shape(geometry="socket.off")
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| radius | m | Outer radius of sample in (x,z) plane | 0 |

## Links

- [Source code](/Users/peterwillendrup/Projects/willend-McCode/mcstas-comps/misc/Legacy_circle.comp) for `Legacy_circle.comp`.
- Geomview and Object File Format (OFF) <http|://www.geomview.org>
- Powercrust/qhull <http://www.cs.utexas.edu/users/amenta/powercrust>

---

*Generated on mcstas 3.99.99.*