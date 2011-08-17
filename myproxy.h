#ifndef MYPROXY_H
#define MYPROXY_H

#include <QWidget>
#include <QNetworkProxy>
#include <QSettings>
#include <QDebug>

namespace Ui {
    class MyProxy;
}

class MyProxy : public QWidget
{
    Q_OBJECT

public:
    explicit MyProxy(QWidget *parent = 0);
    ~MyProxy();

private:
    Ui::MyProxy *ui;
    QNetworkProxy proxy;

public slots:
    void init();
};

#endif // MYPROXY_H
