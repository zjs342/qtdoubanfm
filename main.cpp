#include <QtGui/QApplication>
#include "widget.h"
#include <QtDeclarative>
#include <QTextCodec>
#include <QVariant>
#include <QNetworkProxy>
#include "nativequickwidgets.h"


int main(int argc, char *argv[])
{
	//QTextCodec::setCodecForCStrings(QTextCodec::codecForName("GB2312"));
	QTextCodec *codec = QTextCodec::codecForName("System");
	QTextCodec::setCodecForLocale(codec);
	QTextCodec::setCodecForCStrings(codec);
	QTextCodec::setCodecForTr(codec);
	QApplication a(argc, argv);
	NativeQuickWidgets::qmlRegisterTypes();
	a.setWindowIcon(QIcon(":douban.ico"));
	Widget *w = new Widget;
	//QDeclarativeView mywidget;
	w->rootContext()->setContextProperty("widget",w);
	w->setSource(QUrl("qrc:ui.qml"));
	w->setWindowOpacity(0.9);
	w->setWindowTitle("豆瓣电台");
	w->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::Tool );
	w->show();
	QObject *rootObject = dynamic_cast<QObject*>(w->rootObject());
	QObject::connect((QObject*)w->engine(), SIGNAL(quit()), &a, SLOT(quit()));
	QObject::connect(w, SIGNAL(data(QVariant,QVariant)), rootObject, SLOT(updateData(QVariant,QVariant)));
	QObject::connect(w, SIGNAL(data2(QVariant,QVariant,QVariant)), rootObject, SLOT(updateData2(QVariant,QVariant,QVariant)));
	return a.exec();
}
