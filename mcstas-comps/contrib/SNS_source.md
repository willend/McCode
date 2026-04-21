# The `SNS_source` Component

*McStas: Modified: G. E. Granroth  Nov 2014 Move to Mcstas V2
Modified: J.Y.Y. Lin April 2021 to Fix race condition
Modified: P. WIllendrup 2021 Move to Move to Mcstas Version 3 and enable GPus

A source that produces a time and energy distribution from the SNS moderator files*

## Identification

- **Site:** 
- **Author:** G. Granroth
- **Origin:** SNS Project Oak Ridge National Laboratory
- **Date:** July 2004

## Description

```text
Produces a time-of-flight spectrum from SNS moderator files
moderator files can be obtained from the <A href="http://www.sns.gov/users/instrument_systems/components/moderator/">SNS website </A>.
<strong>IMPORTANT: The output units of this component are N/pulse</strong>
<strong>IMPORTANT: The component needs a FULL PATH to the source input file</strong>
Notes:
(1) the raw moderator files are per Sr.  The focusing parameters provide the solid
angle accepted by the guide to remove the Sr dependence from the output. Therefore
the best practice is to set focus_xw and focus_yh to the width and height of the next beam
component, respectively. The dist parameter should then be set as the distance
from the moderator to the first component.
(2) This component works purely by interpolation. Therefore be sure that Emin and
Emax are within the limits of the moderator file
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| **filename** |  | Filename of source data |  |
| xwidth | m | width of moderator | 0.1 |
| yheight | m | height of moderator | 0.12 |
| **dist** | m | Distance from source to the focusing rectangle |  |
| **focus_xw** | m | Width of focusing rectangle |  |
| **focus_yh** | m | Height of focusing rectangle |  |
| **Emin** | meV | minimum energy of neutron to generate |  |
| **Emax** | meV | maximum energy of neutron to generate |  |

## Links

- [Source code](SNS_source.comp) for `SNS_source.comp`.

---

*Generated on mcstas 3.99.99.*