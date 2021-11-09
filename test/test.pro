QT += core gui
QT += testlib

TARGET = NonogramsTests
TEMPLATE = app

CONFIG += console

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
    HintsFieldModelTest.h \
    CellsFieldModelTest.h \
    solver/SolverWorkerTest.h \
    solver/field/DeductiveFieldSolverTest.h \
    solver/line/BlocksFromBordersSolverTest.h \
    solver/line/BlocksFromDotAndFilledSolverTest.h \
    solver/line/CoveringBlocksSolverTest.h \
    solver/line/DotsBetweenDotsSolverTest.h \
    solver/line/FillFinishedSolverTest.h \
    solver/line/SingleDotsAroundFinishedBlocksSolverTest.h


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
    HintsFieldModelTest.cpp \
    CellsFieldModelTest.cpp \
    solver/SolverWorkerTest.cpp \
    solver/field/DeductiveFieldSolverTest.cpp \
    solver/line/BlocksFromBordersSolverTest.cpp \
    solver/line/BlocksFromDotAndFilledSolverTest.cpp \
    solver/line/CoveringBlocksSolverTest.cpp \
    solver/line/DotsBetweenDotsSolverTest.cpp \
    solver/line/FillFinishedSolverTest.cpp \
    solver/line/SingleDotsAroundFinishedBlocksSolverTest.cpp
