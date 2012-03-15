#ifndef LRCDesktop_H
#define LRCDesktop_H

#include <QLabel>
#include <QBitmap>
#include <QPainterPath>
#include <QPainter>
#include <QDebug>
#include <QMouseEvent>
#include <QSettings>

class LRCDesktop : public QLabel
{
	Q_OBJECT
	public:
		explicit LRCDesktop(QWidget *parent = 0);
		~LRCDesktop();
		void showWord(QString str);
	private:
//		QFont *font;
//		QPainterPath *path;
        QRect r;
//		QBitmap bmp;
//		QRect left;
//		QRect right;
        QPoint dragPosition;
//		int last;
//        qreal length;
//        qreal lrcWidth;

	protected:
        virtual void paintEvent(QPaintEvent *e);
		void mouseMoveEvent(QMouseEvent *);
		void mousePressEvent(QMouseEvent *);

		public slots:

};

#endif // LRCDesktop_H
