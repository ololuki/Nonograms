#ifndef COLUMNSDESCRIPTIONVIEW_H
#define COLUMNSDESCRIPTIONVIEW_H

#include <QWidget>
#include <QTextEdit>
#include <QPushButton>
#include "field/BlocksDescriptionField.h"
#include "field/BlockDescription.h"

class ColumnsDescriptionView : public QWidget
{
	Q_OBJECT
public:
	explicit ColumnsDescriptionView(QWidget *parent = 0);
	void setField(BlocksDescriptionField *field);
	
signals:
	
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
	const int insertingButtonHeight = squareSize/2;
	
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

#endif // COLUMNSDESCRIPTIONVIEW_H
