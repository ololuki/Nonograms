#ifndef FILECONTROLLER_H
#define FILECONTROLLER_H

#include <memory>
#include "field/WholeField.h"


class FileController
{
public:
	FileController(std::shared_ptr<WholeField> field);
	bool isFieldDirty(std::shared_ptr<WholeField> field);	// porównuje wewnętrzny field z fieldem przekazanym, wewnętrzny field odpowiada temu zapisanemu w pliku
	void trySaveChanges(std::shared_ptr<WholeField> field);		// zapisuje do bieżącego pliku lub pyta o scieżkę (trySaveAs); TODO zwraca SavedOkOrAbandoned = 0 lub Error = 1
	void trySaveAs(std::shared_ptr<WholeField> field);		// pyta o scieżkę i zapisuje plik
	void tryOpenAnotherFile();	//TODO zwraca enum/wyjątek CurrentFileIsDirty
	void setNewCreatedField(std::shared_ptr<WholeField> field);	// wywoływać po utworzeniu nowego pola, resetuje śiężkę do bieżącego pliku
	std::shared_ptr<WholeField> getField();	// zwraca field, który jest aktualnie zapisany w pliku; wywoływać po odczycie z pliku
	
	bool abandonChangesOrSavePrompt(std::shared_ptr<WholeField> field);	// will be private
private:
	std::shared_ptr<WholeField> fieldInFile;
	
	QString currentFileName;
	bool isFileNameSet;	// czy jest ustawiona ścieżka do pliku
	
	void setCurrentFileName(const QString &pathAndName);
	void dropCurrentFileName();		// wywoływana przy tworzeniu nowego nonogramu, żeby nowy nonogram zapisać w nowym pliku
	void saveFile(std::shared_ptr<WholeField> field);
};

#endif // FILECONTROLLER_H
