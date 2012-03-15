#include "lrcshow.h"

int beforelrc=11;
LRCshow::LRCshow(LRCwidget *parent) :
	QTextEdit(parent)
{
	lrcdesktop = new LRCDesktop;
	this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	//    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	this->document()->setDefaultTextOption(QTextOption(Qt::AlignHCenter));
	this->setReadOnly(true);
	QPalette p;
	QColor back(204, 204, 204);
	p.setColor(QPalette::Base, back);    //背景色, 默认是白色的
	this->setPalette(p);
	p.setColor(QPalette::Text, QColor(77, 100, 102));// 文字的前景色
	this->setPalette(p);
	p.setColor(QPalette::Highlight, back);// 被选中后文字的背景色
	this->setPalette(p);
	p.setColor(QPalette::HighlightedText, Qt::white);// 被选中后文字的前景色
	this->setPalette(p);
}


void LRCshow::showWord(int time)
{
	if (map->contains(time))
	{
		//this->setText(map->value(time));
		QTextCursor tc = textCursor();
		int pos = this->document()->findBlockByLineNumber(posmap->value(time)+beforelrc).position();
		tc.setPosition(pos, QTextCursor::MoveAnchor);
		this->setTextCursor(tc);

		pos = this->document()->findBlockByLineNumber(posmap->value(time)+1).position();
		tc.setPosition(pos, QTextCursor::MoveAnchor);
		this->setTextCursor(tc);
		this->moveCursor(QTextCursor::EndOfLine, QTextCursor::KeepAnchor);
        lrcdesktop->setText(this->textCursor().selectedText());
        //lrcdesktop->showWord(this->textCursor().selectedText());
		//        qDebug()<<time<<posmap->value(time)<<map->value(time);
	}
}

void LRCshow::getHeader(const char *str, QString &des)
{
	des = des.remove(str);
	des = des.remove("]");
}

void LRCshow::getTime(QString line)
{
	//    qDebug()<<line;
	if(line.startsWith("["))
	{
		int findex = line.indexOf("]");
		QString t = line.mid(1, findex - 1);
		QString mm = t.mid(0, 2);
		QString ss = t.mid(3, 2);
		int m = mm.toInt();
		int s = ss.toInt();
		int time = m*60*1000 + s*1000;
		t = line.mid(findex + 1);
		int index = t.lastIndexOf("]");
		if(index < 0)
		{
			map->insert(time, t);
		}
		else
		{
			t = t.mid(index + 1);
			map->insert(time, t);
			t = line.mid(findex + 1);
			getTime(t);
		}
	}
}

void LRCshow::init(const QString &title, const QString &artist)
{
	map = new QMap<int, QString>();
	posmap = new QMap<int, int>();

	//  QString url = QString("http://mp3.sogou.com/lyric.so?query=%1 %2").arg(title, artist);
	//   QUrl urlEn = QUrl::fromEncoded(url.toLocal8Bit());

	QString url = QString("http://mp3.youdao.com/search?q=%1+%2&t=LRC").arg(title, artist);
	//    QUrl urlEn = QUrl(QUrl(url).toEncoded());
	QUrl urlEn = QUrl(url);
	//    qDebug()<<urlEn;

	manager = new QNetworkAccessManager(this);
	connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(lrcresearch(QNetworkReply*)));
	manager->get(QNetworkRequest(urlEn));
}

void LRCshow::textshow()
{
	int i;
	this->clear();
	this->append("\n");
	for (i=1;i<beforelrc;i++)
		this->append("");
	QMap<int, QString>::iterator it;
	for (it=map->begin();it!=map->end();++it)
	{
		posmap->insert(it.key(), i);
		this->append(it.value());
		i++;
	}
	for (i=0;i<beforelrc;i++)
		this->append("");
	this->moveCursor(QTextCursor::Start, QTextCursor::MoveAnchor);
}

void LRCshow::lrcresearch(QNetworkReply *reply)  //当回复结束后
{
	//    QString all = codec->toUnicode(reply->readAll());
	QTextCodec *codec = QTextCodec::codecForName("utf-8");
	QString all = codec->toUnicode(reply->readAll());
	//    qDebug()<<all;
	//    QString head = "downlrc.jsp?tGroupid=";
	//    QString tail = "uigs=\"lyric_down";
	QString head = "/lyric?d=";
	QString tail = "target=";
	int h = all.indexOf(head);
	int t = all.indexOf(tail, h);
	//    qDebug()<<h<<" "<<t;
	if (h==-1) return;
	QString lrc = all.mid(h, t-h-2);
	lrc= "http://mp3.youdao.com" + lrc;
	//    lrc = "http://mp3.sogou.com/" + lrc;
	//    qDebug()<<lrc;
	manager = new QNetworkAccessManager(this);
	connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(downloadlrc(QNetworkReply*)));
	manager->get(QNetworkRequest(QUrl(lrc)));
	reply->deleteLater();   //最后要释放reply对象
}

void LRCshow::downloadlrc(QNetworkReply *reply)
{
	//    QTextCodec *codec = QTextCodec::codecForName("gb18030");
	QTextCodec *codec = QTextCodec::codecForName("utf-8");
	QString all = codec->toUnicode(reply->readAll());
	//    QTextEdit temp(all);
	//    all=temp.toPlainText();
	//    qDebug()<<all;
	int h=0, t=0;
	QString tail = "\n";
	QString s;
	//    qDebug()<<s;

	h = t;
	t = all.indexOf(tail, h);
	h = t+1;
	t = all.indexOf(tail, h);

	tail = "<br/>";

	h = t + 1;
	t = all.indexOf(tail, h);
	s=all.mid(h, t-h);
	//    qDebug()<<h<<" "<<" "<<t<<" "<<s;


	//    while(!reply->atEnd())
	while (t!=-1)
	{
		//        QString s = codec->toUnicode(reply->readLine());
		if(s.length()<4)
		{
			h = t + 1;
			t = all.indexOf(tail, h);
			s=all.mid(h+4, t-h-4);
			//            qDebug()<<h<<" "<<" "<<t<<" "<<s;
			continue;
		}
		if(s.startsWith("[ti:"))
		{
			getHeader("[ti:", s);
			map->insert(0, s);
			h = t + 1;
			t = all.indexOf(tail, h);
			s=all.mid(h+4, t-h-4);
			//            qDebug()<<h<<" "<<" "<<t<<" "<<s;
			continue;
		}
		else if(s.startsWith("[ar:"))
		{
			getHeader("[ar:", s);
			map->insert(1000, s);
			h = t + 1;
			t = all.indexOf(tail, h);
			s=all.mid(h+4, t-h-4);
			//          qDebug()<<h<<" "<<" "<<t<<" "<<s;
			continue;
		}
		else if(s.startsWith("[al:"))
		{
			getHeader("[al:", s);
			map->insert(2000, s);
			h = t + 1;
			t = all.indexOf(tail, h);
			s=all.mid(h+4, t-h-4);
			//          qDebug()<<h<<" "<<" "<<t<<" "<<s;
			continue;
		}
		else if(s.startsWith("[by:"))
		{
			getHeader("[by:", s);
			map->insert(3000, s);
			h = t + 1;
			t = all.indexOf(tail, h);
			s=all.mid(h+4, t-h-4);
			//         qDebug()<<h<<" "<<" "<<t<<" "<<s;
			continue;
		}
		else
		{
			getTime(s);
			h = t + 1;
			t = all.indexOf(tail, h);
			s=all.mid(h+4, t-h-4);
			//         qDebug()<<h<<" "<<" "<<t<<" "<<s;
		}
	}
	textshow();


}

void LRCshow::mousePressEvent(QMouseEvent* event)
{
	QWidget::mousePressEvent(event);
}

void LRCshow::mouseMoveEvent(QMouseEvent *event)
{
	QWidget::mouseMoveEvent(event);
}
void LRCshow::mouseDoubleClickEvent(QMouseEvent *event)
{
	QWidget::mouseDoubleClickEvent(event);
}
void LRCshow::mouseReleaseEvent(QMouseEvent *event)
{
	QWidget::mouseReleaseEvent(event);
}
void LRCshow::contextMenuEvent(QContextMenuEvent *event)
{

}

void LRCshow::search()
{
	QUrl urlEn = QUrl::fromEncoded(surl.toLocal8Bit());
	//    qDebug()<<urlEn;
	QDesktopServices::openUrl(urlEn);
}
