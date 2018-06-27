#-------------------------------------------------
#
# Project created by QtCreator 2017-09-05T17:16:22
#
#-------------------------------------------------

QT       += core gui
QT       += concurrent
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LTC
TEMPLATE = app
INCLUDEPATH += "C:/Users/stevensn2h/Source/Repos/Visual-Timecode-"
INCLUDEPATH += "C:/"


# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++14

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    ../../Source/Repos/Visual-Timecode-/manchester.cpp \
    ../../Source/Repos/Visual-Timecode-/opal_interface.cpp \
    ../../Source/Repos/Visual-Timecode-/timecode.cpp \
    ../../Source/Repos/Visual-Timecode-/lowpass.cpp

HEADERS += \
        mainwindow.h \
    ../../Source/Repos/Visual-Timecode-/manchester.h \
    ../../Source/Repos/Visual-Timecode-/opal_interface.h \
    ../../Source/Repos/Visual-Timecode-/timecode.h \
    mainwindow.h \
    ../../../../al.h \
    ../../../../alc.h \
    ../../Source/Repos/Visual-Timecode-/lowpass.h

FORMS += \
    mainwindow.ui
        mainwindow.ui


LIBS += -L"C:/" -lOpenAL32

