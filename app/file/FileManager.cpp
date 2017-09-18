#include "FileManager.h"

#include <QMessageBox>
#include <QDebug>
#include <QFileDialog>
#include <QObject>
#include "file/NonogramFileWriter.h"
#include "file/NonogramFileReader.h"


FileManager::FileManager(std::shared_ptr<WholeField> field)
{
	this->fieldInFile = std::make_shared<WholeField>(*field);
}

bool FileManager::isFieldDirty(std::shared_ptr<WholeField> field)
{
	//return (*fieldInFile != *field);
	return true;	//TODO
}

void FileManager::trySaveChanges(std::shared_ptr<WholeField> field)
{
	if(isFileNameSet)
	{
		saveFile(field);
	} else {
		trySaveAs(field);
	}
}

void FileManager::trySaveAs(std::shared_ptr<WholeField> field)
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

void FileManager::setNewCreatedField(std::shared_ptr<WholeField> field)
{
	this->fieldInFile = std::make_shared<WholeField>(*field);
	dropCurrentFileName();
}

std::shared_ptr<WholeField> FileManager::getField()
{
	return std::make_shared<WholeField>(*fieldInFile);
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

void FileManager::saveFile(std::shared_ptr<WholeField> field)
{
	FileWriter *writer = new NonogramFileWriter();
	writer->setField(field);
	if (writer->write(currentFileName.toStdString()))
	{
		this->fieldInFile = std::make_shared<WholeField>(*field);
		//ui->statusBar->showMessage(QString("Saved file: \"%1\"").arg(currentFileName));
		// public Qstring status = TODO
	} else {
		QMessageBox::critical(nullptr,
			"File Write Error",
			"Can not write to file.");
	}
	delete writer;
}

bool FileManager::abandonChangesOrSavePrompt(std::shared_ptr<WholeField> field)
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
