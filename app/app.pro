#-------------------------------------------------
# App:	    nonograms - application for creating and solving nonograms
# Author:   ololuki
# Site:	    ololuki.pl
# Created:  2017-03-28 12:05:23
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = nonograms
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS #emit warning if any deprecated feature is used

SOURCES += main.cpp\
        mainwindow.cpp \
    field/WholeField.cpp \
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
    field/HintsField.cpp \
    field/Orientation.cpp

HEADERS  += mainwindow.h \
    field/WholeField.h \
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
    field/HintsField.h \
    field/Orientation.h

FORMS    += mainwindow.ui \
    sizedialog.ui
