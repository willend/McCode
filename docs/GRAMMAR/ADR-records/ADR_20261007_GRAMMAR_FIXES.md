# Grammar consistency fixes from code-generator review

## Status

*Proposed* and *implemented* on branch `cogen-improve-comments-review`
(follows the comment-only commit b478b4e32).

## Context

A review of the code generator (`mccode/src/instrument.l`,
`instrument.y`, `cogen.c.in`) found places where accepted syntax did
not behave as documented or intended. A few crashed the generator; others
silently produced wrong simulations. None of these is a new feature: each
change makes the existing grammar do what it already claims to do, or
turns silent misbehaviour into an error.

The most serious one concerns the `INHERIT` keyword
(see [ADR_20250612_INHERIT_COMP](ADR_20250612_INHERIT_COMP.md)):
`DEFINE COMPONENT X INHERIT Y` with no sections of its own produced a
component *without any code*. The shipped `Diaphragm` (`INHERIT Slit`)
and `Place` (`INHERIT Arm`) were therefore no-ops in both McStas and
McXtrace. A Diaphragm let the full beam through: a test monitor behind
it read about 16x the intensity measured behind the equivalent Slit.

## Decision

Fix the following in the generator. No new keywords are introduced.

1. **Whole-component `INHERIT`**: a code section that `X` leaves empty is
   taken from `Y`. Parameter lists keep being concatenated (unchanged).
   `SHARE` is emitted once per code block, so `X` and `Y` in the same
   instrument do not duplicate the shared code.
2. **`JUMP PREVIOUS[(n)]` / `NEXT[(n)]`** are resolved relative to the
   jumping component, as documented. A target that does not exist (an
   unknown name, or out of range) is an error.
3. **`MYSELF` in the actual parameters** of a component instance is an
   error. It remains valid from `WHEN` onwards (`WHEN`, `AT`, `ROTATED`,
   `JUMP`, ...), where the instance is known.
4. **Component `USERVARS ... EXTEND %{ %}`**: the `EXTEND` blocks are
   kept, as for all other sections.
5. **`COPY(...)` of an undefined instance**, and an **unknown component
   class**, are reported as errors (both previously crashed the generator).
6. **`%include "file.ext"` inside C blocks** accepts any alphanumeric
   extension (e.g. `.hpp`), not only one-character ones. Names without an
   extension are still treated as libraries (`lib.h` + `lib.c`).
7. **`DECLARE` / `USERVARS` scanning** recognises several declarations
   on one line (`double a; double b;`).
8. **`USERVARS` read through `particle_getvar()`** (e.g. Monitor_nD
   `user1="var"`): numeric scalars are converted to `double` instead of
   having their memory read as a `double`. Arrays, pointers and structs
   report failure. USERVARS used with Monitor_nD should still be declared
   `double`.
9. **Literal vector parameters** (`par={1.0, 0.0219, ...}`) are written
   to the generated C with full double precision instead of `%g`
   (6 significant digits).

## Consequences

* Instruments using `Diaphragm` or `Place`, or user components built as
  `DEFINE COMPONENT X INHERIT Y`, **change results**: they now behave like
  their parent. This is the intended behaviour, but CHANGELOG should say
  so clearly. No shipped example instrument uses Diaphragm.
* `StatisticalChopper_Monitor` now also works in instruments that do not
  contain a `Monitor_nD`.
* Instruments that used `JUMP PREVIOUS` (generator crash) or `JUMP NEXT`
  (jumped to the first component) now work. Instruments that used
  `MYSELF` in component parameters, or `JUMP` to a non-existent target,
  now fail to generate with an error message. No shipped instrument does
  either.
* Vector literals with more than 6 significant digits shift by at most
  5e-6 relative. A worst-case test (all `Pol_mirror` reflectivity
  parameters given 8 digits) showed no change in monitor output. Shipped
  literals are reproduced exactly.
* All other shipped instruments are unaffected. All 332 McStas and 112
  McXtrace examples generate the same code as before, apart from
  cosmetic lines and the `particle_getvar()` casts. Representative
  JUMP/SPLIT/GROUP/USERVARS/Union/xraylib test instruments give identical
  results.

## Behaviour

Relative JUMP (`c` is component 3 of `a, b, c, d`):

```
COMPONENT c = Arm() AT (0,0,1) RELATIVE b
  JUMP PREVIOUS WHEN (cond)   /* goes to b (before: generator crash)  */
  JUMP NEXT WHEN (cond)       /* goes to d (before: went to a)        */
  JUMP NEXT(2) WHEN (cond)    /* error: no component 5                */
```

`MYSELF` only after the parameter list:

```
COMPONENT s = Slit(xwidth=MYSELF)              /* error                  */
COMPONENT s = Slit(xwidth=0.1) WHEN (MYSELF)   /* ok, MYSELF -> s        */
```

Whole-component inheritance:

```
DEFINE COMPONENT Diaphragm INHERIT Slit
END
/* now has Slit's INITIALIZE/TRACE/DISPLAY; before it had none */
```
