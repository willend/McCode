#Packages the pure-Python NCrystal module and its command-line scripts from an
#NCrystal checkout as the Debian package python3-ncrystal. Configure with
#-DNCRYSTAL_PYTHON_SRC=<ncrystal checkout>/ncrystal_python.

cmake_minimum_required(VERSION 3.16...4.4)

file( STRINGS "${NCRYSTAL_PYTHON_SRC}/src/NCrystal/__init__.py" _v
  REGEX "^__version__ *= *'[0-9.]+'" )
string( REGEX MATCH "[0-9.]+" _v "${_v}" )

project( NCrystalPython VERSION ${_v} LANGUAGES NONE
  DESCRIPTION "Library for thermal neutron transport in crystals and other materials"
  HOMEPAGE_URL "https://github.com/mctools/ncrystal"
)

include( "${PROJECT_SOURCE_DIR}/../ncrystal_debian_docs.cmake" )

install( DIRECTORY "${NCRYSTAL_PYTHON_SRC}/src/NCrystal"
  DESTINATION "lib/python3/dist-packages"
  PATTERN "__pycache__" EXCLUDE
)

#One script per entry point in [project.scripts] of pyproject.toml:
file( STRINGS "${NCRYSTAL_PYTHON_SRC}/pyproject.toml" _eps
  REGEX "^[A-Za-z0-9_-]+ *= *\"[A-Za-z0-9_.]+:[A-Za-z0-9_]+\"" )
if ( NOT _eps )
  message( FATAL_ERROR "No script entry points found in pyproject.toml" )
endif()
foreach( _ep IN LISTS _eps )
  string( REGEX MATCH "^([A-Za-z0-9_-]+) *= *\"([A-Za-z0-9_.]+):([A-Za-z0-9_]+)\"" dummy "${_ep}" )
  file( WRITE "${PROJECT_BINARY_DIR}/scripts/${CMAKE_MATCH_1}"
    "#!/usr/bin/python3\nfrom ${CMAKE_MATCH_2} import ${CMAKE_MATCH_3}\n${CMAKE_MATCH_3}()\n" )
  install( PROGRAMS "${PROJECT_BINARY_DIR}/scripts/${CMAKE_MATCH_1}" DESTINATION bin )
endforeach()

ncrystal_install_debian_docs( python3-ncrystal "${NCRYSTAL_PYTHON_SRC}/../CHANGELOG" )

set( CPACK_PACKAGE_NAME "python3-ncrystal" )
set( CPACK_DEBIAN_PACKAGE_MAINTAINER "${NCRYSTAL_DEB_MAINTAINER}" )
set( CPACK_DEBIAN_PACKAGE_ARCHITECTURE "all" )
set( CPACK_DEBIAN_PACKAGE_SECTION "python" )
#The module locates libNCrystal via ncrystal-config and requires the very same
#version. Other dependencies mirror pyproject.toml (endf-parserpy, needed only
#for ncrystal_ncmat2endf, is not available in Debian):
set( CPACK_DEBIAN_PACKAGE_DEPENDS
  "ncrystal (= ${PROJECT_VERSION}), python3 (>= 3.8), python3-numpy (>= 1:1.22)" )
set( CPACK_DEBIAN_PACKAGE_SUGGESTS
  "python3-matplotlib, python3-spglib, python3-ase, python3-gemmi" )
#Debian-proper ships nctool etc. in this package:
set( CPACK_DEBIAN_PACKAGE_CONFLICTS "libncrystal-bin" )
set( CPACK_DEBIAN_PACKAGE_REPLACES "libncrystal-bin" )
set( CPACK_DEBIAN_PACKAGE_DESCRIPTION "Python module (NCrystal) and command-line tools (ncrystal, nctool,\nncrystal_cif2ncmat, ...) for NCrystal." )
#Byte-compile on install and clean up on removal (like dh_python3 does):
file( WRITE "${PROJECT_BINARY_DIR}/debian/postinst"
  "#!/bin/sh\nset -e\nif command -v py3compile >/dev/null 2>&1; then\n"
  "  py3compile -p python3-ncrystal\nfi\n" )
file( WRITE "${PROJECT_BINARY_DIR}/debian/prerm"
  "#!/bin/sh\nset -e\nif command -v py3clean >/dev/null 2>&1; then\n"
  "  py3clean -p python3-ncrystal\nfi\n" )
set( CPACK_DEBIAN_PACKAGE_CONTROL_STRICT_PERMISSION ON )
set( CPACK_DEBIAN_PACKAGE_CONTROL_EXTRA
  "${PROJECT_BINARY_DIR}/debian/postinst;${PROJECT_BINARY_DIR}/debian/prerm" )
include(CPack)
