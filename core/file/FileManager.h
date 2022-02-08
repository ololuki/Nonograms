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
#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <memory>
#include "field/WholeFieldModel.h"


class FileManager
{
public:
	explicit FileManager(const WholeField& field);
	explicit FileManager(WholeField&& field);

	FileManager(const FileManager&) = delete;
	FileManager(FileManager&&) = delete;
	FileManager& operator=(const FileManager&) = delete;
	FileManager& operator=(FileManager&&) = delete;
	~FileManager() = default;

	bool isFieldDirty(const WholeField& field);	// porównuje wewnętrzny field z fieldem przekazanym, wewnętrzny field odpowiada temu zapisanemu w pliku
	void trySaveChanges(const WholeField& field);		// zapisuje do bieżącego pliku lub pyta o scieżkę (trySaveAs); TODO zwraca SavedOkOrAbandoned = 0 lub Error = 1
	bool trySaveAs(const WholeField& field);
	bool tryOpenAnotherFile();
	void setNewCreatedField(const WholeField& field);	// wywoływać po utworzeniu nowego pola, resetuje śiężkę do bieżącego pliku
	const WholeField& getField();	// zwraca field, który jest aktualnie zapisany w pliku; wywoływać po odczycie z pliku
	
	bool abandonChangesOrSavePrompt(const WholeField& field);	// will be private
private:
	WholeField fieldInFile;
	
	QString currentFileName;
	bool isFileNameSet;	// czy jest ustawiona ścieżka do pliku
	
	void setCurrentFileName(const QString &pathAndName);
	void dropCurrentFileName();		// wywoływana przy tworzeniu nowego nonogramu, żeby nowy nonogram zapisać w nowym pliku
	void saveFile(const WholeField& field);
};

#endif // FILEMANAGER_H
