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
    fieldguicontroller.cpp \
    game.cpp \
    Player/player.cpp \
    Player/playerhuman.cpp \
    fieldrandomizer.cpp \
    Player/playerbotstatic.cpp \
    evolbot.cpp \
    fp_functions.cpp \
    function_pool.cpp \
    tree.cpp

HEADERS  += mainwindow.h \
    Serializer/Serializer.h \
    field.h \
    qwidgetwithposclicked.h \
    fieldgui.h \
    fieldguicontroller.h \
    game.h \
    Player/player.h \
    Player/playerhuman.h \
    fieldrandomizer.h \
    Player/playerbotstatic.h \
    evolbot.h \
    fp_functions.h \
    function_pool.h \
    tree.h

FORMS    += mainwindow.ui \
    fieldgui.ui

RESOURCES += \
    graph.qrc

CONFIG += c++11
