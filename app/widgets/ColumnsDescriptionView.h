#ifndef COLUMNSDESCRIPTIONVIEW_H
#define COLUMNSDESCRIPTIONVIEW_H

#include <QWidget>
#include <QTextEdit>
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
	
protected:
	void paintEvent(QPaintEvent *event) override;
	void mousePressEvent(QMouseEvent *event) override;
	
private:
	const size_t squareSize = 30;		// TODO: move to generalView class
	const int myPenWidth = 1;
	const QColor myPenColor = Qt::black;
	QTextEdit *qTextEdit;
	
	QImage image;
	BlocksDescriptionField *field;
	
	bool isPointOnDefinedDescription(QPoint point);
	void redrawAll();
	void drawOneBlockDescription(BlockDescription blockDescription);
	void initTextBox();
	void hideTextBox();
	void saveTextBoxToBlockDescription();
	void moveAndShowTextBox(AddressOnBlocksDescription address);
	
	void resize(const QSize &newSize);
};

#endif // COLUMNSDESCRIPTIONVIEW_H
