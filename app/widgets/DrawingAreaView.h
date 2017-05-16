#ifndef DRAWINGAREAVIEW_H
#define DRAWINGAREAVIEW_H

#include <QWidget>
#include "field/DrawingAreaField.h"


class DrawingAreaView : public QWidget
{
	Q_OBJECT
public:
	explicit DrawingAreaView(QWidget *parent = 0);
	void setField(DrawingAreaField *field);
	
public slots:
	void onDataChanged();
	
protected:
	void mousePressEvent(QMouseEvent *event) override;
	void paintEvent(QPaintEvent *event) override;
	
private:
	const int squareSize = 30;
	void drawGrid();
	void drawOnePixel(Pixel pixel);
	
	void resizeDrawingArea(const QSize &newSize);
	int myPenWidth;
	QColor myPenColor;
	QImage image;
	QPoint lastPoint;
	
	DrawingAreaField *field;
};

#endif // DRAWINGAREAVIEW_H
