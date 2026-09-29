/*******************************************************************************
*
*  McXtrace, photon ray-tracing package
*  Copyright(C) 2007 Risoe National Laboratory.
*
* %I
* Written by: Mads Bertelsen
* Date: 20.08.15
* Version: $Revision: 0.1 $
* Origin: University of Copenhagen
*
* A sample component to separate geometry and phsysics
*
* %D
* Alpha version, no input system yet
* Hardcode input to geometry engine
* Allows complicated geometry by combination of simple shapes
*
* Algorithm:
* Described elsewhere
*
* %P
* INPUT PARAMETERS:
* radius:  [m] Outer radius of sample in (x,z) plane
*
* OUTPUT PARAMETERS:
* V_rho:  [AA^-3] Atomic density
*
* %L
* The test/example instrument <a href="../examples/Test_Phonon.instr">Test_Phonon.instr</a>.
*
* %E
******************************************************************************/

#ifndef UNION_INIT_C
#define UNION_INIT_C

// The lists Union components use to communicate now live in the shared Union
// state in union-lib.h (struct union_state_struct), which every Union
// component loads with %include "union-lib". This file is kept empty so that
// a code generator which still embeds it does not define them twice.

#endif /* UNION_INIT_C */
