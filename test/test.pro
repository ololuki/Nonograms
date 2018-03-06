QT += core gui
QT += testlib

TARGET = NonogramsTests
TEMPLATE = app

CONFIG += console


# Headers of Test classes
HEADERS += \
    CellSignTest.h \
    AddressOfCellTest.h \
    AddressOfHintTest.h \
    CellTest.h \
    HintTest.h \
    ArrayOfCellsTest.h \
    LineOfCellsTest.h \
    HintsFieldTest.h \
    CellsFieldTest.h \
    solver/SolverWorkerTest.h


# Sources of Test classes
SOURCES += TestMain.cpp \
    CellSignTest.cpp \
    AddressOfCellTest.cpp \
    AddressOfHintTest.cpp \
    CellTest.cpp \
    HintTest.cpp \
    ArrayOfCellsTest.cpp \
    LineOfCellsTest.cpp \
    HintsFieldTest.cpp \
    CellsFieldTest.cpp \
    solver/SolverWorkerTest.cpp


# Headers of Application classes (classes under tests)
HEADERS += ../app/field/HintsField.h \
    ../app/field/CellsField.h \
    ../app/field/WholeField.h \
    ../app/solver/SolverWorker.h


# Sources of Application classes (classes under tests)
SOURCES += \
    ../app/field/CellSign.cpp \
    ../app/field/AddressOfCell.cpp \
    ../app/field/AddressOfHint.cpp \
    ../app/field/Hint.cpp \
    ../app/field/HintsField.cpp \
    ../app/field/LineOfHints.cpp \
    ../app/field/ArrayOfCells.cpp \
    ../app/field/LineOfCells.cpp \
    ../app/field/Cell.cpp \
    ../app/field/CellsField.cpp \
    ../app/field/WholeField.cpp \
    ../app/solver/SolverWorker.cpp


INCLUDEPATH += \
    ../app \
    ../lib
