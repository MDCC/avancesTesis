#-------------------------------------------------
#
# Project created by QtCreator 2013-01-23T19:50:31
#
#-------------------------------------------------

QT += core gui

TARGET = GUIOpenCV

TEMPLATE = app

SOURCES += main.cpp\
          mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

INCLUDEPATH += /usr/local/include/opencv2

LIBS += -L/usr/local/lib -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_features2d -lopencv_calib3d

