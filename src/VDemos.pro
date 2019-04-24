#-------------------------------------------------
#
# Project created by QtCreator 2018-05-09T08:22:53
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = VDemos
TEMPLATE = app

# CONFIG += console

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    MediaManager/sourcemanager.cpp \
    MediaManager/videoplayer.cpp \
    MediaManager/dispwidget.cpp \
    screen.cpp \
    Vision/Algorithms/activecontours.cpp \
    Vision/Algorithms/bresenham.cpp \
    Vision/Algorithms/sobel.cpp \
    Vision/Algorithms/gaussarea.cpp \
    paraminterface.cpp \
    custonsnakeparams.cpp \
    Vision/Algorithms/customsnake.cpp

HEADERS += \
        mainwindow.h \
    MediaManager/sourcemanager.h\
    MediaManager/videoplayer.h \
    MediaManager/dispwidget.h \
    screen.h \
    Vision/Algorithms/activecontours.h \
    Vision/Algorithms/bresenham.h \
    Vision/Algorithms/sobel.h \
    Vision/Algorithms/gaussarea.h \
    paraminterface.h \
    Vision/tsparams.h \
    custonsnakeparams.h \
    Vision/Algorithms/customsnake.h

FORMS += \
        mainwindow.ui \
    screen.ui \
    paraminterface.ui \
    custonsnakeparams.ui

unix {
    CONFIG += link_pkgconfig
    PKGCONFIG += opencv
}

mac {
    INCLUDEPATH += /usr/local/Cellar/opencv/3.4.1_2/include \

    LIBS += -L/usr/local/Cellar/opencv/3.4.1_2/lib \
         -lopencv_core \
         -lopencv_imgproc \
         -lopencv_features2d\
         -lopencv_highgui\
         -lopencv_video\
         -lopencv_videoio

}

