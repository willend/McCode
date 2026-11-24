[&larr; back to overview](README.md)

# mcmerge / mxmerge

Merges 2 or more datasets (runs or scans, ASCII or NeXus) into a new one:

```
mcmerge -d OUT [--format McCode|NeXus] [--force] DATASET DATASET ...
```

- Same parameter values: pooled, as if simulated in one run of all rays. Histograms and errors are combined
  from the ray counts, event lists are concatenated with rescaled weights.
- Different parameter values: a new scan. The points of scans with the same values are pooled.

| Option | Description |
|---|---|
| `datasets` | dataset directories, 2 or more |
| `-d`, `--dir OUT` | output directory, must not exist |
| `--format FMT` | `McCode` (ASCII) or `NeXus` (default: as the first dataset) |
| `--force` | merge doubtful datasets anyway |

The output lists its input runs as `Merged_from`. Forced merges are marked with `Merged_forced`: **the result may be wrong**.

## What is refused

| Always | Unless `--force` |
|---|---|
| `OUT` exists, less than 2 datasets | made before McCode 3.10.3 (may be an interrupted run) |
| unreadable data, missing event files | other McCode version, gravitation, trace mode or instrument source |
| interrupted runs, incomplete scans | parameter values that were not recorded |
| other instrument or monitors | overlapping seeds: with MPI, node *i* uses seed+*i* |
| same parameters, but other number of bins or list columns | other limits of a monitor, e.g. `auto` in `Monitor_nD` |
| log of the signal in `Monitor_nD` | intensities that differ by more than 5 sigma |
| | intermediate saves by McCode 3.10.3 or older |
| | event lists without `p` column |

## Not seen by mcmerge

- `signal=` monitors of `Monitor_nD` run with MPI in McCode 3.10.3 or older are wrong.
- Same MCPL input file in all runs: these are not independent, however different the seeds.
- Parameter values that differ beyond the 6 digits recorded.
- NeXus files do not record the number of MPI nodes: keep the seeds at least that far apart.

MCPL files are not merged: use `mcpltool --merge`.
