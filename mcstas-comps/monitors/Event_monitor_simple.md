# The `Event_monitor_simple` Component

*McStas: Low-key event-monitor for debugging purposes.*

## Identification

- **Site:** 
- **Author:** Peter Willendrup
- **Origin:** DTU
- **Date:** Oct 3rd, 2020

## Description

```text
Simple, low-key event-monitor for debugging purposes. No propagation,
no MPI support. Simply prints the event list to a log file in the SAVE section.
The filename is "comp-instance".log
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| nevents | 1 | Number of events to store and print | 1e6 |

## Links

- [Source code](/Users/peterwillendrup/Projects/willend-McCode/mcstas-comps/monitors/Event_monitor_simple.comp) for `Event_monitor_simple.comp`.

---

*Generated on mcstas 3.99.99.*