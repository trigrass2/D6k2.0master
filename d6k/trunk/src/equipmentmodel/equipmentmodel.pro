# ----------------------------------------------------
# This file is generated by the Qt Visual Studio Add-in.
# ------------------------------------------------------

TEMPLATE = app
TARGET = equipmentmodel
DESTDIR = ./Win32/Debug
QT += core widgets gui
CONFIG += debug
DEFINES += WIN64 QT_DLL QT_WIDGETS_LIB
INCLUDEPATH += ./GeneratedFiles \
    . \
    ./GeneratedFiles/Debug
DEPENDPATH += .
MOC_DIR += ./GeneratedFiles/debug
OBJECTS_DIR += debug
UI_DIR += ./GeneratedFiles
RCC_DIR += ./GeneratedFiles
win32:RC_FILE = equipmentmodel.rc
HEADERS += ./contentmodel.h \
    ./modeldefine.h \
    ./modelinfo.h \
    ./equipmentmodel.h \
    ./treeview.h \
    ./delegate.h \
    ./resource.h
SOURCES += ./contentmodel.cpp \
    ./delegate.cpp \
    ./equipmentmodel.cpp \
    ./main.cpp \
    ./modelinfo.cpp \
    ./treeview.cpp
RESOURCES += equipmentmodel.qrc
