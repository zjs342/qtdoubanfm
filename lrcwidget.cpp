#include "lrcwidget.h"

LRCwidget::LRCwidget(QWidget *parent) :
	QWidget(parent)
{
}

void LRCwidget::mousePressEvent(QMouseEvent* event)
{
	if ((event->button() == Qt::RightButton)||(event->button() == Qt::LeftButton))
	{
		dragPosition = event->globalPos() - frameGeometry().topLeft();
		event->accept();
	}
}

void LRCwidget::mouseMoveEvent(QMouseEvent *event)
{
	if ((event->buttons() == Qt::RightButton)||(event->buttons() == Qt::LeftButton))
	{
		move(event->globalPos() - dragPosition);
		event->accept();
	}
}
