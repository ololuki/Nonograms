#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <memory>
#include "controller/FieldController.h"


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
	std::shared_ptr<FieldController> fieldController;
};

#endif // MAINWINDOW_H
