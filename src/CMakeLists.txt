include_directories (
${CMAKE_CURRENT_BINARY_DIR}
${CMAKE_CURRENT_SOURCE_DIR}/gui
${COMBIT_COGIT_INCLUDES}
${COMBIT_CODATA_INCLUDES}
)

configure_file (
  "${CMAKE_CURRENT_SOURCE_DIR}/version_combit.h.cmake"
  "${CMAKE_CURRENT_BINARY_DIR}/version_combit.h"
  )

add_subdirectory(cogit)
add_subdirectory(codata)

set(combit_SRCS
  main.cpp
  gui/comainwindow.cpp
)
set(combit_MOC_SRCS
  gui/comainwindow.h
)
set(combit_UIS
  gui/comainwindow.ui
)
set(combit_RCCS
  combit.qrc
)

qt4_wrap_cpp(combit_MOCS ${combit_MOC_SRCS})
qt4_wrap_ui(combit_UIS_H ${combit_UIS})
qt4_wrap_cpp(combit_MOC_UI ${combit_UIS_H})
qt4_add_resources(combit_RCCS_SRCS ${combit_RCCS})
add_definitions(-DQT_NO_DEBUG)

add_executable (Combit
  ${combit_SRCS}
  ${combit_MOCS}
  ${combit_MOC_UI}
  ${combit_RCCS_SRCS}
)
target_link_libraries (Combit CoGit CoData ${QT_LIBRARIES})