#ifndef DRAWINGAREAVIEW_H
#define DRAWINGAREAVIEW_H

#include <memory>
#include <QWidget>
#include "field/DrawingAreaField.h"


class DrawingAreaView : public QWidget
{
	Q_OBJECT
public:
	explicit DrawingAreaView(QWidget *parent = 0);
	void setField(std::shared_ptr<DrawingAreaField> field);
	
public slots:
	void onPixelChanged(AddressOnDrawingArea address);
	
protected:
	void mousePressEvent(QMouseEvent *event) override;
	void paintEvent(QPaintEvent *event) override;
	
private:
	const size_t squareSize = 30;		// TODO: move to generalView class
	void drawGrid();
	void drawOnePixel(Pixel pixel);
	void drawAllPixels();
	
	void resizeDrawingArea(const QSize &newSize);
	int myPenWidth;
	QColor myPenColor;
	QImage image;
	QPoint lastPoint;
	
	std::shared_ptr<DrawingAreaField> field;
};

#endif // DRAWINGAREAVIEW_H
