#-------------------------------------------------
#
# Project created by QtCreator 2014-11-27T04:16:08
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SeaBattle
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    field.cpp \
    qwidgetwithposclicked.cpp \
    fieldgui.cpp \
    fieldguicontroller.cpp

HEADERS  += mainwindow.h \
    field.h \
    Serializer/Serializer.h \
    field.h \
    qwidgetwithposclicked.h \
    fieldgui.h \
    fieldguicontroller.h

FORMS    += mainwindow.ui \
    gamefield.ui

RESOURCES += \
    graph.qrc

CONFIG += c++11
