#include "lrcdesktop.h"

LRCDesktop::LRCDesktop(QWidget *parent) : QLabel(parent)
{
    QSettings settings("conf.ini", QSettings::IniFormat);
    settings.beginGroup("LRCProperty");
    this->restoreGeometry(settings.value("geometry").toByteArray());
    settings.endGroup();

    this->setWindowFlags(Qt::SubWindow |Qt::FramelessWindowHint| Qt::WindowStaysOnTopHint);
    this->resize(1024,60);
    this->setText(tr("豆瓣电台 By Spring"));
    this->setAttribute(Qt::WA_TranslucentBackground);//背景透明

    this->setCursor(Qt::OpenHandCursor);
//    this->setAlignment(Qt::AlignCenter);
//    lrcWidth = 0;
//    font = new QFont("微软雅黑", 25);
//    QFontMetrics metrics(*font);
//    QString list=tr("豆瓣电台 By Spring");
//    r = metrics.boundingRect(list);
//    this->resize(r.size());
//    //    left = QRect(0, 0, (int)left.width(), r.height());
//    //    right = QRect(left.width(), 0, r.width()-left.width(), r.height());
//    last = r.width();
//    bmp = QBitmap(this->size());
//    bmp.fill();

//    path = new QPainterPath;
//    path->addText(0.0, metrics.ascent(), *font, list);

//    QPainter painter(&bmp);
////    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
////    //使用该行代码可以实现反锯齿，使歌词显示更漂亮，但是会明显增加CPU占用率
////    //QFont font(tr("Times New Roman"),30,QFont::Bold);
//    painter.setBrush(Qt::black);
//    painter.setPen(Qt::black);
////    painter.setFont(*font);
//    painter.drawPath(*path);

//    setMask(bmp);

//        this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::Tool );
//    //this->setWindowFlags(Qt::WindowStaysOnTopHint | Qt::Tool);
}

LRCDesktop::~LRCDesktop()
{

}

void LRCDesktop::paintEvent(QPaintEvent *e)
{
//    QPixmap pmp(r.size());
    //qDebug()<<text();
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    //使用该行代码可以实现反锯齿，使歌词显示更漂亮，但是会明显增加CPU占用率
    QFont font(tr("微软雅黑"),30,QFont::Bold);
    QLinearGradient lg(0,20,0,50);
    lg.setColorAt(0,QColor(0,170,255,255));
    lg.setColorAt(0.2,QColor(61,200,190,250));
    lg.setColorAt(0.5,QColor(85,255,255,255));
    lg.setColorAt(0.8,QColor(61,200,190,250));
    lg.setColorAt(1,QColor(0,170,255,255));
    painter.setBrush(lg);
    painter.setPen(Qt::blue);
    painter.setFont(font);

    QFontMetrics metrics(font);
    r = metrics.boundingRect(text());

    QPainterPath textPath;
    textPath.addText((this->width()-r.width())/2,50,font,text());
    painter.drawPath(textPath);
    //painter.drawText(0,14,0,50,Qt::AlignCenter,text());

//    QFontMetrics metrics(font);
//    r = metrics.boundingRect(text());
//    this->resize(r.size());


//    length = textPath.currentPosition().x();
   // move(this->x()-int((this.width()-last)/2), this->y());

     //  last=this.width();
   // painter.setPen(Qt::yellow);
   // painter.drawText(0,14,0,50,Qt::AlignCenter,text());


//    painter.setClipRect(0, 0, r.width(), r.height());
//    painter.drawPath(*path);
//    setMask(pmp);
//    QPainter pWidget(this);
//    pWidget.drawPixmap(0, 0, pmp);
}

void LRCDesktop::showWord(QString str)
{
//    QFontMetrics metrics(*font);
//    r = metrics.boundingRect(str);
//    this->resize(r.size());

//    bmp = QBitmap(this->size());
//    bmp.fill();

//    path = new QPainterPath;
//    path->addText(0.0, metrics.ascent(), *font, str);
//    path->closeSubpath();

//    QPainter painter(&bmp);
//    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

//    QLinearGradient lg(0,20,0,50);
//    lg.setColorAt(0,QColor(0,170,255,255));
//    lg.setColorAt(0.2,QColor(61,214,191,250));
//    lg.setColorAt(0.5,QColor(85,255,255,255));
//    lg.setColorAt(0.8,QColor(61,214,191,250));
//    lg.setColorAt(1,QColor(0,170,255,255));
//    painter.setBrush(lg);
//    painter.setPen(Qt::NoPen);
//    painter.setFont(*font);
//    painter.drawPath(*path);
//    setMask(bmp);
//    move(this->x()-int((r.width()-last)/2), this->y());
//    last=r.width();
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
