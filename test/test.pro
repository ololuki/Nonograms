QT += core gui
QT += testlib

TARGET = NonogramsTests
TEMPLATE = app

CONFIG += console


# Sources of Test classes
SOURCES += TestMain.cpp \
    AddressOfCellTest.cpp \
    AddressOfHintTest.cpp \
    CellTest.cpp \
    ArrayOfCellsTest.cpp \
    LineOfCellsTest.cpp \
    HintsFieldTest.cpp


#Headers of Application classes (classes under tests)
HEADERS += ../app/field/HintsField.h \
    AddressOfCellTest.h \
    AddressOfHintTest.h \
    CellTest.h \
    ArrayOfCellsTest.h \
    LineOfCellsTest.h \
    HintsFieldTest.h


#Sources of Application classes (classes under tests)
SOURCES += ../app/field/AddressOfCell.cpp \
    ../app/field/AddressOfHint.cpp \
    ../app/field/Hint.cpp \
    ../app/field/HintsField.cpp \
    ../app/field/LineOfHints.cpp \
    ../app/field/ArrayOfCells.cpp \
    ../app/field/LineOfCells.cpp \
    ../app/field/Cell.cpp \


INCLUDEPATH += \
    ../app \
    ../lib
