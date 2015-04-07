#-------------------------------------------------
#
# Project created by QtCreator 2013-12-06T16:25:31
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QtGuiOpenCV
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui
INCLUDEPATH += "C:\opencv\build\include"
LIBS += -LC:/opencv/build/x86/vc11/lib

# Add the libraries you actually use with -l options.
LIBS += -lopencv_highgui246 \
        -lopencv_imgproc246 \
        -lopencv_core246 \
        -lopencv_features2d246 \
        -lopencv_calib3d246
