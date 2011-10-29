#ifndef LRCWIDGET_H
#define LRCWIDGET_H

#include <QWidget>
#include <QMouseEvent>

class LRCwidget : public QWidget
{
	Q_OBJECT
	public:
		explicit LRCwidget(QWidget *parent = 0);
	private:
		QPoint dragPosition;
	protected:
		void mouseMoveEvent(QMouseEvent *);
		void mousePressEvent(QMouseEvent *);

};

#endif // LRCWIDGET_H
