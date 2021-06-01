#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <memory>
#include "field/WholeFieldModel.h"


class FileManager
{
public:
	FileManager(const WholeField& field);
	bool isFieldDirty(const WholeField& field);	// porównuje wewnętrzny field z fieldem przekazanym, wewnętrzny field odpowiada temu zapisanemu w pliku
	void trySaveChanges(const WholeField& field);		// zapisuje do bieżącego pliku lub pyta o scieżkę (trySaveAs); TODO zwraca SavedOkOrAbandoned = 0 lub Error = 1
	void trySaveAs(const WholeField& field);		// pyta o scieżkę i zapisuje plik
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
