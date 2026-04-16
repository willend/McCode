# The `Progress_bar` Component

*McStas: A simulation progress bar*

## Identification

- **Site:** 
- **Author:** Emmanuel Farhi
- **Origin:** ILL
- **Date:** 2002

## Description

```text
An indicator of the progress of the simulation, monitoring
the Init, Trace with the achieved percentage, and the Finally section.
Intermediate savings (e.g. triggered by USR2 signal) are also shown.
This component should be positioned at the very begining of the instrument
The profile option will save the intensity and number of events for each
component It may be used to evaluate the simulation efficiency.

Example: Progress_bar(percent=10,flag_save=1) AT (0,0,0)
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| profile | str | file name to save the simulation profile if set to "", it is set to the name of the instrument. | "NULL" |
| percent | 0-100 | percentage interval between updates. Default is 10%. | 10 |
| flag_save | 0\|1 | flag to enable intermediate saving for all monitors | 0 |
| minutes | min | time in minutes between updates (Overrides percent flag). | 0 |

## Links

- [Source code](/Users/peterwillendrup/Projects/willend-McCode/mcstas-comps/misc/Progress_bar.comp) for `Progress_bar.comp`.

---

*Generated on mcstas 3.99.99.*