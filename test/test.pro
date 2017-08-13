QT       += core gui

TARGET = NonogramsTests
TEMPLATE = app

CONFIG += console

# Sources of Test classes
SOURCES += TestMain.cpp \
    LineOfPixelsTest.cpp \
    AddressOnDrawingAreaTest.cpp \
    ArrayOfPixelsTest.cpp \
    AllLinesDescriptionTest.cpp

#Sources of Application classes (classes under tests)
SOURCES += ../app/field/AddressOnDrawingArea.cpp \
    ../app/field/AddressOnBlocksDescription.cpp \
    ../app/field/AllLinesDescription.cpp \
    ../app/field/ArrayOfPixels.cpp \
    ../app/field/Pixel.cpp \
    

INCLUDEPATH += \
    ../app \
    ../lib

HEADERS +=
