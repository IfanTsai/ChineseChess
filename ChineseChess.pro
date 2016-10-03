#-------------------------------------------------
#
# Project created by QtCreator 2016-05-22T21:04:16
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = chinaChess
TEMPLATE = app


SOURCES += main.cpp\
        Board.cpp \
    Stone.cpp \
    WinWidget.cpp \
    SingleGame.cpp \
    openWidget.cpp \
    NetGame.cpp \
    ChooseSerOrCli.cpp \
    ChooseIP.cpp \
    InputIP.cpp

HEADERS  += Board.h \
    Stone.h \
    WinWidget.h \
    Step.h \
    SingleGame.h \
    openWidget.h \
    NetGame.h \
    ChooseSerOrCli.h \
    ChooseIP.h \
    InputIP.h \
    step.h
CONFIG += c++11

RESOURCES += \
    chessrec.qrc

FORMS += \
    openWidget.ui \
    ChooseSerOrCli.ui
