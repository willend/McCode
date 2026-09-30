/*******************************************************************************
*
* McStas, neutron ray-tracing package
*         Copyright (C) 1997-2026, All rights reserved
*         DTU Physics, Kgs. Lyngby, Denmark
*
* Library: share/mccode-ncrystal-lib.c
*
* %Identification
* Written by: Thomas Kittelmann
* Date: 2026
* Origin: ESS
*
* Common functionality for McStas components using NCrystal. See
* mccode-ncrystal-lib.h.
*
*******************************************************************************/

#ifndef MCCODE_NCRYSTAL_LIB_H
#include "mccode-ncrystal-lib.h"
#endif

/* Same default as in read_table-lib.h: */
#ifndef MCSTAS
#ifdef WIN32
#define MCSTAS "C:\\mcstas\\lib"
#else
#define MCSTAS "/usr/local/lib/mcstas"
#endif
#endif

/* Absolute path of dir, with "." and ".." components resolved, and without
   repeated or trailing path separators (used to detect directories added more
   than once, and for printing). Returns 0 on failure. */
static int
mccode_ncrystal_normalise_dir (const char* dir, char* out, size_t out_size) {
  char tmp[2048];
  char cwd[1024];
  const char* c = tmp;
  size_t n = 0, len;
  if (dir[0] == '/' || dir[0] == MC_PATHSEP_C || (dir[0] && dir[1] == ':')) {
    snprintf (tmp, sizeof (tmp), "%s", dir);
  } else {
    if (!getcwd (cwd, sizeof (cwd)))
      return 0;
    snprintf (tmp, sizeof (tmp), "%s%c%s", cwd, MC_PATHSEP_C, dir);
  }
  /* Keep a Windows drive letter ("C:"), then add the components one by one: */
  if (tmp[0] && tmp[1] == ':') {
    out[n++] = tmp[0];
    out[n++] = ':';
    c += 2;
  }
  while (*c) {
    while (*c == '/' || *c == MC_PATHSEP_C)
      ++c;
    for (len = 0; c[len] && c[len] != '/' && c[len] != MC_PATHSEP_C; ++len)
      ;
    if (len == 0 || (len == 1 && c[0] == '.')) {
      /* nothing to add */
    } else if (len == 2 && c[0] == '.' && c[1] == '.') {
      while (n > 0 && out[n - 1] != MC_PATHSEP_C)
        --n; /* remove the last component */
      if (n > 0 && !(n == 1 || (n == 3 && out[1] == ':')))
        --n; /* and its separator (except for the root directory) */
    } else {
      if (n + len + 2 >= out_size)
        return 0;
      if (n == 0 || out[n - 1] != MC_PATHSEP_C)
        out[n++] = MC_PATHSEP_C;
      memcpy (out + n, c, len);
      n += len;
    }
    c += len;
  }
  if (n == 0 || (n == 2 && out[1] == ':'))
    out[n++] = MC_PATHSEP_C; /* root directory */
  out[n] = '\0';
  return 1;
}

/* Add an existing directory to the NCrystal search path, unless already added: */
static void
mccode_ncrystal_add_search_dir (const char* dir, char* added, size_t added_size) {
  static char done[4][1024];
  static int ndone = 0;
  char norm[1024];
  int i;
  DIR* handle = opendir (dir);
  if (!handle)
    return;
  closedir (handle);
  if (!mccode_ncrystal_normalise_dir (dir, norm, sizeof (norm)))
    return;
  for (i = 0; i < ndone; ++i)
    if (!strcmp (done[i], norm))
      return;
  if (ndone < 4)
    strcpy (done[ndone++], norm);
  ncrystal_add_custom_search_dir (dir);
  if (strlen (added) + strlen (norm) + 3 < added_size) {
    if (added[0])
      strcat (added, ", ");
    strcat (added, norm);
  }
}

/* Add the directory part of a file path (up to and including the last path
   separator), in the same way as Open_File() does it: */
static void
mccode_ncrystal_add_dir_of (const char* file, char* added, size_t added_size) {
  char dir[1024];
  const char* path_pos;
  size_t path_length;
  if (!file || file[0] == '\0')
    return;
  path_pos = strrchr (file, MC_PATHSEP_C);
  if (!path_pos)
    return;
  path_length = path_pos + 1 - file;
  if (path_length >= sizeof (dir))
    return;
  strncpy (dir, file, path_length);
  dir[path_length] = '\0';
  mccode_ncrystal_add_search_dir (dir, added, added_size);
}

void
mccode_setup_ncrystal_search_paths (void) {
  /* NB: This must add the same directories, in the same order, as searched by
     Open_File() in read_table-lib.c. Please keep the two in sync. */
  static int done = 0;
  char dir[1024];
  char added[4096];
  const char* mcstas_dir;

  if (done)
    return;
  done = 1;
  added[0] = '\0';

  mccode_ncrystal_add_dir_of (instrument_source, added, sizeof (added));
  mccode_ncrystal_add_dir_of (instrument_exe, added, sizeof (added));

  mcstas_dir = getenv ("MCSTAS") ? getenv ("MCSTAS") : MCSTAS;
  snprintf (dir, sizeof (dir), "%s%c%s", mcstas_dir, MC_PATHSEP_C, "data");
  mccode_ncrystal_add_search_dir (dir, added, sizeof (added));
  snprintf (dir, sizeof (dir), "%s%c%s", mcstas_dir, MC_PATHSEP_C, "contrib");
  mccode_ncrystal_add_search_dir (dir, added, sizeof (added));

  if (added[0])
    MPI_MASTER (printf ("NCrystal: Added to the NCrystal search path: %s\n", added););
}
