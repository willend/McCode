# The `Res_monitor` Component

*McStas: Monitor for resolution calculations*

## Identification

- **Site:** 
- **Author:** Kristian Nielsen
- **Origin:** Risoe
- **Date:** 1999

## Description

```text
A single detector/monitor, used together with the Res_sample component to
compute instrument resolution functions. Outputs a list of neutron
scattering events in the sample along with their intensities in the
detector. The output file may be analyzed with the mcresplot front-end.

Example: Res_monitor(filename="Output.res", res_sample_comp="RSample", xmin=-0.1, xmax=0.1, ymin=-0.1, ymax=0.1)

Setting the monitor geometry.
The optional parameter 'options' may be set as a string with the
following keywords. Default is rectangular ('square'):
box                       Box of size xwidth, yheight, zdepth
cylinder                  To get a cylindrical monitor (diameter is xwidth, height is yheight).
banana                    Same as cylinder, without top/bottom, on restricted angular area
disk                      Disk flat xy monitor. diameter is xwidth.
sphrere                   To get a spherical monitor (e.g. a 4PI) (diameter is xwidth).
square                    Square flat xy monitor (xwidth, yheight)
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| **res_sample_comp** | WITH quotes | Name of Res_sample component in the instrument definition |  |
| filename | string | Name of output file. If unset, use automatic name | 0 |
| options | str | String that specifies the geometry of the monitor | 0 |
| xwidth | m | Width/diameter of detector | .1 |
| yheight | m | Height of detector | .1 |
| zdepth | m | Thichness of detector | 0 |
| radius | m | Radius of sphere/cylinder monitor | 0 |
| xmin | m | Lower x bound of detector opening | 0 |
| xmax | m | Upper x bound of detector opening | 0 |
| ymin | m | Lower y bound of detector opening | 0 |
| ymax | m | Upper y bound of detector opening | 0 |
| zmin | m | Lower z bound of detector opening | 0 |
| zmax | m | Upper z bound of detector opening | 0 |
| bufsize | 1 | Number of events to store. Use 0 to store all | 0 |
| restore_neutron | 1 | If set, the monitor does not influence the neutron state | 0 |
| live_calc | 1 | If set, the monitor directly outputs the resolution matrix | 1 |

## Links

- [Source code](/Users/peterwillendrup/Projects/willend-McCode/mcstas-comps/monitors/Res_monitor.comp) for `Res_monitor.comp`.

---

*Generated on mcstas 3.99.99.*