QT       += core gui

TARGET = NonogramsTests
TEMPLATE = app

CONFIG += console

SOURCES += TestMain.cpp \
    LineOfPixelsTest.cpp \
    AddressOnDrawingAreaTest.cpp \
    ArrayOfPixelsTest.cpp

INCLUDEPATH += \
    ../app \
    ../lib

HEADERS +=
