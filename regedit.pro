#-------------------------------------------------
#
# Project created by QtCreator 2017-04-08T13:08:57
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = regedit
TEMPLATE = app
LIBS += -lAdvapi32
SOURCES += main.cpp\
        mainwindow.cpp \
    usb.cpp \
    autorun.cpp \
    ie.cpp \
    sysinfo.cpp \
    word.cpp

HEADERS  += mainwindow.h \
    usb.h \
    autorun.h \
    ie.h \
    sysinfo.h \
    word.h

FORMS    += mainwindow.ui

RESOURCES += \
    regedit.qrc

