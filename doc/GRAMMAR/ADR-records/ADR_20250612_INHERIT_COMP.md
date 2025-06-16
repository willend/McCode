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
* CHANGELOG should be crystal clear on this change / potential incompatibility
