#-------------------------------------------------
# App:	    nonograms - application for creating and solving nonograms
# Author:   ololuki
# Site:	    ololuki.pl
# Created:  2017-03-28 12:05:23
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = nonograms
TEMPLATE = app

CONFIG += c++14

# put binaries in common directory
DESTDIR = $$OUT_PWD/../bin

# add lib binary for linking
unix|win32: LIBS += -L$$OUT_PWD/../bin -lcore

# add path to lib headers
INCLUDEPATH += $$PWD/../core
DEPENDPATH += $$PWD/../core

# force relink if sources in core lib change
win32:!win32-g++: PRE_TARGETDEPS += $$OUT_PWD/../bin/core.lib
else:unix|win32-g++: PRE_TARGETDEPS += $$OUT_PWD/../bin/libcore.a

DEFINES += QT_DEPRECATED_WARNINGS #emit warning if any deprecated feature is used

SOURCES += main.cpp
