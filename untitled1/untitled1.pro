#-------------------------------------------------
#
# Project created by QtCreator 2013-12-16T23:08:11
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = untitled1
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    MyGlobalShortcut/MyWinEventFilter.cpp \
    MyGlobalShortcut/MyGlobalShortCut.cpp \
    ScreenShoot/ScreenShoot.cpp

HEADERS  += mainwindow.h \
    MyGlobalShortcut/MyWinEventFilter.h \
    MyGlobalShortcut/MyGlobalShortCut.h \
    ScreenShoot/ScreenShoot.h

FORMS    += mainwindow.ui

RESOURCES += \
    images/images.qrc
RC_FILE = myapp.rc
