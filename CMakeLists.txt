cmake_minimum_required(VERSION 2.8.3)
project(rqt_estop)

## Find catkin macros and libraries
find_package(catkin REQUIRED COMPONENTS 
    roscpp
    rqt_gui
    rqt_gui_cpp
    std_msgs
)

if("${qt_gui_cpp_USE_QT_MAJOR_VERSION} " STREQUAL "5 ")
  find_package(Qt5Widgets REQUIRED)
else()
  find_package(Qt4 COMPONENTS QtCore QtGui REQUIRED)
  include(${QT_USE_FILE})
endif()

catkin_python_setup()

catkin_package(
	INCLUDE_DIRS include
	LIBRARIES ${PROJECT_NAME} 
  CATKIN_DEPENDS roscpp rqt_gui rqt_gui_cpp std_msgs
)

set(rqt_estop_SRCS
  src/estop_gui.cpp
)

set(rqt_estop_HDRS
  include/estop_gui.h
)

set(rqt_estop_UIS
  resource/estop_gui.ui
)

if("${qt_gui_cpp_USE_QT_MAJOR_VERSION} " STREQUAL "5 ")
  qt5_wrap_cpp(rqt_estop_MOCS ${rqt_estop_HDRS})
  qt5_wrap_ui(rqt_estop_UIS_H ${rqt_estop_UIS})
else()
  qt4_wrap_cpp(rqt_estop_MOCS ${rqt_estop_HDRS})
  qt4_wrap_ui(rqt_estop_UIS_H ${rqt_estop_UIS})
endif()

include_directories(
  include
  ${CMAKE_CURRENT_BINARY_DIR}
  ${catkin_INCLUDE_DIRS}
)
add_library(${PROJECT_NAME}
  ${rqt_estop_SRCS}
  ${rqt_estop_MOCS}
  ${rqt_estop_UIS_H}
)

target_link_libraries(${PROJECT_NAME}
  ${catkin_LIBRARIES}
)

if("${qt_gui_cpp_USE_QT_MAJOR_VERSION} " STREQUAL "5 ")
  target_link_libraries(${PROJECT_NAME} Qt5::Widgets)
else()
  target_link_libraries(${PROJECT_NAME} ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY})
endif()

find_package(class_loader)
class_loader_hide_library_symbols(${PROJECT_NAME})

add_dependencies(rqt_estop ${catkin_EXPORTED_TARGETS})

install(FILES plugin.xml
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
)

install(TARGETS ${PROJECT_NAME}
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION})

install(PROGRAMS scripts/rqt_estop
  DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

install(DIRECTORY include/${PROJECT_NAME}/
  resource
  DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
)
