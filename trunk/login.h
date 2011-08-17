#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <QtNetwork>
#include <QtNetwork/QNetworkCookie>
#include <QTextCodec>
#include <QNetworkProxy>
#include <QVariant>

namespace Ui {
    class Login;
}

class Login : public QWidget
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = 0);
    ~Login();
    QList<QNetworkCookie> fmCookies;
    QList<QNetworkCookie> m_cookies;
signals:
    void succ(const QString&);

private:
    Ui::Login *ui;
    QNetworkAccessManager *m_extraFunctionManager;
    QNetworkAccessManager *m_manager;
    QNetworkAccessManager *Mamanager;
    QNetworkReply *r_testAccountReply;
    QString s_ckCookieValue;
    QString captchaid;
    void setCookie(QList<QNetworkCookie>& list);
public slots:
    void loginit();
    void extraNetworkFinished(QNetworkReply*);
    void testfinished(QNetworkReply*);
    void downloadMa(QNetworkReply *);
    void init();
};

#endif // LOGIN_H
