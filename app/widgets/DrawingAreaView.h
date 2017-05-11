#ifndef DRAWINGAREAVIEW_H
#define DRAWINGAREAVIEW_H

#include <QWidget>

class DrawingAreaView : public QWidget
{
	Q_OBJECT
public:
	explicit DrawingAreaView(QWidget *parent = 0);
protected:
	void mousePressEvent(QMouseEvent *event) override;
	void paintEvent(QPaintEvent *event) override;
	
public slots:
private:
	const int squareSize = 30;
	void drawGrid();
	
	void resizeDrawingArea(const QSize &newSize);
	int myPenWidth;
	QColor myPenColor;
	QImage image;
	QPoint lastPoint;
};

#endif // DRAWINGAREAVIEW_H
