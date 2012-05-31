#-------------------------------------------------
#
# Project created by QtCreator 2010-09-08T16:19:14
#
#-------------------------------------------------

QT       += core gui network

TARGET = testCamIP_AXIS_213_PTZ
TEMPLATE = app


SOURCES += main.cpp\
        dialog.cpp

HEADERS  += dialog.h

FORMS    += dialog.ui

#on ajoute la librairie VLC:
INCLUDEPATH +=D:\Libs\vlc-1.0.5\sdk\include

LIBS += -LD:\Libs\vlc-1.0.5\sdk\lib
LIBS += -lvlc
