QT += core gui
QT += testlib

TARGET = NonogramsTests
TEMPLATE = app

CONFIG += console

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
    CellsFieldModelTest.h \
    solver/SolverWorkerTest.h \
    solver/line/CoveringBlocksSolverTest.h


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
    CellsFieldModelTest.cpp \
    solver/SolverWorkerTest.cpp \
    solver/line/CoveringBlocksSolverTest.cpp
