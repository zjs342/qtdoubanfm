#ifndef LRCSHOW_H
#define LRCSHOW_H

#include <QTextEdit>
#include <QString>
#include <QObject>
#include <QFile>
#include <QTextStream>
#include <QMap>
#include <QTextBlock>
#include <QPalette>
#include <QtNetwork>
#include <QUrl>
#include <QDesktopServices>
#include <QMouseEvent>
#include <QDebug>
#include "lrcwidget.h"
#include "lrcdesktop.h"

class LRCshow : public QTextEdit
{
	Q_OBJECT
	public:
		explicit LRCshow(LRCwidget *parent = 0);
		QString surl;
		LRCDesktop *lrcdesktop;
		public slots:
			void showWord(int time);
		void init(const QString &title,const QString &artist);
	private:
		QMap<int,QString> *map;
		QMap<int,int> *posmap;
		QPoint dragPosition;
		void getHeader(const char *str, QString &des);
		void getTime(QString line);
		void textshow();
		QNetworkAccessManager *manager;

		private slots:
			void lrcresearch(QNetworkReply *);
		void downloadlrc(QNetworkReply *);
		void search();

	protected:
		void mouseMoveEvent(QMouseEvent *);
		void mousePressEvent(QMouseEvent *);
		void mouseDoubleClickEvent(QMouseEvent *);
		void mouseReleaseEvent(QMouseEvent *);
		void contextMenuEvent(QContextMenuEvent *);
};

#endif // LRCSHOW_H
