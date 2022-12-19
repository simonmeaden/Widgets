cmake_minimum_required(VERSION 3.7)

project(helpdialogs VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

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
    Core5Compat
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
    )
  if (Qt5_FOUND)
    message("Qt Help Dialogs Qt5 Found ")
  endif()
else()
  message("Qt Help Dialogs Qt6 Found")
endif()

set(TS_FILES helpdialogs_en_GB.ts)

add_executable(helpdialogs
  main.cpp
  mainwindow.cpp
  mainwindow.h
  mainwindow.ui
  ${TS_FILES}
)

target_link_libraries(
    helpdialogs
  PRIVATE
   Qt${QT_VERSION_MAJOR}::Widgets
   SMLibraries::SMLibraries
   qmarkdowntextedit
)

