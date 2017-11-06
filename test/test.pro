QT       += core gui

TARGET = NonogramsTests
TEMPLATE = app

CONFIG += console


# Sources of Test classes
SOURCES += TestMain.cpp \
    ArrayOfPixelsTest.cpp \
    AddressOfCellTest.cpp \
    LineOfCellsTest.cpp \
    HintsFieldTest.cpp


#Headers of Application classes (classes under tests)
HEADERS += ../app/field/HintsField.h \


#Sources of Application classes (classes under tests)
SOURCES += ../app/field/AddressOfCell.cpp \
    ../app/field/AddressOfHint.cpp \
    ../app/field/Hint.cpp \
    ../app/field/HintsField.cpp \
    ../app/field/LineOfHints.cpp \
    ../app/field/ArrayOfPixels.cpp \
    ../app/field/LineOfCells.cpp \
    ../app/field/Cell.cpp \


INCLUDEPATH += \
    ../app \
    ../lib
