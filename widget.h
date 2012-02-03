#ifndef WIDGET_H
#define WIDGET_H

#include <QtGui/QWidget>
#include <QDebug>
#include <QMouseEvent>
#include <QtDeclarative/QDeclarativeView>
#include <QApplication>
#include <QDesktopWidget>
#include <QTime>
#include <QSystemTrayIcon>
#include <QSettings>
#include <QtNetwork>
#include <QAction>
#include <QMenu>
#include <QMessageBox>
// #include <phonon>
#include <phonon/mediaobject.h>
#include <phonon/audiooutput.h>
#include <phonon/volumeslider.h>
#include <phonon/seekslider.h>
#include <QStringList>
#include <QScriptEngine>
#include <QScriptValueIterator>
#include <QMap>
#include <QDesktopServices>
#include <QFile>
#include <QTextStream>
#include <song.h>
#include <login.h>
#include <myproxy.h>
#include "shortcut.h"
#include "lrcshow.h"

class Channel
{
	public:
        int id;
		QString name;
};

class Channeldj
{
	public:
        int id;
		QString name;
		int update;
		int num;
		Channel channel[50];
        QString iid;
};

class Channelpublic
{
	public:
		QString name;
        int id;
		int num;
		Channel channel[50];
};

class Channeldb
{
	public:
		QString id;
		QString name;
};

class Widget : public QDeclarativeView
{
	Q_OBJECT
		Q_PROPERTY(QString title READ title WRITE settitle NOTIFY titleChanged)
		Q_PROPERTY(QString album READ album WRITE setalbum NOTIFY albumChanged)
		Q_PROPERTY(QString artist READ artist WRITE setartist NOTIFY artistChanged)
		Q_PROPERTY(QString ttime READ ttime WRITE setttime NOTIFY ttimeChanged)
		Q_PROPERTY(QString pic READ pic WRITE setpic NOTIFY picChanged)
		Q_PROPERTY(QString playsource READ playsource WRITE setplaysource NOTIFY playsourceChanged)
		Q_PROPERTY(QString likesource READ likesource WRITE setlikesource NOTIFY likesourceChanged)
		Q_PROPERTY(int pb READ pb WRITE setpb NOTIFY pbChanged)
		Q_PROPERTY(int mystate READ mystate WRITE setmystate NOTIFY mystateChanged)
		Q_PROPERTY(QString cName READ cName WRITE setcName NOTIFY cNameChanged)
        Q_PROPERTY(int cNum READ cNum WRITE setcNum NOTIFY cNumChanged)
		Q_PROPERTY(bool fdesktop READ fdesktop WRITE setfdesktop NOTIFY fdesktopChanged)
		Q_PROPERTY(QString cType READ cType WRITE setcType NOTIFY cTypeChanged)
	public:
		Widget(QDeclarativeView *parent = 0);
		~Widget();
		QString title() const {return m_title;}
		void settitle(const QString a){if (a!=m_title) {m_title=a;emit titleChanged();}}
		QString album() const {return m_album;}
		void setalbum(const QString a){if (a!=m_album) {m_album=a;emit albumChanged();}}
		QString artist() const {return m_artist;}
		void setttime(const QString a){if (a!=m_ttime) {m_ttime=a;emit ttimeChanged();}}
		QString ttime() const {return m_ttime;}
		void setartist(const QString a){if (a!=m_artist) {m_artist=a;emit artistChanged();}}
		QString pic() const {return m_pic;}
		void setpic(const QString a){if (a!=m_pic) {m_pic=a;emit picChanged();}}
		QString likesource() const {return m_likesource;}
		void setlikesource(const QString a){if (a!=m_likesource) {m_likesource=a;emit likesourceChanged();}}
		QString playsource() const {return m_playsource;}
		void setplaysource(const QString a){if (a!=m_playsource) {m_playsource=a;emit playsourceChanged();}}
		int pb() const {return m_pb;}
		void setpb(const int a){if (a!=m_pb) {m_pb=a;emit pbChanged();}}
		bool fdesktop() const {return m_fdesktop;}
		void setfdesktop(const bool a){if (a!=m_fdesktop) {m_fdesktop=a;emit fdesktopChanged();}}
		int mystate() const {return m_mystate;}
		void setmystate(const int a) {m_mystate=a;emit mystateChanged();}
		QString cName() const {return m_cName;}
		void setcName(const QString a){if (a!=m_cName) {m_cName=a;emit cNameChanged();}}
		QString cType() const {return m_cType;}
		void setcType(const QString a){if (a!=m_cType) {m_cType=a;emit cTypeChanged();}}
        int cNum() const {return m_cNum;}
        void setcNum(const int a){if (a!=m_cNum) {m_cNum=a;emit cNumChanged();}}
signals:
		void titleChanged();
		void albumChanged();
		void artistChanged();
		void ttimeChanged();
		void picChanged();
		void fdesktopChanged();
		void playsourceChanged();
		void likesourceChanged();
		void mystateChanged();
		void pbChanged();
		void cNameChanged();
		void cNumChanged();
		void cTypeChanged();
		void data(QVariant,QVariant);
		void data2(QVariant,QVariant,QVariant);
	private:
		QList<QString> m_historyIds;
		QList<char> m_historyTypes;
		QString m_title;
		QString m_album;
		QString m_artist;
		QString m_ttime;
		QString m_ttick;
		bool m_fdesktop;
		QString m_pic;
		int m_pb;
		QString m_cName;
        int m_cNum;
		QString m_cType;
		int listNum;
		qint64 tttime;
		QString m_playsource;
		QString m_albumsource;
		QString m_source;
		QString m_likesource;
		Login *loginwidget;
		MyProxy *proxywidget;
		Shortcut *shortcutwidget;
		char type;
		int m_mystate;
		int dbfmNum,totlenum;
		int back;
		QPoint dragPosition;
		int MM;
		bool m_like;
        QString e_channel;
		QUrl fmurl;
		Song nowPlaySong;
		Song nowPlayList[5];
		Song dbfm[250];
		QSystemTrayIcon *trayIcon;
		QList<Phonon::MediaSource> sources;
		Phonon::MediaObject *mediaObject;
		Phonon::AudioOutput *audioOutput;
		Phonon::VolumeSlider *volumeSlider;
		Phonon::SeekSlider *seekSlider;
		void loadIni();
		void uiInit();
		void phononInit();
		void netInit();
		void songInit(QString json);
		void createTrayIcon();
		void trayIconmenu();
		void onSongStatus();
		void addFiles();
		void reportPlayed();
		void requireList(char);
		Channelpublic channelpublic[50];
		int channelNum;
		Channeldj channeldj[50];
		int channeldjNum;
		int channelCate;
		Channeldb channeldb[50];
		int channeldbNum;
		QAction* quitAction;
		QAction* myabout;
		QAction* mylogin;
		QAction* myproxy;
		QAction* myshortcut;
		QAction* mylikeit;
		QAction* mytrashit;
		QAction* mynextfile;
		LRCshow *lrcshow;
		public slots:
			void moveThis();
		void movePos(int,int);
		void enter();
		void messageAbout();
		void aboutToFinish();
		void finished();
		void sourceChanged(const Phonon::MediaSource &source);
		void tick(qint64);
		void ttick(qint64);
		void downloadList(QNetworkReply *);
		void playPause();
		void nextFile();
		void lastFile(int);
		void lastFile1(){lastFile(1);}
		void lastFile2(){lastFile(2);}
		void lastFile3(){lastFile(3);}
		void lastFile4(){lastFile(4);}
		void lastFile5(){lastFile(5);}
		void minit();
		void trashIt();
		void likeIt();
		void likeItit();
		void openIt();
		void quitIt();
		void logindb();
		void showMessage(const QString &s);
		void iconActivated(QSystemTrayIcon::ActivationReason reason);
		void channelInit();
		void downloadChannel(QNetworkReply*);
		void downloadSong();
		void downloadSongfinish(QNetworkReply*);
		void setmystate2(int a){ if (a!=2) {back=a; setmystate(2);} else setmystate(back); }
		void search(QString);
		void searchfinish(QNetworkReply *);
		void searchfinish2(QNetworkReply *);
		void updateData(QString,int);
		void updateData2(QString,int,int);
		void changeChannel(QString,int);
        void changeChannel2(QString);
        void Mdesktop(bool);
};

#endif // WIDGET_H
