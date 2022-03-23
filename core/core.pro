QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = core
TEMPLATE = lib
# using static lib there is no need to declaring export / import macros for MSVC
CONFIG += staticlib

CONFIG += c++14

# put binaries in common directory
DESTDIR = ../bin

DEFINES += QT_DEPRECATED_WARNINGS #emit warning if any deprecated feature is used

SOURCES += \
    controller/AbstractCellsController.cpp \
    controller/AbstractHintsController.cpp \
    controller/EditableCellsController.cpp \
    controller/EditableHintsController.cpp \
    controller/ReadOnlyCellsController.cpp \
    controller/ReadOnlyHintsController.cpp \
    mainwindow.cpp \
    field/WholeField.cpp \
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
    field/CellsField.cpp \
    field/CellsFieldModel.cpp \
    field/HintsField.cpp \
    field/HintsFieldModel.cpp \
    field/Orientation.cpp \
    solver/SolverWorker.cpp \
    solver/field/AbstractFieldSolver.cpp \
    solver/field/DeductiveFieldSolver.cpp \
    solver/field/FieldSolverObserver.cpp \
    solver/line/AbstractLineSolver.cpp \
    solver/line/BlocksFromBordersSolver.cpp \
    solver/line/BlocksFromDotAndFilledSolver.cpp \
    solver/line/CoveringBlocksSolver.cpp \
    solver/line/DotsBetweenDotsSolver.cpp \
    solver/line/FillFinishedSolver.cpp \
    solver/line/SingleDotsAroundFinishedBlocksSolver.cpp \
    splitter/FinishedBlocksLineSplitter.cpp \
    splitter/SplittingTools.cpp \
    utils/TimeMeasure.cpp

HEADERS += \
    controller/AbstractCellsController.h \
    controller/AbstractHintsController.h \
    controller/DrawingMode.h \
    controller/EditableCellsController.h \
    controller/EditableHintsController.h \
    controller/ReadOnlyCellsController.h \
    controller/ReadOnlyHintsController.h \
    mainwindow.h \
    field/WholeField.h \
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
    field/CellsField.h \
    field/CellsFieldModel.h \
    field/HintsField.h \
    field/HintsFieldModel.h \
    field/Orientation.h \
    solver/SolverWorker.h \
    solver/field/AbstractFieldSolver.h \
    solver/field/DeductiveFieldSolver.h \
    solver/field/FieldSolverObserver.h \
    solver/line/AbstractLineSolver.h \
    solver/line/BlocksFromBordersSolver.h \
    solver/line/BlocksFromDotAndFilledSolver.h \
    solver/line/CoveringBlocksSolver.h \
    solver/line/DotsBetweenDotsSolver.h \
    solver/line/FillFinishedSolver.h \
    solver/line/SingleDotsAroundFinishedBlocksSolver.h \
    splitter/AbstractLineSplitter.h \
    splitter/FinishedBlock.h \
    splitter/FinishedBlocksLineSplitter.h \
    splitter/SplittingTools.h \
    splitter/SubLine.h \
    utils/TimeMeasure.h

FORMS += \
    mainwindow.ui \
    sizedialog.ui
