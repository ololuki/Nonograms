#include "FileManager.h"

#include <QMessageBox>
#include <QDebug>
#include <QFileDialog>
#include <QObject>
#include "file/NonogramFileWriter.h"
#include "file/NonogramFileReader.h"


FileManager::FileManager(const WholeField& field)
  : fieldInFile(field)
{
}

bool FileManager::isFieldDirty(const WholeField& field)
{
	//return (*fieldInFile != *field);
	return true;	//TODO
}

void FileManager::trySaveChanges(const WholeField& field)
{
	if(isFileNameSet)
	{
		saveFile(field);
	} else {
		trySaveAs(field);
	}
}

void FileManager::trySaveAs(const WholeField& field)
{
	// string filePath = FileView.FilePathDialog();
	//setCurrentFileName(fileName);
	//saveFile();
	
	QString fileName =
		QFileDialog::getSaveFileName(nullptr,
			QObject::tr("Save File"),
			QDir::currentPath(),
			QObject::tr("nonogram (*.nonogram)"));
	qDebug() << fileName;
	if (fileName.isEmpty()) return;
	setCurrentFileName(fileName);
	saveFile(field);
}

void FileManager::tryOpenAnotherFile()
{
	QString fileName =
		QFileDialog::getOpenFileName(nullptr,
			QObject::tr("Open File"),
			QDir::currentPath(),
			QObject::tr("nonogram (*.nonogram);;All File Types (*.*)"));
	
	if (fileName.isEmpty()) return;
	
	FileReader *reader = new NonogramFileReader();
	reader->read(fileName.toStdString());
	this->fieldInFile = reader->getField();
	delete reader;
}

void FileManager::setNewCreatedField(const WholeField& field)
{
	this->fieldInFile = field;
	dropCurrentFileName();
}

const WholeField& FileManager::getField()
{
	return fieldInFile;
}

void FileManager::setCurrentFileName(const QString &pathAndName)
{
	currentFileName = pathAndName;
	isFileNameSet = true;
}

void FileManager::dropCurrentFileName()
{
	currentFileName = "";
	isFileNameSet = false;
}

void FileManager::saveFile(const WholeField& field)
{
	FileWriter *writer = new NonogramFileWriter();
	writer->setField(field);
	if (writer->write(currentFileName.toStdString()))
	{
		this->fieldInFile = field;
		//ui->statusBar->showMessage(QString("Saved file: \"%1\"").arg(currentFileName));
		// public Qstring status = TODO
	} else {
		QMessageBox::critical(nullptr,
			"File Write Error",
			"Can not write to file.");
	}
	delete writer;
}

bool FileManager::abandonChangesOrSavePrompt(const WholeField& field)
{
	auto answer = QMessageBox::question(nullptr,
		"Unsaved changes",
		"Do you want to save changes?",
		QMessageBox::StandardButtons(QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel));
	if (answer == QMessageBox::Yes)
	{
		trySaveAs(field);
		
	} else if (answer == QMessageBox::Cancel) {
		return false;
	}
	return true;
}
