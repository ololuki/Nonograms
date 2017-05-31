#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <memory>
#include "field/WholeFieldImpl.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT
	
public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();
	
private slots:
	void on_actionNew_triggered();
	void on_actionOpen_triggered();
	void on_actionSave_as_triggered();
	
	void on_actionAdd_blocks_triggered();
	
	void on_actionAbout_triggered();
	void on_actionAbout_Qt_triggered();
	
private:
	Ui::MainWindow *ui;
	std::shared_ptr<WholeField> field;
	QString currentFileName;
	bool isFileNameSet;
	
	void setCurrentFileName(const QString &pathAndName);
	void saveFile();
	bool abandonChangesOrSavePrompt();
	void recreateField(size_t width, size_t height);
	void replaceField(std::shared_ptr<WholeField> newField);
};

#endif // MAINWINDOW_H
