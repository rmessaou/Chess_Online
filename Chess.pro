#-------------------------------------------------
#
# Project created by QtCreator 2019-09-21T13:03:50
#
#-------------------------------------------------

QT       += core gui network widgets


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
CONFIG += c++14
TARGET = Chess
TEMPLATE = app
QMAKE_CXXFLAGS += -Wall

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
    Gui/errormessage.cpp \
    Gui/stopwatch.cpp \
        main.cpp \
        supervisor.cpp \
    Netzwerk/myserver.cpp \
    Logik/chess.cpp \
    Gui/chesspieces.cpp \
    Gui/chessboard.cpp \
    Gui/game.cpp \
    Gui/chesstile.cpp \
    Gui/network.cpp \
    Netzwerk/myclient.cpp \
    Gui/chat.cpp

HEADERS += \
    Gui/errormessage.h \
    Gui/stopwatch.h \
        supervisor.h \
    Netzwerk/myserver.h \
    Logik/chess.h \
    Gui/chesspieces.h \
    Gui/chessboard.h \
    Gui/game.h \
    Gui/chesstile.h \
    Gui/network.h \
    Netzwerk/myclient.h \
    Gui/chat.h

FORMS += \
    Gui/errormessage.ui \
    Gui/game.ui \
    Gui/chat.ui

RESOURCES += \
    Gui/chessPiecesWhite.qrc \
    Gui/ChessFigures.qrc \
    Gui/normal_figures.qrc \
    Gui/gifs.qrc \
    Gui/schachbrett.qrc \
    Gui/figures_startscreennosubs.qrc

DISTFILES += \
    Gui/tenor.gif \
    Gui/Tower_black.png \
    Gui/tower_white.png \
    Gui/bishop_black.png \
    Gui/bishop_white.png \
    Gui/queen_black.png \
    Gui/queen_white.png \
    Gui/king_black.png \
    Gui/king_white.png \
    Gui/knight_black.png \
    Gui/knight_white.png \
    Gui/Pawn_black.png \
    Gui/pawn_white.png
