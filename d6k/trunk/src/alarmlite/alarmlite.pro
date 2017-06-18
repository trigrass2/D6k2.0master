# ----------------------------------------------------
# This file is generated by the Qt Visual Studio Add-in.
# ------------------------------------------------------

TEMPLATE = lib
TARGET = alarmlite
DESTDIR = ../../x64/Debug
QT += core multimedia widgets gui
CONFIG += debug
DEFINES += WIN64 QT_DLL QT_MULTIMEDIA_LIB SCD_ALARM_LIB QT_WIDGETS_LIB
INCLUDEPATH += ./GeneratedFiles \
    . \
    ./GeneratedFiles/Debug \
    ./../../include \
    ./../../include/mail \
    ./../../include/log
LIBS += -L"./../../lib" \
    -llog \
    -lmail
DEPENDPATH += .
MOC_DIR += ./GeneratedFiles/debug
OBJECTS_DIR += debug
UI_DIR += ./GeneratedFiles
RCC_DIR += ./GeneratedFiles
HEADERS +=  ./scd_alarm_global.h \
    ./alarmdataconfig.h \
    ./alarminfomodel.h \
    ./alarmwindow.h \
    ./analysemsg.h \
    ./delegate.h \
    ./recvinfo.h \
    ./threadsafedata.h \
    ./alarmlite.h
SOURCES += ./alarminfomodel.cpp \
    ./alarmwindow.cpp \
    ./analysemsg.cpp \
    ./delegate.cpp \
    ./recvinfo.cpp \
    ./alarmlite.cpp
FORMS += ./alarmwindow.ui
