project(codata)

set (CODATA_VERSION_MAJOR 0)
set (CODATA_VERSION_MINOR 1)
set (CODATA_VERSION_RELEASE 1)
set (CODATA_VERSION "${CODATA_VERSION_MAJOR}.${CODATA_VERSION_MINOR}.${CODATA_VERSION_RELEASE}" )
set (CODATA_VERSION_STRING "${CODATA_VERSION} (0.1 >=20110210)")

include_directories (
${CMAKE_CURRENT_BINARY_DIR}
)

configure_file (
  "${CMAKE_CURRENT_SOURCE_DIR}/version_codata.h.cmake"
  "${CMAKE_CURRENT_BINARY_DIR}/version_codata.h"
  )

add_definitions(-DCODATA_LIBRARY)

set(codata_SRCS
  codata.cpp
)
set(codata_HEADERS
  codata.h
)

qt4_wrap_cpp(codata_HEADERS_MOC ${codata_HEADERS})


add_library(CoData ${LIBRARY_TYPE} ${codata_SRCS} ${codata_HEADERS_MOC})
target_link_libraries(CoData ${QT_LIBRARIES})
