#include "lrcdesktop.h"

LRCDesktop::LRCDesktop(QWidget *parent) : QWidget(parent)
{
	QSettings settings("conf.ini", QSettings::IniFormat);
	settings.beginGroup("LRCProperty");
	this->restoreGeometry(settings.value("geometry").toByteArray());
	settings.endGroup();
	font = new QFont("ºÚÌå", 20);
	QFontMetrics metrics(*font);
	QString list=tr("¶¹°êµçÌ¨ By Spring");
	r = metrics.boundingRect(list);
	this->resize(r.size());
	//    left = QRect(0, 0, (int)left.width(), r.height());
	//    right = QRect(left.width(), 0, r.width()-left.width(), r.height());
	last = r.width();
	bmp = QBitmap(this->size());
	bmp.fill();
	QPainter p(&bmp);
	path = new QPainterPath;
	path->addText(0.0, metrics.ascent(), *font, list);
	p.setPen(Qt::red);
	p.setBrush(Qt::red);
	p.setFont(*font);
	p.drawPath(*path);
	setMask(bmp);
	//    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::Tool );
	this->setWindowFlags(Qt::WindowStaysOnTopHint | Qt::Tool);
}

LRCDesktop::~LRCDesktop()
{

}

void LRCDesktop::paintEvent(QPaintEvent *e)
{
	QPixmap pmp(r.size());
	QPainter p(&pmp);

	p.setFont(*font);
	p.setPen(Qt::red);
	p.setBrush(Qt::red);
	p.setClipRect(0, 0, r.width(), r.height());
	p.drawPath(*path);

	/*    p.setPen(Qt::green);
	      p.setBrush(Qt::green);
	      p.setClipRect(right);
	      p.drawPath(*path);
	 */
	QPainter pWidget(this);
	pWidget.drawPixmap(0, 0, pmp);
}

void LRCDesktop::showWord(QString str)
{
	QFontMetrics metrics(*font);
	r = metrics.boundingRect(str);
	this->resize(r.size());

	bmp = QBitmap(this->size());
	bmp.fill();
	QPainter p(&bmp);
	path = new QPainterPath;
	path->addText(0.0, metrics.ascent(), *font, str);
	path->closeSubpath();
	p.setPen(Qt::red);
	p.setBrush(Qt::red);
	p.setFont(*font);
	p.drawPath(*path);
	setMask(bmp);
	move(this->x()-int((r.width()-last)/2), this->y());
	last=r.width();
}

void LRCDesktop::mousePressEvent(QMouseEvent* event)
{
	if ((event->button() == Qt::RightButton)||(event->button() == Qt::LeftButton))
	{
		dragPosition = event->globalPos() - frameGeometry().topLeft();
		event->accept();
	}
}

void LRCDesktop::mouseMoveEvent(QMouseEvent *event)
{
	if ((event->buttons() == Qt::RightButton)||(event->buttons() == Qt::LeftButton))
	{
		move(event->globalPos() - dragPosition);
		event->accept();
	}
}
