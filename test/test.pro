QT       += core gui

TARGET = NonogramsTests
TEMPLATE = app

CONFIG += console

SOURCES += TestMain.cpp \
    LineOfPixelsTest.cpp \
    AddressOnDrawingAreaTest.cpp \
    ArrayOfPixelsTest.cpp \
    AllLinesDescriptionTest.cpp

SOURCES += ../app/field/AddressOnDrawingArea.cpp \
    ../app/field/AddressOnBlocksDescription.cpp \
    ../app/field/AllLinesDescription.cpp \
    

INCLUDEPATH += \
    ../app \
    ../lib

HEADERS +=
