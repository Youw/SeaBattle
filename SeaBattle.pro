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
<<<<<<< HEAD
    gamefieldguicontroller.cpp \
    function_pool.cpp \
    fp_functions.cpp \
    tree.cpp \
    evolbot.cpp
=======
    fieldgui.cpp \
    fieldguicontroller.cpp \
    game.cpp \
    Player/player.cpp \
    Player/playerhuman.cpp \
    fieldrandomizer.cpp \
    Player/playerbotstatic.cpp
>>>>>>> d4356fd700d6309a2364e8e555b38ac06dfd324b

HEADERS  += mainwindow.h \
    Serializer/Serializer.h \
    field.h \
    qwidgetwithposclicked.h \
<<<<<<< HEAD
    gamefieldguicontroller.h \
    function_pool.h \
    fp_functions.h \
    tree.h \
    evolbot.h
=======
    fieldgui.h \
    fieldguicontroller.h \
    game.h \
    Player/player.h \
    Player/playerhuman.h \
    fieldrandomizer.h \
    Player/playerbotstatic.h
>>>>>>> d4356fd700d6309a2364e8e555b38ac06dfd324b

FORMS    += mainwindow.ui \
    fieldgui.ui

RESOURCES += \
    graph.qrc

CONFIG += c++11

OTHER_FILES +=
