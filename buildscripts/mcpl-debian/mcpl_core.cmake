#Injected into the MCPL mcpl_core project via
#-DCMAKE_PROJECT_MCPL_INCLUDE=<this file> to add Debian metadata to the mcpl
#package (variables below are not set by MCPL itself, so they take effect).

include( "${CMAKE_CURRENT_LIST_DIR}/mcpl_debian_docs.cmake" )
set( CPACK_DEBIAN_PACKAGE_MAINTAINER "${MCPL_DEB_MAINTAINER}" )
set( CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON )
set( CPACK_DEBIAN_PACKAGE_SECTION "science" )
set( CPACK_DEBIAN_PACKAGE_CONFLICTS "libmcpl-dev" )
set( CPACK_DEBIAN_PACKAGE_REPLACES "libmcpl-dev" )
set( CPACK_DEBIAN_PACKAGE_DESCRIPTION "Library, header files and command-line tools (mcpltool, mcpl-config) for\nthe MCPL (.mcpl) particle list file format." )
set( CPACK_STRIP_FILES ON )
mcpl_install_debian_docs( mcpl "${PROJECT_SOURCE_DIR}/../CHANGELOG" )
