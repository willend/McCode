#Packages the pure-Python mcpl module and the pymcpltool command from an MCPL
#checkout as the Debian package python3-mcpl. Configure with
#-DMCPL_PYTHON_SRC=<mcpl checkout>/mcpl_python.

cmake_minimum_required(VERSION 3.16...4.4)

file( STRINGS "${MCPL_PYTHON_SRC}/src/mcpl/__init__.py" _v
  REGEX "^__version__ *= *'[0-9.]+'" )
string( REGEX MATCH "[0-9.]+" _v "${_v}" )

project( MCPLPython VERSION ${_v} LANGUAGES NONE
  DESCRIPTION "Utilities and API for accessing MCPL (.mcpl) files"
  HOMEPAGE_URL "https://github.com/mctools/mcpl"
)

include( "${PROJECT_SOURCE_DIR}/../mcpl_debian_docs.cmake" )

install( DIRECTORY "${MCPL_PYTHON_SRC}/src/mcpl"
  DESTINATION "lib/python3/dist-packages"
  PATTERN "__pycache__" EXCLUDE
)

#Use the pymcpltool entry point from pyproject.toml (it differs between MCPL
#versions):
file( STRINGS "${MCPL_PYTHON_SRC}/pyproject.toml" _ep REGEX "^pymcpltool *=" )
if ( NOT _ep MATCHES "\"([A-Za-z0-9_.]+):([A-Za-z0-9_]+)\"" )
  message( FATAL_ERROR "pymcpltool entry point not found in pyproject.toml" )
endif()
file( WRITE "${PROJECT_BINARY_DIR}/pymcpltool"
  "#!/usr/bin/python3\nfrom ${CMAKE_MATCH_1} import ${CMAKE_MATCH_2}\n${CMAKE_MATCH_2}()\n" )
install( PROGRAMS "${PROJECT_BINARY_DIR}/pymcpltool" DESTINATION bin )

mcpl_install_debian_docs( python3-mcpl "${MCPL_PYTHON_SRC}/../CHANGELOG" )

set( CPACK_PACKAGE_NAME "python3-mcpl" )
set( CPACK_DEBIAN_PACKAGE_MAINTAINER "${MCPL_DEB_MAINTAINER}" )
set( CPACK_DEBIAN_PACKAGE_ARCHITECTURE "all" )
set( CPACK_DEBIAN_PACKAGE_SECTION "python" )
#Mirrors dependencies and optional-dependencies in pyproject.toml:
set( CPACK_DEBIAN_PACKAGE_DEPENDS "python3 (>= 3.9), python3-numpy (>= 1:1.22)" )
set( CPACK_DEBIAN_PACKAGE_RECOMMENDS "mcpl (= ${PROJECT_VERSION})" )
set( CPACK_DEBIAN_PACKAGE_SUGGESTS "python3-matplotlib, python3-plotly" )
set( CPACK_DEBIAN_PACKAGE_DESCRIPTION "Python module (mcpl) and the pymcpltool command for reading, writing,\ninspecting and plotting MCPL (.mcpl) particle list files." )
#Byte-compile on install and clean up on removal (like dh_python3 does):
file( WRITE "${PROJECT_BINARY_DIR}/debian/postinst"
  "#!/bin/sh\nset -e\nif command -v py3compile >/dev/null 2>&1; then\n"
  "  py3compile -p python3-mcpl\nfi\n" )
file( WRITE "${PROJECT_BINARY_DIR}/debian/prerm"
  "#!/bin/sh\nset -e\nif command -v py3clean >/dev/null 2>&1; then\n"
  "  py3clean -p python3-mcpl\nfi\n" )
set( CPACK_DEBIAN_PACKAGE_CONTROL_STRICT_PERMISSION ON )
set( CPACK_DEBIAN_PACKAGE_CONTROL_EXTRA
  "${PROJECT_BINARY_DIR}/debian/postinst;${PROJECT_BINARY_DIR}/debian/prerm" )
include(CPack)
