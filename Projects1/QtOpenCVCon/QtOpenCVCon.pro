#-------------------------------------------------
#
# Project created by QtCreator 2013-12-05T10:50:12
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = QtOpenCVCon
CONFIG   += console
CONFIG   -= app_bundle
TEMPLATE = app

SOURCES += main.cpp
INCLUDEPATH += "C:\opencv\build\include"

# One of these variants depending on your compiler
# or an x64 version if you are building 64-bit
#

LIBS += -LC:/opencv/build/x86/vc11/lib

# Add the libraries you actually use with -l options.
LIBS += -lopencv_highgui246 \
        -lopencv_imgproc246 \
        -lopencv_core246 \
        -lopencv_features2d246 \
        -lopencv_calib3d246


