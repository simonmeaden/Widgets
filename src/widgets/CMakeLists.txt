
target_sources(
    ${PROJECT_NAME}
  PRIVATE
  # NEED to include the header files here otherwise MOC won't handle them.
  # they are also automatically included in the target_include_directories
  # section but moc and indeed QtCreator seem to need them here as well
  ../../include/widgets/lnplaintextedit.h
  ../../include/widgets/lntextedit.h
  ../../include/widgets/htmltypes.h
  ../../include/widgets/helpdialogs.h
  ../../include/widgets/htmlscanner.h
  ../../include/widgets/htmlhighlighter.h
  ../../include/widgets/isettingspage.h
  ../../include/widgets/extendedcolordialog.h
  ../../include/widgets/hoverwidget.h
  ../../include/widgets/lnsettingsdialog.h
  ../../include/widgets/lnstatusbar.h
  ../../include/widgets/htmledit.h
  ../../include/widgets/htmleditor.h
#  ../../include/widgets/colordialog.h
  ../../include/widgets/htmltagdialog.h

   #


  # line number edits
  htmltypes.cpp
  lnplaintextedit.cpp
  lntextedit.cpp
  lnsettingsdialog.cpp
  lnstatusbar.cpp
  isettingspage.cpp
#  colordialog.cpp
  extendedcolordialog.cpp
  htmltagdialog.cpp
  htmledit.cpp
  htmleditor.cpp
  isettingspage.cpp
  settingsdialog.h
  settingsdialog.cpp

  # help dialogs.
  helpdialogs.cpp
  hoverwidget.cpp

  # HTML 5 scanner/highlighter
  htmlscanner.cpp
  htmlhighlighter.cpp
  htmltypes.cpp

  # extended color dialog
  extendedcolordialog.cpp

  icons.qrc
  fonts.qrc
)
