QT       += core gui

TARGET = NonogramsTests
TEMPLATE = app

CONFIG += console


# Sources of Test classes
SOURCES += TestMain.cpp \
    LineOfPixelsTest.cpp \
    AddressOnDrawingAreaTest.cpp \
    ArrayOfPixelsTest.cpp \
    BlocksDescriptionFieldTest.cpp


#Headers of Application classes (classes under tests)
HEADERS += ../app/field/BlocksDescriptionField.h


#Sources of Application classes (classes under tests)
SOURCES += ../app/field/AddressOnDrawingArea.cpp \
    ../app/field/AddressOnBlocksDescription.cpp \
    ../app/field/BlockDescription.cpp \
    ../app/field/BlocksDescriptionField.cpp \
    ../app/field/ArrayOfPixels.cpp \
    ../app/field/Pixel.cpp


INCLUDEPATH += \
    ../app \
    ../lib
