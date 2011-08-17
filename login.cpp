#include "login.h"
#include "ui_login.h"
#include <QDataStream>
#include <QDateTime>

QDataStream& operator<<(QDataStream &stream,const QList<QNetworkCookie>& listCookies)
{
    stream <<quint32(listCookies.size());
    foreach(QNetworkCookie cookie,listCookies)
            stream << cookie.toRawForm();
    return stream;
}

QDataStream& operator>>(QDataStream &stream,QList<QNetworkCookie>& listCookies)
{
    QNetworkCookie networkCookie;
    listCookies.clear();
    int count;
    stream >>count;

    for (int i =0;i < count; i++){
        QByteArray byteArrary;
        stream >> byteArrary;
        QList<QNetworkCookie>  parseList= QNetworkCookie::parseCookies(byteArrary);
        if (!parseList.isEmpty()){
            foreach(QNetworkCookie cookie,parseList)
                    listCookies << cookie;
        }
        if (stream.atEnd())
                break;
    }
    return stream;
}


Login::Login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Login)
{
    QSettings settings("conf.ini",QSettings::IniFormat);

    qRegisterMetaTypeStreamOperators<QList<QNetworkCookie> >("QList<QNetworkCookie>");

    m_manager = new QNetworkAccessManager;
    ui->setupUi(this);
    ui->passwd->setEchoMode(QLineEdit::Password);

    settings.beginGroup("Email");
    ui->email->setText(settings.value("email").toString());
//    ui->passwd->setText(settings.value("passwd").toString());
    settings.endGroup();
  //  init();
    connect(ui->Btnlogin,SIGNAL(clicked()),this,SLOT(loginit()));
    connect(ui->BtnCancel,SIGNAL(clicked()),this,SLOT(hide()));
    connect(ui->Btnagain,SIGNAL(clicked()),this,SLOT(init()));
    connect(ui->email,SIGNAL(returnPressed()),ui->Btnlogin,SIGNAL(clicked()));
    connect(ui->passwd,SIGNAL(returnPressed()),ui->Btnlogin,SIGNAL(clicked()));
    connect(ui->ma,SIGNAL(returnPressed()),ui->Btnlogin,SIGNAL(clicked()));
    ui->Btnagain->hide();
    ui->ma->hide();
    ui->yanzhengma->hide();
    ui->Lma->hide();

    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::Tool );
//if ((ui->email->text()!="")&&(ui->passwd->text()!=""))
//      loginit();
    settings.beginGroup("Cookies");
    m_cookies = qvariant_cast< QList<QNetworkCookie> >(settings.value("cookies"));
    settings.endGroup();
}


Login::~Login()
{
    delete ui;
}

void Login::init()
{
    QNetworkRequest test;
    test.setUrl(QUrl("http://www.douban.com/accounts/login"));
    QNetworkAccessManager *mtest = new QNetworkAccessManager();
    connect(mtest,SIGNAL(finished(QNetworkReply*)),this,SLOT(testfinished(QNetworkReply*)));
    mtest->get(test);
    //    m_extraFunctionManager->get(test);
}

void Login::loginit()
{
//    qDebug()<<"loginit";
    m_extraFunctionManager = new QNetworkAccessManager();
    connect(m_extraFunctionManager,SIGNAL(finished(QNetworkReply*)), this, SLOT(extraNetworkFinished(QNetworkReply*)));

    QString captchasolution=ui->ma->text();
    QString email=ui->email->text();
    QString password = ui->passwd->text();
    QNetworkRequest r;
    r.setUrl(QUrl("http://www.douban.com/accounts/login"));
    r.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");
    r.setRawHeader("Host","www.douban.com");
    r.setRawHeader("Connection","Keep-Alive");
    QByteArray body;
//    if (captchasolution=="")
//        body =QString("form_email=%1&form_password=%2&remember=on&source=simple").arg(email,password).toUtf8();
//    else
        body = QString("captcha-id=%1&captcha-solution=%2&form_email=%3&form_password=%4&remember=on&source=simple").arg(captchaid,captchasolution,email,password).toUtf8();
    QByteArray exclued	= "=&";
   // qDebug()<<body;
    r_testAccountReply	= m_extraFunctionManager->post(r,body.toPercentEncoding(exclued));
 //   connect(r_testAccountReply,SIGNAL(finished()),this,SLOT(accountTestFinished()));
this->hide();
QSettings settings("conf.ini",QSettings::IniFormat);
settings.beginGroup("Email");
settings.setValue("email",ui->email->text());
//settings.setValue("passwd",ui->passwd->text());
settings.endGroup();

}

void Login::extraNetworkFinished(QNetworkReply* reply)
{
   // qDebug()<<"extraNetworkFinished";
    QTextCodec *codec = QTextCodec::codecForName("utf8");
    QString all = codec->toUnicode(reply->readAll());
//    ui->textBrowser->setText(all);
        // 获取Cookie


        QVariant list = reply->header(QNetworkRequest::SetCookieHeader);
        fmCookies = qvariant_cast<QList<QNetworkCookie> >(list);
        setCookie(fmCookies);

        if (all=="Your browser should have redirected you to http://www.douban.com/")
            emit succ("登录成功");
        else
            emit succ("登录失败");
}

void Login::setCookie(QList<QNetworkCookie>& list)
{
        m_cookies = list;

        for(int i=0;i<m_cookies.length();++i)
        {
                const QNetworkCookie& cc = m_cookies.at(i);
                if(cc.name() == "ue" || cc.name() == "sites")
                {
                        m_cookies.removeAt(i);
                        --i;
                        continue;
                }

                QNetworkCookie& cc_no_const = const_cast<QNetworkCookie&>(cc);
                cc_no_const.setDomain(".douban.fm");
        }


        QSettings settings("conf.ini",QSettings::IniFormat);
        settings.beginGroup("Cookies");
//        QList<QNetworkCookie> a = qvariant_cast< QList<QNetworkCookie> >(settings.value(QLatin1String("cookies")));
        settings.setValue("cookies",qVariantFromValue<QList<QNetworkCookie> >(m_cookies));
        settings.endGroup();
//        qDebug()<<a;
//        qDebug()<<QVariant::fromValue<QList<QNetworkCookie> >(m_cookies)<<'\n'<<qVariantFromValue<QList<QNetworkCookie> >(m_cookies).value<QList<QNetworkCookie> >();


        m_manager->cookieJar()->setCookiesFromUrl(m_cookies,QUrl("http://douban.fm"));
   //     qDebug()<<"已登录";

//        QNetworkRequest test;
//        test.setUrl(QUrl("http://douban.fm"));
//        QNetworkAccessManager *mtest = new QNetworkAccessManager();
//        connect(mtest,SIGNAL(finished(QNetworkReply*)),this,SLOT(testfinished(QNetworkReply*)));
//        mtest->cookieJar()->setCookiesFromUrl(m_cookies,QUrl("http://douban.fm"));
//        mtest->get(test);


//        QNetworkAccessManager *mtest = new QNetworkAccessManager();
//        mtest->cookieJar()->setCookiesFromUrl(cc_no_const,QUrl("http://douban.fm"));
}

void Login::testfinished(QNetworkReply *reply)
{
    QTextCodec *codec = QTextCodec::codecForName("utf8");
    QString all = codec->toUnicode(reply->readAll());
//    ui->textBrowser->setText(all);
//    ui->webView->setHtml(all);
//   qDebug()<<all;
    QString head = "captcha?id=";
    QString tail = "&amp;";
    int h = all.indexOf(head);
    int t = all.indexOf(tail);
    if (h!=-1)
    {
        ui->Btnagain->show();
        ui->Lma->show();
        ui->yanzhengma->show();
        ui->ma->show();
    }
    captchaid = all.mid(h+11,t-h-11);
   // qDebug()<<captchaid;
    QString lrc = "http://www.douban.com/misc/captcha?id=" + captchaid + "&size=s";
    QUrl url;
    url.setUrl(lrc);
  //  qDebug()<<lrc;
    Mamanager = new QNetworkAccessManager(this);  //新建QNetworkAccessManager对象
    connect(Mamanager,SIGNAL(finished(QNetworkReply*)),this,SLOT(downloadMa(QNetworkReply*)));
    Mamanager->get(QNetworkRequest(QUrl(url))); //发送请求

}

void Login::downloadMa(QNetworkReply *reply)
{
//    qDebug()<<"downloadMa";
    QImage image;
    image.loadFromData(reply->readAll());
    QPixmap pixmap(QPixmap::fromImage(image));
    ui->yanzhengma->setPixmap(pixmap);
}
