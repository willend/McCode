#Debian packaging helpers for NCrystal packages built by McCode (see
#build_debs_mcstas*). Only wraps the upstream NCrystal sources, which are left
#untouched.

set( NCRYSTAL_DEB_MAINTAINER "NCrystal developers <ncrystal-developers@cern.ch>" )

#"YYYY-MM-DD" -> "Www, DD Mmm YYYY 00:00:00 +0000" (RFC 2822):
function( _ncrystal_rfc2822_date date outvar )
  if ( NOT date MATCHES "^([0-9]+)-0?([0-9]+)-0?([0-9]+)$" )
    message( FATAL_ERROR "Invalid date in CHANGELOG: ${date}" )
  endif()
  set( y "${CMAKE_MATCH_1}" )
  set( m "${CMAKE_MATCH_2}" )
  set( d "${CMAKE_MATCH_3}" )
  #Day of week (Sakamoto's method, 0=Sunday):
  set( yy "${y}" )
  if ( m LESS 3 )
    math( EXPR yy "${y} - 1" )
  endif()
  math( EXPR mi "${m} - 1" )
  list( GET _ncrystal_t "${mi}" t )
  math( EXPR dow "(${yy} + ${yy}/4 - ${yy}/100 + ${yy}/400 + ${t} + ${d}) % 7" )
  list( GET _ncrystal_wdays "${dow}" wday )
  list( GET _ncrystal_months "${mi}" mon )
  if ( d LESS 10 )
    set( d "0${d}" )
  endif()
  set( "${outvar}" "${wday}, ${d} ${mon} ${y} 00:00:00 +0000" PARENT_SCOPE )
endfunction()
set( _ncrystal_t 0 3 2 5 0 3 5 1 4 6 2 4 )
set( _ncrystal_wdays Sun Mon Tue Wed Thu Fri Sat )
set( _ncrystal_months Jan Feb Mar Apr May Jun Jul Aug Sep Oct Nov Dec )

#Installs a DEP-5 copyright file and a Debian changelog.gz, converted from the
#NCrystal CHANGELOG, into share/doc/<pkgname>:
function( ncrystal_install_debian_docs pkgname changelog )
  set( outdir "${PROJECT_BINARY_DIR}/debian" )
  file( WRITE "${outdir}/copyright"
    "Format: https://www.debian.org/doc/packaging-manuals/copyright-format/1.0/\n"
    "Upstream-Name: NCrystal\nSource: https://github.com/mctools/ncrystal\n\n"
    "Files: *\nCopyright: 2015-2026 NCrystal developers\nLicense: Apache-2.0\n"
    " On Debian systems, the full text of the Apache License, Version 2.0\n"
    " can be found in /usr/share/common-licenses/Apache-2.0.\n" )
  install( FILES "${outdir}/copyright" DESTINATION "share/doc/${pkgname}" )
  find_program( NCRYSTAL_GZIP_CMD gzip )
  if ( NOT NCRYSTAL_GZIP_CMD )
    message( FATAL_ERROR "gzip not found" )
  endif()
  #Entries keep their original indentation (5-8 spaces, varying over the
  #years), which is valid in Debian changelogs (at least 2 spaces needed):
  file( READ "${changelog}" txt )
  string( REGEX REPLACE "[ \n]+$" "" txt "\n\n${txt}" )
  #Release headers are "vX.Y.Z YYYY-MM-DD" (no date if work in progress):
  string( REGEX MATCHALL "\n\nv[0-9][^\n]*\n" headers "${txt}" )
  string( TIMESTAMP today "%Y-%m-%d" UTC )#respects SOURCE_DATE_EPOCH
  set( trailer "" )
  foreach( hdr IN LISTS headers )
    string( REGEX MATCH "v([0-9.]+) +([0-9-]*)" dummy "${hdr}" )
    set( ver "${CMAKE_MATCH_1}" )
    set( date "${CMAKE_MATCH_2}" )
    if ( NOT date )
      set( date "${today}" )
    endif()
    _ncrystal_rfc2822_date( "${date}" date )
    string( REPLACE "${hdr}"
      "${trailer}\n\n${pkgname} (${ver}) unstable; urgency=medium\n\n"
      txt "${txt}" )
    set( trailer "\n\n -- ${NCRYSTAL_DEB_MAINTAINER}  ${date}" )
  endforeach()
  string( REGEX REPLACE "^\n+" "" txt "${txt}${trailer}\n" )
  file( WRITE "${outdir}/changelog" "${txt}" )
  execute_process( COMMAND "${NCRYSTAL_GZIP_CMD}" -9nc "${outdir}/changelog"
    OUTPUT_FILE "${outdir}/changelog.gz" RESULT_VARIABLE rc )
  if ( NOT rc EQUAL 0 )
    message( FATAL_ERROR "Failed to gzip ${outdir}/changelog" )
  endif()
  install( FILES "${outdir}/changelog.gz" DESTINATION "share/doc/${pkgname}" )
endfunction()
