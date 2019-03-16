QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = core
TEMPLATE = lib
# using static lib there is no need to declaring export / import macros for MSVC
CONFIG += staticlib

# put binaries in common directory
DESTDIR = ../bin

DEFINES += QT_DEPRECATED_WARNINGS #emit warning if any deprecated feature is used

SOURCES += \
    mainwindow.cpp \
    field/WholeFieldModel.cpp \
    field/ArrayOfCells.cpp \
    field/LineOfHints.cpp \
    SizeDialog.cpp \
    file/FileManager.cpp \
    file/NonogramFileWriter.cpp \
    file/NonogramFileReader.cpp \
    controller/FieldController.cpp \
    widgets/common/DrawableView.cpp \
    widgets/HintsView.cpp \
    utils/NVector.cpp \
    widgets/common/InsertingButtonEventFilter.cpp \
    field/AddressOfHint.cpp \
    field/AddressOfCell.cpp \
    field/Cell.cpp \
    field/CellSign.cpp \
    field/Hint.cpp \
    field/LineOfCells.cpp \
    widgets/CellsView.cpp \
    controller/HintsController.cpp \
    controller/CellsController.cpp \
    field/CellsField.cpp \
    field/CellsFieldModel.cpp \
    field/HintsField.cpp \
    field/HintsFieldModel.cpp \
    field/Orientation.cpp \
    solver/SolverWorker.cpp \
    solver/line/AbstractLineSolver.cpp \
    solver/line/CoveringBlocksSolver.cpp \
    utils/TimeMeasure.cpp

HEADERS += \
    mainwindow.h \
    field/WholeFieldModel.h \
    field/ArrayOfCells.h \
    field/LineOfHints.h \
    field/FieldMode.h \
    SizeDialog.h \
    file/FileManager.h \
    file/FileWriter.h \
    file/NonogramFileWriter.h \
    file/FileReader.h \
    file/NonogramFileReader.h \
    controller/FieldController.h \
    widgets/common/FieldViewConstants.h \
    widgets/common/DrawableView.h \
    widgets/HintsView.h \
    utils/NVector.h \
    widgets/common/InsertingButtonEventFilter.h \
    controller/action/CellAction.h \
    controller/action/HintAction.h \
    field/AddressOfHint.h \
    field/AddressOfCell.h \
    field/Cell.h \
    field/CellSign.h \
    field/Hint.h \
    field/LineOfCells.h \
    widgets/CellsView.h \
    controller/HintsController.h \
    controller/CellsController.h \
    field/CellsField.h \
    field/CellsFieldModel.h \
    field/HintsField.h \
    field/HintsFieldModel.h \
    field/Orientation.h \
    solver/SolverWorker.h \
    solver/line/AbstractLineSolver.h \
    solver/line/CoveringBlocksSolver.h \
    utils/TimeMeasure.h

FORMS += \
    mainwindow.ui \
    sizedialog.ui
