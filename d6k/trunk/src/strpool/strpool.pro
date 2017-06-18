# ----------------------------------------------------
# This file is generated by the Qt Visual Studio Add-in.
# ------------------------------------------------------

TEMPLATE = lib
TARGET = strpool
DESTDIR = ../../bin

QT       += core gui xml 
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += debug
CONFIG += c++11

DEFINES += WIN64 SP_LIBRARY DEBUG
INCLUDEPATH += ./GeneratedFiles \
    . \
    ./GeneratedFiles/Debug \
    ./../../include/

LIBS += \
        -L../../lib/\
		-llog


DEPENDPATH += .
MOC_DIR += ./GeneratedFiles/debug
OBJECTS_DIR += debug
UI_DIR += ./GeneratedFiles
RCC_DIR += ./GeneratedFiles
 
win32:RC_FILE = strpool.rc


SOURCES += feslib.cpp\ 
		   ../fespub/sharemem.cpp \
		   fespapi.cpp \
		   mem_db.cpp \
		   msg_pump.cpp \
		   node.cpp \
		   channnel.cpp \
		   device.cpp \
		   tag.cpp \
		   alarm.cpp \


         

HEADERS +=  
          strpool.h\
           

RANSLATIONS += strpool-zh-CN.ts
    
RESOURCES  += strpool.qrc