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
    widgets/DrawingAreaView.cpp \
    field/AddressOnDrawingArea.cpp \
    field/Pixel.cpp \
    field/DrawingAreaField.cpp \
    field/WholeField.cpp \
    field/LineOfPixels.cpp \
    field/ArrayOfPixels.cpp \
    field/BlocksDescriptionField.cpp \
    field/AddressOnBlocksDescription.cpp \
    field/BlockDescription.cpp \
    field/LineOfHints.cpp \
    SizeDialog.cpp \
    file/FileManager.cpp \
    file/NonogramFileWriter.cpp \
    file/NonogramFileReader.cpp \
    controller/FieldController.cpp \
    controller/DrawingAreaController.cpp \
    controller/BlocksDescriptionController.cpp \
    widgets/common/DrawableView.cpp \
    widgets/HintsView.cpp \
    utils/NVector.cpp

HEADERS  += mainwindow.h \
    widgets/DrawingAreaView.h \
    field/AddressOnDrawingArea.h \
    field/pixelSign.h \
    field/Pixel.h \
    field/DrawingAreaField.h \
    field/WholeField.h \
    field/LineOfPixels.h \
    field/ArrayOfPixels.h \
    field/BlocksDescriptionField.h \
    field/AddressOnBlocksDescription.h \
    field/BlockDescription.h \
    field/LineOfHints.h \
    field/FieldMode.h \
    SizeDialog.h \
    file/FileManager.h \
    file/FileWriter.h \
    file/NonogramFileWriter.h \
    file/FileReader.h \
    file/NonogramFileReader.h \
    controller/FieldController.h \
    controller/DrawingAreaController.h \
    controller/BlocksDescriptionController.h \
    widgets/common/FieldViewConstants.h \
    widgets/common/DrawableView.h \
    widgets/HintsView.h \
    utils/NVector.h

FORMS    += mainwindow.ui \
    sizedialog.ui
