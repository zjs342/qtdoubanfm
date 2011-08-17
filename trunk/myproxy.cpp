#include "myproxy.h"
#include "ui_myproxy.h"

MyProxy::MyProxy(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyProxy)
{
    ui->setupUi(this);
    ui->Password->setEchoMode(QLineEdit::Password);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::Tool );
    //proxy.setType(QNetworkProxy::HttpProxy);
    QSettings settings("conf.ini",QSettings::IniFormat);
    settings.beginGroup("Proxy");
    QString hh = settings.value("hosttype").toString();
    if ((hh!="None")&(hh!=""))
    {
        if (hh=="HTTP")
        {
            ui->Type->setCurrentIndex(1);
            proxy.setType(QNetworkProxy::HttpProxy);
        }
        else if (hh=="Socks5")
        {
            ui->Type->setCurrentIndex(2);
            proxy.setType(QNetworkProxy::Socks5Proxy);
        }
        else if (hh=="Caching")
        {
            ui->Type->setCurrentIndex(3);
            proxy.setType(QNetworkProxy::HttpCachingProxy);
        }
        ui->HostName->setText(settings.value("hostname").toString());
        proxy.setHostName(ui->HostName->text());
        QString str = settings.value("port").toString();
        ui->Port->setText(str);
        proxy.setPort(quint16(str.toInt()));
        ui->User->setText(settings.value("user").toString());
        proxy.setUser(ui->User->text());
        ui->Password->setText(settings.value("password").toString());
        proxy.setPassword(ui->Password->text());
        QNetworkProxy::setApplicationProxy(proxy);
    }
    settings.endGroup();
connect(ui->BtnOK,SIGNAL(clicked()),this,SLOT(init()));
connect(ui->BtnCancel,SIGNAL(clicked()),this,SLOT(hide()));
connect(ui->HostName,SIGNAL(returnPressed()),ui->BtnOK,SIGNAL(clicked()));
connect(ui->User,SIGNAL(returnPressed()),ui->BtnOK,SIGNAL(clicked()));
connect(ui->Password,SIGNAL(returnPressed()),ui->BtnOK,SIGNAL(clicked()));
connect(ui->Port,SIGNAL(returnPressed()),ui->BtnOK,SIGNAL(clicked()));
}

MyProxy::~MyProxy()
{

    delete ui;
}

void MyProxy::init()
{
    QString hh = ui->Type->currentText();
     this->hide();
     if (hh=="None")
        proxy.setType(QNetworkProxy::NoProxy);
    else if (hh=="HTTP")
        proxy.setType(QNetworkProxy::HttpProxy);
    else if (hh=="Socks5")
        proxy.setType(QNetworkProxy::Socks5Proxy);
    else if (hh=="Caching")
        proxy.setType(QNetworkProxy::HttpCachingProxy);

    proxy.setHostName(ui->HostName->text());
    proxy.setPort(quint16(QString(ui->Port->text()).toInt()));
    proxy.setUser(ui->User->text());
    proxy.setPassword(ui->Password->text());
    QNetworkProxy::setApplicationProxy(proxy);

    QSettings settings("conf.ini",QSettings::IniFormat);
    settings.beginGroup("Proxy");
    settings.setValue("hosttype",ui->Type->currentText());
    settings.setValue("hostname",ui->HostName->text());
    settings.setValue("port",ui->Port->text());
    settings.setValue("user",ui->User->text());
    settings.setValue("password",ui->Password->text());
    settings.endGroup();

}
