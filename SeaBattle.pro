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
    gamefields.cpp \
    field.cpp \
    qwidgetwithposclicked.cpp \
    gamefieldguicontroller.cpp

HEADERS  += mainwindow.h \
    field.h \
    gamefields.h \
    Serializer/Serializer.h \
    field.h \
    qwidgetwithposclicked.h \
    gamefieldguicontroller.h

FORMS    += mainwindow.ui \
    gamefields.ui

RESOURCES += \
    graph.qrc

CONFIG += c++11
