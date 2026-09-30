/*******************************************************************************
*
* McStas, neutron ray-tracing package
*         Copyright (C) 1997-2026, All rights reserved
*         DTU Physics, Kgs. Lyngby, Denmark
*
* Library: share/mccode-ncrystal-lib.h
*
* %Identification
* Written by: Thomas Kittelmann
* Date: 2026
* Origin: ESS
*
* Common functionality for McStas components using NCrystal (NCrystal_sample,
* NCrystal_process, Union_NCrystal_material, PowderN, Single_crystal),
* included with %include "mccode-ncrystal-lib" in a SHARE section. It also
* includes the NCrystal C API (ncrystal.h).
*
*******************************************************************************/

#ifndef MCCODE_NCRYSTAL_LIB_H
#define MCCODE_NCRYSTAL_LIB_H

#if defined(WIN32) || defined(_WIN32)
#include "NCrystal\\ncrystal.h"
#else
#include "NCrystal/ncrystal.h"
#endif

/* Set up NCrystal's search path for data files. To be called before loading
   any NCrystal materials. Calling it more than once has no further effect.

   This adds the same directories to the NCrystal search path as searched by
   Open_File() in read_table-lib (used by most McStas components to find data
   files): the directory of the instrument file, the directory of the
   executable, and the data/ and contrib/ directories of the McStas
   installation. So data files (e.g. "localdata/X.ncmat") are found by NCrystal
   in the same way as other data files. (NCrystal itself already searches
   relative to the current working directory, like Open_File()). */
void mccode_setup_ncrystal_search_paths( void );

#endif
