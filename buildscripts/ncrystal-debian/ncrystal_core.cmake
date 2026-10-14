#Injected into the NCrystal ncrystal_core project via
#-DCMAKE_PROJECT_NCrystal_INCLUDE=<this file> to add Debian metadata to the
#ncrystal package (variables below are not set by NCrystal itself, so they take
#effect).

include( "${CMAKE_CURRENT_LIST_DIR}/ncrystal_debian_docs.cmake" )
set( CPACK_DEBIAN_PACKAGE_MAINTAINER "${NCRYSTAL_DEB_MAINTAINER}" )
set( CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON )
set( CPACK_DEBIAN_PACKAGE_SECTION "science" )
#Debian-proper ships the same files in these packages:
set( CPACK_DEBIAN_PACKAGE_CONFLICTS "libncrystal-dev, libncrystal-bin" )
set( CPACK_DEBIAN_PACKAGE_REPLACES "libncrystal-dev, libncrystal-bin" )
set( CPACK_DEBIAN_PACKAGE_DESCRIPTION "Library, header files and the ncrystal-config command for NCrystal, a\nlibrary for thermal neutron transport in crystals and other materials." )
set( CPACK_STRIP_FILES ON )
ncrystal_install_debian_docs( ncrystal "${PROJECT_SOURCE_DIR}/../CHANGELOG" )
