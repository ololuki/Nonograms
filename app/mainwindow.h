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
	
	void on_actionAdd_blocks_triggered();
	
private:
	Ui::MainWindow *ui;
	std::shared_ptr<WholeField> field;
	void recreateField(size_t width, size_t height);
	bool abandonChangesOrSavePrompt();
};

#endif // MAINWINDOW_H
