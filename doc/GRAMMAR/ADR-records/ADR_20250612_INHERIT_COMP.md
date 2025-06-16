# New COMPONENT keyword 'INHERIT'

## Status

*Proposed* and prototype *implemented* 

## Context

As discussed in https://github.com/mccode-dev/McCode/discussions/2041,
a recent addition of a 'multi-COPY for flexible mix and match of
COMPONENT sections lead to different syntax / meaning of the COPY
keyword in:
* instruments: `COMPONENT COPY(instance) = COPY(instance)(par1=val1, par2=val2)`
* component sections: `SHARE COPY PowderN COPY Fluorescence`

## Decision

In a zoom meeting on June 11th 2025 it was agreed between  @farhi,
@g5t, @mads-bertelsen, @willend to 
* Keep the `COPY` syntax in instrument files as is
* Stop supporting `COPY` in components, and define a new `INHERIT` keyword for component section copying (mix
  and match as used in e.g.  McXtrace`FluoPowder`)
* Prototype implemented and ready for review in PR https://github.com/mccode-dev/McCode/pull/2062


## Consequences

* Syntax becomes clearer - either `COPY(reference)` with parenthesis in
  instruments or `INHERIT reference` in components.
* Existing components with use of `COPY` must be migrated (already
  done for repo comps in PR.
* User home-grown McStas or McXtrace components will break and need
  migration to `INHERIT`. It is believed that very few - if any - such
  components exist in the wild. 
* Important: `INHERIT` does not ensure that component setting
  parameters used in copied section(s) are copied too. (This to allow
  complete modification of the parameter interface for a "derived" component.) 
* CHANGELOG should be crystal clear on this change / potential incompatibility

## Behaviour

For trivial components `n_part.comp`:

```
DEFINE COMPONENT n_part
SETTING PARAMETERS (int n)
TRACE
%{
  for (int i= 0; i < n; i++) {
    printf("n=%d\\n", i);
  }
%}
END
```
and `m_part.comp`:

```
DEFINE COMPONENT m_part
SETTING PARAMETERS (int m)
TRACE
%{
  for (int i = 0; i < m; i++) {
    printf("m=%d\\n", i);
  }
%}
END
```
a third component can now be defined pulling together sections from each, `both_parts.comp`:

```
DEFINE COMPONENT both_parts
SETTING PARAMETERS (int n, int m)
TRACE INHERIT n_part INHERIT m_part
END
```
Using the third component in a trivial instrument, e.g., `test_both_parts.instr`:

```
define instrument test_both_parts(dummy=0.)
trace
component origin = both_parts(n=3, m=2) at (0, 0, 0) absolute
end
```
will produce runtime output

```
$ mcrun test_both_parts -n 1 dummy=0
n=0
n=1
n=2
m=0
m=1
```
