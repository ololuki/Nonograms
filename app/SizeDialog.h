#ifndef SIZEDIALOG_H
#define SIZEDIALOG_H

#include <QDialog>

namespace Ui {
class SizeDialog;
}

class SizeDialog : public QDialog
{
	Q_OBJECT
	
public:
	explicit SizeDialog(QWidget *parent = 0);
	~SizeDialog();
	int getWidth();
	int getHeight();
	
private:
	Ui::SizeDialog *ui;
};

#endif // SIZEDIALOG_H
