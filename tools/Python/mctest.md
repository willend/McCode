[&larr; back to overview](README.md)

# mctest family

Installation testing / benchmarking tools, under `tools/Python/mctest`.

## mctest / mxtest

Runs every `%Example` test embedded in the instrument library, compiling,
displaying (single-particle), and running each one, then compares the
result against the target value recorded in the instrument header.

A `%Scan:` header line works the same way for a parameter scan. The
parameters use the `mcrun` scan syntax, followed by one target value per
scan point, e.g.

    %Scan: dBz=-0.0001,0.0001 -N41 -n1e5 Detector: detector_I=79.2,102.7,...

`mcrun` and `*.instr` tokens on `%Example:`/`%Scan:` lines are ignored. A scan
uses its own `-n` if given, otherwise at most `1e5` per point, and runs its
points in parallel (`--scan_split=auto`) unless MPI is used. A scan passes when
every point is within 20% of its target.

A target may carry its error bar, written as in the simulation's own output, e.g.
`%Example: ... Detector: NAME_I=2.00752e+08 NAME_ERR=2.28872e+06` or, for a scan,
`Detector: NAME_I={...} NAME_ERR={...}`. It is used with `--nsigma`/`--pvalue`.

| Option | Description |
|---|---|
| `--ncount N`, `-n N` | ncount sent to `mcrun` (default: `1e6`) |
| `--seed S`, `-s S` | seed sent to `mcrun` (default: `1000`; `0`/`NULL` randomises) |
| `--mpi N` | MPI node count sent to `mcrun` |
| `--no-mpi` | compile and run without MPI (`--no-mpi` sent to `mcrun`) |
| `--openacc` | pass `--openacc` to `mcrun` |
| `--nexus` | compile/run with NeXus output format everywhere |
| `--lint` | just run the C-linter (no simulation run) |
| `--config CONFIG` | test only this specific config — label name (regex) or absolute path |
| `--instr PATTERN` | test only instruments matching this regex (comma-separated for multiple); together with `--comp`, instruments matching either are tested |
| `--comp COMP[,COMP...]` | test only instruments that use any of the given components (whole-word match) |
| `--mccoderoot DIR` | root search folder for McCode installations |
| `--testdir DIR` | write test results directly into `DIR` (default: cwd) |
| `--local DIR` | pick up instruments to test from `DIR` instead of the McCode installation |
| `--limit N` | test only the first `N` instruments |
| `--skipnontest` | skip compiling instruments that have no `%Example` test |
| `--suffix SUFFIX` | append `SUFFIX` to the test directory name |
| `--uid ID` | unique identifier for the suffix (default: timestamp) |
| `--compilemax S` | max seconds allowed per compilation (default: 1800; x100 with `--lint`) |
| `--runmax S` | max seconds allowed per test run (default: 3600) |
| `--displaymax S` | max seconds allowed per test display run (default: 60) |
| `--nsigma N` | accept a test value (each point of a scan) within N × the combined error bar `sqrt(ERR_test² + ERR_target²)`, when the target line gives `NAME_ERR`; targets without it are assumed to have the test run's ERR (`√2·ERR_test`) and are also accepted within 20 %. Error bars from fewer than 100 effective events `(I/ERR)²` are not used: the 20 % rule applies |
| `--statfactor F` | scale the ncount of every test (and per scan point) by F, e.g. `0.01` for quick runs or `100` for reference-quality ones; with `--nsigma`/`--pvalue`, a target without `NAME_ERR` is assumed to come from the unscaled ncount (combined error bar `√(1+F)·ERR_test`) |
| `--pvalue P` | as `--nsigma`, given as a two-sided Gaussian p-value (e.g. `0.0027` = 3σ, `5.7e-7` = 5σ) |
| `--noscans` | skip the `%Scan` tests, only run the `%Example` tests |
| `--noplots` | do not generate plots (`01_overview.pdf`, `02_plots.html`) of the test output |
| `--permissive` | exit 0 even if some tests fail |
| `--strict` | let instruments without `%Example` line(s) fail immediately (cannot be combined with `--permissive`) |
| `--verbose` | print a test/no-test status header before each test |

## mcviewtest / mxviewtest

Builds a single browsable HTML comparison report from one or more `mctest`
result sets (as written by `mctest --testdir`), diffing/co-plotting each
row against a chosen reference column via `mcplotdiff-html`/`mccoplot-html`.

| Option | Description |
|---|---|
| `testdir` | *(optional)* root folder containing `mctest` result subfolders (default: cwd) |
| `--reflabel LABEL` | reference column/label to compare against (default: oldest subfolder in cwd) |
| `--testroot DIR` | test-root folder for interactive result management/cleanup |
| `--verbose` | output excessive debug information |
| `--nobrowse` | do not open a browser on completion |
| `--nodiff` | do not generate diff/co-plot comparison cells |
| `--diff-errors-only` | only diff rows that show a discrepancy (default: diff every valid row) |
| `--diffmax S` | max seconds per diff/co-plot comparison (default: 300) |
| `--diffworkers N` | number of comparisons to run in parallel (default: number of CPUs) |

---
[&larr; back to overview](README.md)
