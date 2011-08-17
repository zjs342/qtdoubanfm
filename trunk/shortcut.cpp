#include "shortcut.h"
#include "ui_shortcut.h"

Shortcut::Shortcut(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Shortcut)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::Tool );

    connect(ui->Btnok,SIGNAL(clicked()),this,SLOT(init()));
    connect(ui->BtnCancel,SIGNAL(clicked()),this,SLOT(mcancel()));

    m_next = new QxtGlobalShortcut(this);
    m_like = new QxtGlobalShortcut(this);
    m_dislike = new QxtGlobalShortcut(this);
    m_min = new QxtGlobalShortcut(this);;
    m_play = new QxtGlobalShortcut(this);
    m_down = new QxtGlobalShortcut(this);
    //m_lrc = new QxtGlobalShortcut(this);
    m_desktop = new QxtGlobalShortcut(this);
    //m_list = new QxtGlobalShortcut(this);
    m_close = new QxtGlobalShortcut(this);

    QSettings settings("conf.ini",QSettings::IniFormat);
    settings.beginGroup("ShortCut");
    ui->Lnext->setText(settings.value("Next").toString());
    ui->Llike->setText(settings.value("Like").toString());
    ui->Ldislike->setText(settings.value("Dislike").toString());
    ui->Lmin->setText(settings.value("Min").toString());
    ui->Lplay->setText(settings.value("Play").toString());
    ui->Ldown->setText(settings.value("Down").toString());
    //ui->Llrc->setText(settings.value("LRC").toString());
    ui->Ldesktop->setText(settings.value("Desktop").toString());
    //ui->Llist->setText(settings.value("List").toString());
    ui->Lclose->setText(settings.value("Close").toString());
    settings.endGroup();

    m_next->setShortcut(QKeySequence(ui->Lnext->text()));
    m_like->setShortcut(QKeySequence(ui->Llike->text()));
    m_dislike->setShortcut(QKeySequence(ui->Ldislike->text()));
    m_min->setShortcut(QKeySequence(ui->Lmin->text()));
    m_play->setShortcut(QKeySequence(ui->Lplay->text()));
    m_down->setShortcut(QKeySequence(ui->Ldown->text()));
   // m_lrc->setShortcut(QKeySequence(ui->Llrc->text()));
    m_desktop->setShortcut(QKeySequence(ui->Ldesktop->text()));
    //m_list->setShortcut(QKeySequence(ui->Llist->text()));
    m_close->setShortcut(QKeySequence(ui->Lclose->text()));

    //    connect(m_like,SIGNAL(activated()),this,SLOT(BtnLike_toggled()));
      //  connect(m_del,SIGNAL(activated()),this,SLOT(BtnTrash_clicked()));
//        connect(m_next,SIGNAL(activated()),this,SLOT(nextFile()));
    //    connect(m_play,SIGNAL(activated()),this,SLOT(togglePlay()));
    //    connect(m_dislike,SIGNAL(activated()),this,SLOT(BtnLike_toggled()));
    //    connect(m_show,SIGNAL(activated()),lrcshow->lrcdesktop,SLOT(setVisible(bool)));
}

Shortcut::~Shortcut()
{
    delete ui;
}
void Shortcut::init()
{
    QSettings settings("conf.ini",QSettings::IniFormat);
    settings.beginGroup("ShortCut");
    settings.setValue("Next",ui->Lnext->text());
    settings.setValue("Like",ui->Llike->text());
    settings.setValue("Dislike",ui->Ldislike->text());
    settings.setValue("Min",ui->Lmin->text());
    settings.setValue("Play",ui->Lplay->text());
    settings.setValue("Down",ui->Ldown->text());
    //settings.setValue("LRC",ui->Llrc->text());
    settings.setValue("Desktop",ui->Ldesktop->text());
    //settings.setValue("List",ui->Llist->text());
    settings.setValue("Close",ui->Lclose->text());
    settings.endGroup();

    m_next->setShortcut(QKeySequence(ui->Lnext->text()));
    m_like->setShortcut(QKeySequence(ui->Llike->text()));
    m_dislike->setShortcut(QKeySequence(ui->Ldislike->text()));
    m_min->setShortcut(QKeySequence(ui->Lmin->text()));
    m_play->setShortcut(QKeySequence(ui->Lplay->text()));
    m_down->setShortcut(QKeySequence(ui->Ldown->text()));
    //m_lrc->setShortcut(QKeySequence(ui->Llrc->text()));
    //m_desktop->setShortcut(QKeySequence(ui->Ldesktop->text()));
    //m_list->setShortcut(QKeySequence(ui->Llist->text()));
    m_close->setShortcut(QKeySequence(ui->Lclose->text()));
    this->hide();
}

void Shortcut::mcancel()
{

    QSettings settings("conf.ini",QSettings::IniFormat);
    settings.beginGroup("ShortCut");
    ui->Lnext->setText(settings.value("Next").toString());
    ui->Llike->setText(settings.value("Like").toString());
    ui->Ldislike->setText(settings.value("Dislike").toString());
    ui->Lmin->setText(settings.value("Min").toString());
    ui->Lplay->setText(settings.value("Play").toString());
    ui->Ldown->setText(settings.value("Down").toString());
    //ui->Llrc->setText(settings.value("LRC").toString());
    ui->Ldesktop->setText(settings.value("Desktop").toString());
    //ui->Llist->setText(settings.value("List").toString());
    ui->Lclose->setText(settings.value("Close").toString());
    settings.endGroup();

    m_next->setShortcut(QKeySequence(ui->Lnext->text()));
    m_like->setShortcut(QKeySequence(ui->Llike->text()));
    m_dislike->setShortcut(QKeySequence(ui->Ldislike->text()));
    m_min->setShortcut(QKeySequence(ui->Lmin->text()));
    m_play->setShortcut(QKeySequence(ui->Lplay->text()));
    m_down->setShortcut(QKeySequence(ui->Ldown->text()));
    //m_lrc->setShortcut(QKeySequence(ui->Llrc->text()));
    m_desktop->setShortcut(QKeySequence(ui->Ldesktop->text()));
   // m_list->setShortcut(QKeySequence(ui->Llist->text()));
    m_close->setShortcut(QKeySequence(ui->Lclose->text()));

    connect(ui->Btnok,SIGNAL(clicked()),this,SLOT(init()));
    connect(ui->BtnCancel,SIGNAL(clicked()),this,SLOT(mshow()));
    connect(ui->Lnext,SIGNAL(returnPressed()),ui->Btnok,SIGNAL(clicked()));
    connect(ui->Llike,SIGNAL(returnPressed()),ui->Btnok,SIGNAL(clicked()));
    connect(ui->Ldislike,SIGNAL(returnPressed()),ui->Btnok,SIGNAL(clicked()));
    connect(ui->Lmin,SIGNAL(returnPressed()),ui->Btnok,SIGNAL(clicked()));
    connect(ui->Lplay,SIGNAL(returnPressed()),ui->Btnok,SIGNAL(clicked()));
    connect(ui->Ldown,SIGNAL(returnPressed()),ui->Btnok,SIGNAL(clicked()));
    //connect(ui->Llrc,SIGNAL(returnPressed()),ui->Btnok,SIGNAL(clicked()));
    connect(ui->Ldesktop,SIGNAL(returnPressed()),ui->Btnok,SIGNAL(clicked()));
    //connect(ui->Llist,SIGNAL(returnPressed()),ui->Btnok,SIGNAL(clicked()));
    connect(ui->Lclose,SIGNAL(returnPressed()),ui->Btnok,SIGNAL(clicked()));

    this->hide();
}

void Shortcut::mshow()
{
//qDebug()<<"mshow";

    m_next->setShortcut(QKeySequence(""));
    m_like->setShortcut(QKeySequence(""));
    m_dislike->setShortcut(QKeySequence(("")));
    m_min->setShortcut(QKeySequence(("")));
    m_play->setShortcut(QKeySequence(("")));
    m_down->setShortcut(QKeySequence(("")));
   // m_lrc->setShortcut(QKeySequence(("")));
    m_desktop->setShortcut(QKeySequence(("")));
    //m_list->setShortcut(QKeySequence(("")));
    m_close->setShortcut(QKeySequence(("")));

    this->show();
}
