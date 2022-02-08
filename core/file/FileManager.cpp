/**********************************************************************
 * Copyright (C) 2022 Ololuki
 * https://ololuki.pl
 *
 * This file is part of Nonograms
 * https://github.com/ololuki/nonograms
 *
 * Nonograms is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * Nonograms is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Nonograms.  If not, see <http://www.gnu.org/licenses/>.
 *********************************************************************/
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

FileManager::FileManager(WholeField&& field)
  : fieldInFile(std::move(field))
{
}

bool FileManager::isFieldDirty(const WholeField& field)
{
	return fieldInFile != field;
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

///
/// \brief Get filename from user and save field to file.
/// \param field
/// \return true - file saved
///         false - operation cancelled
///
bool FileManager::trySaveAs(const WholeField& field)
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
	if (fileName.isEmpty())
		return false;
	setCurrentFileName(fileName);
	saveFile(field);
	return true;
}

///
/// \brief Get filename from user and open it.
/// \return true - file opened
///         false - operation cancelled
///
bool FileManager::tryOpenAnotherFile()
{
	QString fileName =
		QFileDialog::getOpenFileName(nullptr,
			QObject::tr("Open File"),
			QDir::currentPath(),
			QObject::tr("nonogram (*.nonogram);;All File Types (*.*)"));
	
	if (fileName.isEmpty())
	{
		return false;
	}
	
	FileReader *reader = new NonogramFileReader();
	reader->read(fileName.toStdString());
	this->fieldInFile = reader->getField();
	delete reader;
	return true;
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

///
/// \brief FileManager::abandonChangesOrSavePrompt
/// \param field
/// \return true - file saved,
///                no need to save or
///                user explicitly discarded changes;
///         false - operation cancelled
///
bool FileManager::abandonChangesOrSavePrompt(const WholeField& field)
{
	if (!isFieldDirty(field))
	{
		// no need to save
		return true;
	}
	auto answer = QMessageBox::question(nullptr,
		"Unsaved changes",
		"Do you want to save changes?",
		QMessageBox::StandardButtons(QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel));
	if (answer == QMessageBox::Yes)
	{
		return trySaveAs(field);
	}
	else if (answer == QMessageBox::No)
	{
		// user explicitly discarded changes
		return true;
	}
	// operation cancelled
	return false;
}
