#ifndef ROWSDESCRIPTIONVIEW_H
#define ROWSDESCRIPTIONVIEW_H

#include <QWidget>
#include <QTextEdit>
#include <QPushButton>
#include "field/BlocksDescriptionField.h"
#include "field/BlockDescription.h"

class RowsDescriptionView : public QWidget
{
	Q_OBJECT
public:
	explicit RowsDescriptionView(QWidget *parent = 0);
	void setField(BlocksDescriptionField *field);
	
public slots:
	void onDataChanged();
private slots:
	void onInsertingButtonClick();
	
protected:
	void paintEvent(QPaintEvent *event) override;
	void mousePressEvent(QMouseEvent *event) override;
	void mouseMoveEvent(QMouseEvent *event) override;
private:
	const int squareSize = 30;		// TODO: move to generalView class
	const int myPenWidth = 1;
	const QColor myPenColor = Qt::black;
	QTextEdit *qTextEdit;
	QPushButton *insertingButton;
	const int insertingButtonWidth = squareSize/2;
	
	QImage image;
	BlocksDescriptionField *field;
	
	bool isPointOnDefinedDescription(QPoint screenPoint);
	void redrawAll();
	void drawOneBlockDescription(BlockDescription blockDescription);
	void drawCleanOneBlock(AddressOnBlocksDescription address);
	void initTextBox();
	void hideTextBox();
	void saveTextBoxToBlockDescription();
	void moveAndShowTextBox(AddressOnBlocksDescription address);
	void initInsertingButton();
	void hideInsertingButton();
	void moveAndShowInsertingButton(AddressOnBlocksDescription address);
	
	void resize(const QSize &newSize);
};

#endif // ROWSDESCRIPTIONVIEW_H
