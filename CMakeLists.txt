cmake_minimum_required(VERSION 3.7)

project(Widgets VERSION 0.1.0 LANGUAGES CXX)

add_library(${PROJECT_NAME} "")
add_library(Widgets::Widgets ALIAS Widgets)

find_package(Qt6
  REQUIRED
  COMPONENTS
    Core
    Gui
    Widgets
    Network
    Xml
    Svg
    LinguistTools
  OPTIONAL_COMPONENTS
    Core5Compat
#  PATHS
#    /opt/Qt/6.4.1/gcc_64/lib
)
if (NOT Qt6_FOUND)
    find_package(Qt5
      REQUIRED
      COMPONENTS
        Core
        Gui
        Widgets
        Network
        Xml
        Svg
        LinguistTools
#      PATHS
#        /opt/Qt/5.15.2/gcc_64/lib
    )
endif()

qt_standard_project_setup()

## add option to disable examples executables
#option(SMLIBRARIES_BUILD_EXAMPLES "Build SMLibraries examples" OFF)

#if(SMLIBRARIES_BUILD_EXAMPLES)
#  message("SMLibraries examples on")
#  add_subdirectory(examples)
#endif()

target_include_directories(${PROJECT_NAME}
    PUBLIC 
        include
#        $<INSTALL_INTERFACE:include>
#        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_compile_options(${PROJECT_NAME}
    PRIVATE 
        -Werror
#        -DCMAKE_PREFIX_PATH=/opt/Qt/
)

target_sources(
    ${PROJECT_NAME}

  PRIVATE
    # These have to be added to get MOC to work correctly apparently
    # Not certain if there is a better way - yet.

    #  colordialog.h
    include/widget_global.h
    include/widgets/extendedcolordialog.h
    include/single/qsinglemainwindow.h
    include/single/qsinglecoreapplication.h


    include/layout/borderlayout.h
    # end of MOC shit

    # Singleton applications
    src/single/qsinglecoreapplication.cpp
    src/single/qsinglemainwindow.cpp

    # borderlayout Qt example
    src/layout/borderlayout.cpp

    #  colordialog.cpp
    src/widgets/extendedcolordialog.cpp

    # extended color dialog
    src/widgets/extendedcolordialog.cpp

    src/widgets/icons.qrc
    src/widgets/fonts.qrc

)

target_compile_features(${PROJECT_NAME}
    PRIVATE 
        cxx_std_17
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC
        Qt${QT_VERSION_MAJOR}::Core
        Qt${QT_VERSION_MAJOR}::Widgets
    PRIVATE
        Qt${QT_VERSION_MAJOR}::Gui
        Qt${QT_VERSION_MAJOR}::Network
        Qt${QT_VERSION_MAJOR}::Xml
        Qt${QT_VERSION_MAJOR}::Svg

        CuteLogger
        Utilities::Utilities
        Docker::Docker
        QLNPlainText::QLNPlainText
)

option(BUILD_DOC "Build documentation" ON)
find_package(Doxygen)
if (DOXYGEN_FOUND)
  # Only build documentation when building in Release mode
  if (CMAKE_BUILD_TYPE MATCHES "^[Rr]elease")
    # set input and output files
    set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/doxygen/Doxyfile.in)
    set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

    # request to configure the file
    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
    message("Doxygen build started")

    # note the option ALL which allows to build the docs together with the application
    add_custom_target( doc_doxygen ALL
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM )
  endif()
else (DOXYGEN_FOUND)
  message("Doxygen need to be installed to generate the doxygen documentation")
endif (DOXYGEN_FOUND)
