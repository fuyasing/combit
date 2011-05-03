project(combit)

###---cmake related--------------
cmake_minimum_required (VERSION 2.6)

###---basic info settings--------
set (COMBIT_VERSION_MAJOR 0)
set (COMBIT_VERSION_MINOR 1)
set (COMBIT_VERSION_RELEASE 1)
set (COMBIT_VERSION "${COMBIT_VERSION_MAJOR}.${COMBIT_VERSION_MINOR}.${COMBIT_VERSION_RELEASE}" )
set (COMBIT_VERSION_STRING "${COMBIT_VERSION} (0.1 >=20110210)")

set (COMBIT_WEBSITE "http://combit.combinz.com")

###---qt check and config-----------
find_package(Qt4 4.6.0 COMPONENTS QtCore QtGui QtNetwork REQUIRED)
if(QT4_FOUND)
  set(COMBIT_CAN_BE_COMPILED true)
else(QT4_FOUND)
  set(COMBIT_CAN_BE_COMPILED false)
endif(QT4_FOUND)

include(${QT_USE_FILE})

###---lib config---------
option(STATIC_LIBRARY "Build cogit as static libraries." FALSE)

if(STATIC_LIBRARY)
  set(LIBRARY_TYPE STATIC)
  message(STATUS "Building cogit as static libraries")
else(STATIC_LIBRARY)
  set(LIBRARY_TYPE SHARED)
endif(STATIC_LIBRARY)

###---set include dirs---------
set(COMBIT_COGIT_INCLUDES
${CMAKE_SOURCE_DIR}/src/cogit
)
set(COMBIT_CODATA_INCLUDES
${CMAKE_SOURCE_DIR}/src/codata
)

###---set output path----------
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

###---project file-------------
if(COMBIT_CAN_BE_COMPILED)
  add_subdirectory(src)
  add_subdirectory(doc)
endif(COMBIT_CAN_BE_COMPILED)
