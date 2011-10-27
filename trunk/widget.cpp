#include "widget.h"

const int minX = 20,minY = 180,maxX = 420,maxY=180;
Widget::Widget(QDeclarativeView *parent)
    : QDeclarativeView(parent)
{
    MM = QApplication::desktop()->width();
    QDir dir("./song");
    if (!dir.exists())
    {
        QDir dirsong;
        dirsong.mkdir("./song");
    }
    settitle("豆瓣电台");
    setalbum("");
    setartist("Spring");
    setpic(":image/doubanmusic.png");
    setplaysource(":image/pause.png");
    setlikesource(":image/dislike.png");
    setttime("00:00/00:00");
    setpb(0);
    uiInit();
    loadIni();
    createTrayIcon();
    showMessage("欢迎使用");
    phononInit();
    totlenum=0;dbfmNum=0;e_channel=0;listNum=0;
    type='e';
    connect(this->shortcutwidget->m_next,SIGNAL(activated()),this,SLOT(nextFile()));
    connect(this->shortcutwidget->m_like,SIGNAL(activated()),this,SLOT(likeItit()));
    connect(this->shortcutwidget->m_dislike,SIGNAL(activated()),this,SLOT(trashIt()));
    connect(this->shortcutwidget->m_min,SIGNAL(activated()),this,SLOT(minit()));
    connect(this->shortcutwidget->m_play,SIGNAL(activated()),this,SLOT(playPause()));
    connect(this->shortcutwidget->m_down,SIGNAL(activated()),this,SLOT(downloadSong()));
    //connect(this->shortcutwidget->m_lrc,SIGNAL(activated()),this,SLOT(MLRC()));
    //connect(this->shortcutwidget->m_desktop,SIGNAL(activated()),this,SLOT(Mdesktop()));
    //connect(this->shortcutwidget->m_list,SIGNAL(activated()),this,SLOT(Mlist()));
    connect(this->shortcutwidget->m_close,SIGNAL(activated()),qApp,SLOT(quit()));
    netInit();
    channelInit();
}

void Widget::createTrayIcon()
{
    trayIcon = new QSystemTrayIcon(this);

    quitAction = new QAction(("退出"), this);
    connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));

    myabout = new QAction(("关于"),this);
    connect(myabout,SIGNAL(triggered()),this,SLOT(messageAbout()));

    mylogin = new QAction(("登录"),this);
    connect(mylogin,SIGNAL(triggered()),this,SLOT(logindb()));

    myproxy = new QAction(("代理"),this);
    connect(myproxy,SIGNAL(triggered()),proxywidget,SLOT(show()));

    myshortcut = new QAction(("快捷键"),this);
    connect(myshortcut,SIGNAL(triggered()),shortcutwidget,SLOT(mshow()));

    mylikeit = new QAction(("我喜欢"),this);
    mylikeit->setIcon(QIcon(":image/like.png"));
    connect(mylikeit,SIGNAL(triggered()),this,SLOT(likeItit()));

    mytrashit = new QAction(("不再播放"),this);
    mytrashit->setIcon(QIcon(":image/trash.png"));
    connect(mytrashit,SIGNAL(triggered()),this,SLOT(trashIt()));

    mynextfile = new QAction(("下一首"),this);
    mynextfile->setIcon(QIcon(":image/next.png"));
    connect(mynextfile,SIGNAL(triggered()),this,SLOT(nextFile()));
    trayIcon->setIcon(QIcon(":douban.ico"));
    trayIcon->show();
    trayIcon->setToolTip(("豆瓣电台"));
}

void Widget::trayIconmenu()
{
    QMenu* trayIconMenu = new QMenu(this);
    trayIconMenu->addAction(myabout);
    trayIconMenu->addSeparator();

    QAction* mylastsong[5];
    for (int i=listNum+1;i<5;i++)
    {
        if (nowPlayList[i].title=="") continue;
        mylastsong[i] = new QAction((nowPlayList[i].title + " "+ nowPlayList[i].artist),this);
        if (nowPlayList[i].like=="1") mylastsong[i]->setIcon(QIcon(":image/like.png"));
        trayIconMenu->addAction(mylastsong[i]);
    }
    for (int i=0;i<=listNum;i++)
    {
        if (nowPlayList[i].title=="") continue;
        mylastsong[i] = new QAction((nowPlayList[i].title + " "+ nowPlayList[i].artist),this);
        if (nowPlayList[i].like=="1") mylastsong[i]->setIcon(QIcon(":image/like.png"));
        trayIconMenu->addAction(mylastsong[i]);
    }


    if (nowPlayList[0].title!="") connect(mylastsong[0],SIGNAL(triggered()),this,SLOT(lastFile1()));
    if (nowPlayList[1].title!="") connect(mylastsong[1],SIGNAL(triggered()),this,SLOT(lastFile2()));
    if (nowPlayList[2].title!="") connect(mylastsong[2],SIGNAL(triggered()),this,SLOT(lastFile3()));
    if (nowPlayList[3].title!="") connect(mylastsong[3],SIGNAL(triggered()),this,SLOT(lastFile4()));
    if (nowPlayList[4].title!="") connect(mylastsong[4],SIGNAL(triggered()),this,SLOT(lastFile5()));

    trayIconMenu->addSeparator();
    trayIconMenu->addAction(myshortcut);
    trayIconMenu->addAction(myproxy);
    trayIconMenu->addAction(mylogin);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(mylikeit);
    trayIconMenu->addAction(mytrashit);
    trayIconMenu->addAction(mynextfile);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(quitAction);
    trayIcon->setContextMenu(trayIconMenu);
    connect(trayIcon,SIGNAL(activated(QSystemTrayIcon::ActivationReason)),this,SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));
}

void Widget::iconActivated(QSystemTrayIcon::ActivationReason reason)
{
    //触发后台图标执行相应事件
    switch (reason)
    {
    case QSystemTrayIcon::Trigger:
        //        if (this->isMinimized())
        //      {
        //        this->showNormal();
        //      break;
        //}
        if (this->isHidden())
            this->show();
        else
            this->hide();
        break;
    case QSystemTrayIcon::DoubleClick:
        //        showMessage("鼠标双击！");
        break;
    case QSystemTrayIcon::MiddleClick:
        //        showMessage("鼠标中键！");
        break;
    default:
        break;
    }
}

void Widget::loadIni()
{
    QSettings settings("conf.ini",QSettings::IniFormat);
    settings.beginGroup("Property");
    this->restoreGeometry(settings.value("geometry").toByteArray());
    settings.endGroup();
    settings.beginGroup("Mystate");
    int temp=settings.value("mystate").toInt();
    if (temp==2) temp=0;
    setmystate(temp);
    back=m_mystate;
    settings.endGroup();
    settings.beginGroup("Fmurl");
    this->fmurl.setUrl(QString(settings.value("fmurl").toString()));
    this->m_cType=settings.value("type").toString();
    settings.endGroup();
    if (m_cType=="" || m_cType=="db")
    {
        fmurl.setUrl("http://douban.fm/j/mine/playlist?type=n&h=&channel=0");
        m_cType="public";
    }
    settings.beginGroup("LRC");
    setfdesktop(settings.value("lrc").toBool());
    //qDebug()<<m_fdesktop;
    this->lrcshow->lrcdesktop->setVisible(m_fdesktop);
    settings.endGroup();
}

void Widget::phononInit()
{
    audioOutput = new Phonon::AudioOutput(Phonon::MusicCategory);
    mediaObject = new Phonon::MediaObject();
    connect(mediaObject, SIGNAL(aboutToFinish()), this, SLOT(aboutToFinish()));
    connect(mediaObject, SIGNAL(finished()), this, SLOT(finished()));
    connect(mediaObject, SIGNAL(totalTimeChanged(qint64)),this, SLOT(ttick(qint64)));
    connect(mediaObject, SIGNAL(tick(qint64)), this, SLOT(tick(qint64)));
    connect(mediaObject, SIGNAL(currentSourceChanged(const Phonon::MediaSource &)),this, SLOT(sourceChanged(const Phonon::MediaSource &)));
    //    connect(metaInformationResolver, SIGNAL(stateChanged(Phonon::State,Phonon::State)), this, SLOT(metaStateChanged(Phonon::State, Phonon::State)));
    mediaObject->setTickInterval(1000);
    Phonon::createPath(mediaObject, audioOutput);
}

void Widget::netInit()
{
    //    qDebug()<<"netinit";
    QNetworkAccessManager* listManager = new QNetworkAccessManager(this);  //新建QNetworkAccessManager对象
    connect(listManager,SIGNAL(finished(QNetworkReply*)),this,SLOT(downloadList(QNetworkReply*)));
    listManager->cookieJar()->setCookiesFromUrl(this->loginwidget->m_cookies,QUrl(fmurl));
    //    qDebug()<<this->loginwidget->m_cookies;
    //qDebug()<<fmurl;
    listManager->get(QNetworkRequest(QUrl(fmurl))); //发送请求
}

void Widget::songInit(QString json)
{
    //qDebug()<<json;
    QString head="403 Forbidden";
    int h = json.indexOf(head);
    //qDebug()<<h;
    if (h!=-1) {showMessage("网络问题"); return;}
    QScriptValue sc;
    QScriptEngine engine;
    sc = engine.evaluate("value = " + json);//注意这里必须这么用。不知道为什么。没有去研究。
    int i=0;

    if (sc.property("song").isArray())
    {
        QScriptValueIterator it(sc.property("song"));
        while (it.hasNext())
        {
            it.next();
            dbfm[i].init(it.value(),i);
            i++;
        }
    }
    dbfmNum = i-1;
}

void Widget::uiInit()
{
    loginwidget = new Login();
    proxywidget = new MyProxy();
    shortcutwidget = new Shortcut();
    lrcshow = new LRCshow();
    connect(this->loginwidget,SIGNAL(succ(const QString&)),this,SLOT(showMessage(const QString&)));
}

void Widget::downloadList(QNetworkReply *reply)  //当回复结束后
{
   // qDebug()<<"downloadList";
    QTextCodec *codec = QTextCodec::codecForName("utf8");
    QString json= codec->toUnicode(reply->readAll());
    songInit(json);
    addFiles();
    reply->deleteLater();   //最后要释放reply对象
}


void Widget::addFiles()
{
    //qDebug()<<"addFiles"<<dbfmNum;
    if (dbfmNum==0) return;
    int i;
    int index = sources.size();
    for (i=0;i<dbfmNum;i++)
    {
        Phonon::MediaSource source(QUrl(dbfm[i].url));
        sources.append(source);
    }
    if (!sources.isEmpty())
        mediaObject->setCurrentSource(sources.at(index));
    mediaObject->play();
}

Widget::~Widget()
{

}

void Widget::movePos(int mx,int my)
{
    QPoint mp(mx,my);
    QPoint cp=QCursor::pos();
    dragPosition=cp-frameGeometry().topLeft();
}

void Widget::moveThis()
{
    QPoint cp=QCursor::pos();
    move(cp-dragPosition);
}

void Widget::enter()
{
    if (m_mystate==0)
        setmystate(1);
    else if (m_mystate==1)
        setmystate(0);
}

/*void Widget::enterw()
{
//    qDebug()<<"enterw";
    if (frameGeometry().left() == MM-minX)
        move(MM-maxX,frameGeometry().topLeft().y());
    setmystate(1);
}
void Widget::leavew()
{
    if (frameGeometry().left() <= 0 )
    {
        setmystate(2);
        move(0,frameGeometry().topLeft().y());
    }
    if (frameGeometry().left() >= MM - maxX)
    {
        setmystate(2);
        move(MM-minX,frameGeometry().topLeft().y());
    }
}
    */

void Widget::sourceChanged(const Phonon::MediaSource &source)
{
    //onSongStatus();
    nowPlayList[listNum]=nowPlaySong;

    trayIconmenu();

    type='e';
    int curnum = sources.indexOf(mediaObject->currentSource());
    //qDebug()<<curnum<<totlenum;
    nowPlaySong = dbfm[curnum-totlenum];
    listNum++; if (listNum==5) listNum=0;
    settitle(nowPlaySong.title);
    setalbum(nowPlaySong.albumtitle + " " + nowPlaySong.public_time);
    lrcshow->init(nowPlaySong.title,nowPlaySong.artist);
    setartist(nowPlaySong.artist);
    setpic(nowPlaySong.picture);
    if (nowPlaySong.like == "1")
    {
        setlikesource(":image/like.png");
        m_like=true;
    }
    else {
        setlikesource(":image/dislike.png");
        m_like=false;
    }
    trayIcon->setToolTip(nowPlaySong.title + " " + nowPlaySong.artist);
    QString dburl("http://www.douban.com");
    if (nowPlaySong.album.indexOf("douban")>0)
        m_albumsource=nowPlaySong.album;
    else
        m_albumsource=dburl+nowPlaySong.album;
}

void Widget::onSongStatus()
{
    //qDebug()<<"onSongStatus";
    QString sid = nowPlaySong.sid;
    if (sid=="") return;
    QString subtype = nowPlaySong.subtype;
    if (subtype != "T")// && type != 'u' && type != 'r')
    {
        int index = m_historyIds.indexOf(sid);
        if( index != -1 )
        {
            m_historyIds.removeAt(index);
            m_historyTypes.removeAt(index);
        }
        m_historyIds.append(sid);
        m_historyTypes.append(type);

        if(m_historyIds.length() > 20)
        {
            m_historyIds.removeFirst();
            m_historyTypes.removeFirst();
        }
    }
    // type == 'e' 成功播放完毕
    // type == 'r' 喜欢标记
    // type == 'u' 取消喜欢标记
    // type == 's' 跳过标记
    // type == 'b' 删除标记
    // qDebug()<<type;
    if( type == 'e')
        reportPlayed();
    else
        requireList(type);
}

void Widget::reportPlayed()
{
    uint time = QDateTime::currentDateTime().toTime_t();
    qsrand(time);
    double r = qrand()*1.0/RAND_MAX;
    QString baseString = "http://douban.fm/j/mine/playlist?type=%1&";
    QNetworkRequest request;
    if(m_like)
        baseString = baseString.arg('r');
    else
        baseString = baseString.arg('e');
    baseString.append(QString("sid=%1").arg(nowPlaySong.sid));
    if(m_historyIds.length())
    {
        baseString.append("&h=|");
        QString h;
        for(int i=0; i< m_historyIds.length(); ++i)
        {
            h.append(m_historyIds.at(i));
            h.append(':');
            h.append(m_historyTypes.at(i));
            h.append('|');
        }
        h.remove(h.length()-1,1);
        baseString.append(h);
    }
    if (m_cType=="public"  || m_cType=="db") baseString.append(QString("&channel=%1").arg((int)e_channel));
    if (m_cType=="dj") baseString.append(QString("&channel=dj&pid=%1").arg((int)e_channel));
    baseString.append(QString("&r=%1").arg(r));
    request.setUrl(baseString);

    QNetworkAccessManager* m_manager = new QNetworkAccessManager;
    m_manager->cookieJar()->setCookiesFromUrl(this->loginwidget->m_cookies,QUrl(baseString));
    //   qDebug()<<this->loginwidget->m_cookies;
    m_manager->get(request);

    //    qDebug()<<request.url().toString();
}

void Widget::requireList(char type)
{
    //qDebug()<<"requireList";
    uint time = QDateTime::currentDateTime().toTime_t();
    qsrand(time);
    double r = qrand()*1.0/RAND_MAX;

    QString url = "http://douban.fm/j/mine/playlist?";
    url.append(QString("type=%1").arg(type));
    //    url.append(QString("&uid=%1").arg(i_uid));
    url.append(QString("&sid=%1").arg(nowPlaySong.sid));
    //    url.append(QString("&aid=%1").arg(nowplaysong.aid));
    //    if(e_lastChannel != -1)
    //        url.append(QString("&last_channel=%1").arg((int)e_lastChannel));

    //qDebug()<<m_cType;
    if (m_cType=="public"  || m_cType=="db") url.append(QString("&channel=%1").arg((int)e_channel));
    if (m_cType=="dj")
    {
        if(m_historyIds.length())
        {
            url.append("&h=|");
            QString h;
            for(int i=0; i< m_historyIds.length(); ++i)
            {
                h.append(m_historyIds.at(i));
                h.append(':');
                h.append(m_historyTypes.at(i));
                h.append('|');
            }
            h.remove(h.length()-1,1);
            url.append(h);
        }
        url.append(QString("&channel=dj&pid=%1").arg((int)e_channel));
    }
    url.append(QString("&r=%1").arg(r));
      //  qDebug()<<url;
    /*    url.append("&rest=");
    QString rest;
    if(m_playList.length())
    {
        for(int i=0; i< m_playList.length(); ++i)
        {
            rest.append(m_playList.at(i)->sid());
            rest.append('|');
        }
        rest.remove(rest.length()-1,1);
        url.append(rest);
    }*/
    QNetworkRequest request;
    request.setUrl(url);

    // 不分析喜欢/不喜欢/删除返回的列表
    /*    if(type != 'u' && type != 'r' && type != 'b')
    {
        if(m_getListReply)
            m_getListReply->abort();
        m_getListReply = m_manager->get(request);
        connect(m_getListReply,SIGNAL(finished()),this,SLOT(downloadList()));
    }else*/
    QNetworkAccessManager *m_manager = new QNetworkAccessManager;
    m_manager->cookieJar()->setCookiesFromUrl(this->loginwidget->m_cookies,QUrl(url));
    //   qDebug()<<this->loginwidget->m_cookies;
    m_manager->get(request);
    if (m_cType=="public"  || m_cType=="db")
    {
        if(type == 's' || type == 'b' || type == 'n')
        {
            totlenum=totlenum+dbfmNum;
            connect(m_manager,SIGNAL(finished(QNetworkReply*)),this,SLOT(downloadList(QNetworkReply*)));
        }
    }
    if (m_cType=="dj")
    {
        if(type == 's')
        {
            int index = sources.indexOf(mediaObject->currentSource()) + 1;
            if (sources.size() > index) {
                mediaObject->stop();
                mediaObject->setCurrentSource(sources.at(index));
                mediaObject->play();
            }
        }
        if (type=='n')
        {
            totlenum=totlenum+dbfmNum;
            connect(m_manager,SIGNAL(finished(QNetworkReply*)),this,SLOT(downloadList(QNetworkReply*)));
        }
    }
}

void Widget::aboutToFinish()
{
    //    qDebug()<<"aboutToFinish";
    onSongStatus();
    int index = sources.indexOf(mediaObject->currentSource()) + 1;
    if (sources.size() > index) {
        mediaObject->enqueue(sources.at(index));
    }
}

void Widget::finished()
{
    //   qDebug()<<"finished";
    totlenum=totlenum+dbfmNum;
    // this->netinit();
}

void Widget::tick(qint64 time)
{
    QTime displayTime(0, (time / 60000) % 60, (time / 1000) % 60);
    setttime(displayTime.toString("mm:ss")+"/"+m_ttick);
    if (tttime!=0)
        setpb((int)time*1000/tttime);
    else
        tttime=mediaObject->totalTime();
    // qDebug()<<(int)time*100/tttime;
    //ui->mygroupBox->ui->lcdNumber->display(displayTime.toString("mm:ss"));
    int t=(int)time;
    t /= 1000;
    t *= 1000;
    this->lrcshow->showWord(t);
}

void Widget::ttick(qint64 time)
{
    QTime displayTime(0, (time / 60000) % 60, (time / 1000) % 60);
    tttime=time;
    m_ttick=displayTime.toString("mm:ss");
}

void Widget::nextFile()
{
    //qDebug()<<"nextFile";
    setplaysource(":image/pause.png");
    int index = sources.indexOf(mediaObject->currentSource()) + 1;
    if (sources.size() > index) {
        type='s';
        onSongStatus();
    }
    else
    {
        type='n';
        onSongStatus();
    }
}

void Widget::trashIt()
{
    //    qDebug()<<"next";
    int index = sources.indexOf(mediaObject->currentSource()) + 1;
    if (sources.size() > index) {
        type='b';
        onSongStatus();
    }
    else
    {
        type='n';
        onSongStatus();
    }
}

void Widget::likeIt()
{
    //qDebug()<<"likeit";
    if (m_like)
    {
        setlikesource(":image/dislike.png");
        nowPlaySong.like=="0";
        type='u';
    }
    else{
        setlikesource(":image/like.png");
        nowPlaySong.like=="1";
        type='r';
    }
    m_like=!m_like;
    onSongStatus();
}

void Widget::likeItit()
{
    //qDebug()<<"likeit";
    setlikesource(":image/like.png");
    nowPlaySong.like=="1";
    type='r';
    m_like=!m_like;
    onSongStatus();
}

void Widget::playPause()
{
    switch (mediaObject->state())
    {
    case Phonon::ErrorState:
        if (mediaObject->errorType() == Phonon::FatalError)
        {
            QMessageBox::warning(this, ("Fatal Error"),
                                 mediaObject->errorString());
        }
        else
        {
            QMessageBox::warning(this, ("Error"),
                                 mediaObject->errorString());
        }
        break;
    case Phonon::PlayingState:
    {
        mediaObject->pause();
        setplaysource(":image/play.png");
        break;
    }
    case Phonon::PausedState:
    {
        mediaObject->play();
        setplaysource(":image/pause.png");
        break;
    }
    case Phonon::StoppedState:
        mediaObject->play();
        break;
    case Phonon::LoadingState:
        break;
    case Phonon::BufferingState:
        break;
    default:
        ;
    }
}

void Widget::showMessage(const QString &s)
{
    trayIcon->showMessage(("豆瓣电台"),s);
}

void Widget::messageAbout()
{
    QMessageBox::about(this,("豆瓣电台"),("<h2>By Spring</h2>"
                                      "<p>2011年10月26日"
                                      "<p>Spring的豆瓣电台3.23 beta"
                                      "<p>125392171@163.com"));
}

void Widget::minit()
{
    if (this->isHidden())
        this->show();
    else
        this->hide();
}

void Widget::openIt()
{
    QDesktopServices::openUrl(QUrl(m_albumsource));
}

void Widget::logindb()
{
    this->loginwidget->init();
    this->loginwidget->show();
}

void Widget::quitIt()
{
    QSettings settings("conf.ini",QSettings::IniFormat);
    settings.beginGroup("Property");
    settings.setValue("geometry",this->saveGeometry());
    settings.endGroup();
    settings.beginGroup("Mystate");
    settings.setValue("mystate",this->m_mystate);
    settings.endGroup();
    settings.beginGroup("Fmurl");
    settings.setValue("Fmurl",this->fmurl);
    settings.setValue("Type",this->m_cType);
    settings.endGroup();
    settings.beginGroup("LRCProperty");
    settings.setValue("geometry",this->lrcshow->lrcdesktop->saveGeometry());
    settings.endGroup();
    settings.beginGroup("LRC");
    settings.setValue("lrc",this->m_fdesktop);
    settings.endGroup();
    qApp->quit();
}

void Widget::channelInit()
{
   // qDebug()<<"channelInit"<<dbfmNum;
   // if (dbfmNum==0) return;
    QNetworkAccessManager* channeltManager = new QNetworkAccessManager(this);  //新建QNetworkAccessManager对象
    connect(channeltManager,SIGNAL(finished(QNetworkReply*)),this,SLOT(downloadChannel(QNetworkReply*)));
    channeltManager->cookieJar()->setCookiesFromUrl(this->loginwidget->m_cookies,QUrl(fmurl));
    //    qDebug()<<this->loginwidget->m_cookies;
    channeltManager->get(QNetworkRequest(QUrl("http://douban.fm"))); //发送请求
}

void Widget::downloadChannel(QNetworkReply *reply)  //当回复结束后
{
    //qDebug()<<"downloadList";
    QTextCodec *codec = QTextCodec::codecForName("utf8");
    QString all= codec->toUnicode(reply->readAll());

    QString head = "channelInfo = ";
    QString tail = "cateInfo";
    int h = all.indexOf(head);
    int t = all.indexOf(tail);
    if (h!=-1)
    {
    }
    QString json = all.mid(h+14,t-h-16);
    //qDebug()<<json;
    QScriptValue sc;
    QScriptEngine engine;
    sc = engine.evaluate("value = " + json);//注意这里必须这么用。不知道为什么。没有去研究。
    int i=0;

    QScriptValueIterator it(sc.property("public"));
    int k=0;

    while (it.hasNext())
    {
        it.next();
        i=0;
        channelpublic[k].name=it.value().property("cate").toString();
        channelpublic[k].id=k;
        //qDebug()<<it.value().property("cate").toString();
        QScriptValueIterator cit(it.value().property("channels"));
        while (cit.hasNext())
        {
            cit.next();
            channelpublic[k].channel[i].name=cit.value().property("name").toString();
            channelpublic[k].channel[i].id=cit.value().property("channel_id").toInteger();
            //qDebug()<<channel[i].name<<i;
            if (channelpublic[k].channel[i].name!="") i++;
        }
        channelpublic[k].num=i;
        k++;
        //qDebug()<<cit.value().property("name").toString();
        //qDebug()<<it.value().toString();
    }
    channelCate=k-1;
    channelNum = i-1;

    head = "channelInfo.dj = ";
    tail = "subChannelInfo";
    h = all.indexOf(head);
    t = all.indexOf(tail);
    if (h!=-1)
    {
    }
    //json = "[" + all.mid(h+18,t-h-22) + "]";
    json=all.mid(h+17,t-h-20);
    //qDebug()<<json;
    sc = engine.evaluate("value = " + json);//注意这里必须这么用。不知道为什么。没有去研究。
    i=0;
    QScriptValueIterator cit(sc);
    while (cit.hasNext())
    {
        cit.next();
        channeldj[i].name=cit.value().property("name").toString();
        channeldj[i].id=cit.value().property("channel_id").toInteger();
        channeldj[i].update=cit.value().property("update").toInteger();
        //qDebug()<<channeldj[i].name<<channeldj[i].id<<i;
        if (channeldj[i].name!="") i++;
    }

    channeldjNum=i;
    head = "subChannelInfo = ";
    tail = "!function";
    h = all.indexOf(head);
    t = all.indexOf(tail);
    if (h!=-1)
    {
    }
    //json = "[" + all.mid(h+18,t-h-22) + "]";
    json=all.mid(h+17,t-h-20);
    //qDebug()<<json;
    sc = engine.evaluate("value = " + json);//注意这里必须这么用。不知道为什么。没有去研究。
    for (int j=0;j<i;j++)
    {
        QScriptValueIterator ccit(sc.property(channeldj[j].id));
        //qDebug()<<channeldj[j].id<<j;
        k=0;
        while (ccit.hasNext())
        {
            ccit.next();
            channeldj[j].channel[k].name=ccit.value().property("name").toString();
            channeldj[j].channel[k].id=ccit.value().property("channel_id").toInteger();
            //qDebug()<<channeldj[j].channel[k].name<<j;
            if (channeldj[j].channel[k].name!="") k++;
            //qDebug()<<cit.value().property("name").toString();
            //qDebug()<<it.value().toString();
        }
        channeldj[j].num=k;
    }
    reply->deleteLater();   //最后要释放reply对象
}

void Widget::updateData(QString type,int n)
{
    //qDebug()<<"updateData"<<n<<channelCate;
    if (type=="public"){
        if (n==channelCate) return;
        setcType("public");
        setcName(channelpublic[n].name);
        setcNum(n);
        emit data(QVariant(type),QVariant(n));
        return;
    }
    if (type=="dj"){
        if (n==channeldjNum) return;
        setcType("dj");
        setcName(channeldj[n].name);
        setcNum(n);
        emit data(QVariant(type),QVariant(n));
        return;
    }
    if (type=="db"){
        if (n==channeldbNum) return;
        setcType("db");
        setcName(channeldb[n].name);
        setcNum(n);
        emit data(QVariant(type),QVariant(n));
        return;
    }
}

void Widget::updateData2(QString type,int a,int n)
{
    //qDebug()<<"updateData2"<<a<<n;
    if (type=="public")
    {
        if (n==channelpublic[a].num) return;
        setcName(channelpublic[a].channel[n].name);
        setcNum(channelpublic[a].channel[n].id);
        setcType("public");
        emit data2(QVariant("public"),QVariant(a),QVariant(n));
        return;
    }
    if (type=="dj")
    {
        if (n==channeldj[a].num) return;
        setcName(channeldj[a].channel[n].name);
        setcNum(channeldj[a].channel[n].id);
        setcType("dj");
        emit data2(QVariant("dj"),QVariant(a),QVariant(n));
        return;
    }
    if (type=="db")
    {
        totlenum=totlenum+dbfmNum;
        QNetworkAccessManager* Listmanager = new QNetworkAccessManager(this);  //新建QNetworkAccessManager对象
        connect(Listmanager,SIGNAL(finished(QNetworkReply*)),this,SLOT(downloadList(QNetworkReply*)));
        Listmanager->cookieJar()->setCookiesFromUrl(this->loginwidget->m_cookies,QUrl(channeldb[a].id));
        //qDebug()<<this->loginwidget->m_cookies;
        Listmanager->get(QNetworkRequest(QUrl(channeldb[a].id))); //发送请求
        setmystate2(2);
        return;
    }
}

void Widget::changeChannel(QString t, int a)
{
    e_channel=a;
    setplaysource(":image/pause.png");
    if (t=="public")
    {
        setcType("public");
        fmurl.setUrl(QString("http://douban.fm/j/mine/playlist?type=n&h=&channel=%1").arg(e_channel));
    }
    if (t=="dj")
    {
        setcType("dj");
        fmurl.setUrl(QString("http://douban.fm/j/mine/playlist?type=n&h=&channel=dj&pid=%1").arg(e_channel));
    }
    type='n';
    onSongStatus();
    setmystate2(2);
}

void Widget::downloadSong()
{
    //    qDebug()<<"downloadSong";
    showMessage(nowPlaySong.title + " " + nowPlaySong.artist + "\n正在下载...");
    QNetworkAccessManager* Songmanager = new QNetworkAccessManager(this);  //新建QNetworkAccessManager对象
    connect(Songmanager,SIGNAL(finished(QNetworkReply*)),this,SLOT(downloadSongfinish(QNetworkReply*)));
    Songmanager->get(QNetworkRequest(QUrl(nowPlaySong.url))); //发送请求
}

void Widget::downloadSongfinish(QNetworkReply *reply)
{
    //    qDebug()<<"downloadSongfinish";
    QString filepath;
    filepath = "./song/" + nowPlaySong.title + "-" + nowPlaySong.artist + ".mp3";
    QFile file(filepath);
    if (!file.open(QIODevice::WriteOnly)) { showMessage("下载失败"); return;}
    //    qDebug()<<filepath;
    file.write(reply->readAll());
    showMessage(nowPlaySong.title + " " + nowPlaySong.artist + "\n下载完成");
    file.close();
    reply->deleteLater();
}

void Widget::Mdesktop(bool flag)
{
    this->lrcshow->lrcdesktop->setVisible(!flag);
    setfdesktop(!flag);
    //qDebug()<<m_fdesktop;
}

void Widget::search(QString str)
{
    //qDebug()<<"search"<<str;
    if (str=="") return;
    if (str=="点播") return;
    //setmystate2(2);
    //QString url = QString("http://music.douban.com/subject_search?search_text=%1&cat=1003").arg(str);

    QString url = QString("http://music.douban.com/subject_search?search_text=%1&cat=1003").arg(str);
    //   QUrl urlEn = QUrl::fromEncoded(url.toLocal8Bit());
    QUrl urlEn = QUrl(QString(url));
    //    qDebug()<<url<<'\n';
    //    qDebug()<<urlEn.toString();

    QNetworkAccessManager *Smanager = new QNetworkAccessManager(this);
    //connect(Smanager,SIGNAL(finished(QNetworkReply*)),this,SLOT(searchfinish(QNetworkReply*)));

    connect(Smanager,SIGNAL(finished(QNetworkReply*)),this,SLOT(searchfinish2(QNetworkReply*)));
    //Smanager->cookieJar()->setCookiesFromUrl(this->loginwidget->m_cookies,QUrl(urlEn));
    Smanager->get(QNetworkRequest(urlEn));
}

void Widget::searchfinish2(QNetworkReply *reply)
{
    QTextCodec *codec = QTextCodec::codecForName("utf-8");
    QString all = codec->toUnicode(reply->readAll());
    //QString all=reply->readAll();
    qDebug()<<all;
    QString head="http://music.douban.com/musician/";
    QString head2="去FM收听";
    QString head3="onclick";
    QString head4="title";
    QString teil2="onclick";
    QString teil4=">";
    QString lrc,showList;
    int h,h2,h3,h4,t,t4;
    h = all.indexOf(head);
    h2 = all.indexOf(head2);
    //qDebug()<<h2;
    if (h2<0)
    {
        showMessage("没找着...");
        return;
    }
    channeldbNum = 0;
    //qDebug()<<h2-h;
     if (h2-h<900)
    {
        lrc = all.mid(h+33,6);
        showList=all.mid(h+49);
        t = showList.indexOf(teil2);
        showList = showList.mid(0,t-2);
        //qDebug()<<showList<<lrc;
        QString dburl = QString("http://douban.fm/j/mine/playlist?context=channel:0|musician_id:%1&sid=&channel=0&type=n&h=").arg(lrc);
        all = all.mid(h2+1);
        channeldb[channeldbNum].name = showList;
        channeldb[channeldbNum].id = dburl;
        channeldbNum++;
    }
    h2 = all.indexOf(head2);
    while (h2!=-1)
    {
        all = all.mid(h2-500);
//        qDebug()<<all;
        h4 = all.indexOf(head4);
        showList = all.mid(h4+7);
        t4 = showList.indexOf(teil4);
        showList = showList.mid(0,t4-2);
        showList.replace("&amp;","&");
        h3 = all.indexOf(head3);
//        t3 = all.indexOf(teil3);
//        qDebug()<<h2<<h3<<t3;
//        showList = all.mid(h3+39,t3-h3-56);
//        showList.replace("&amp;","&");
        lrc = all.mid(h3-10,7);
       // qDebug()<<showList<<lrc;
        QString dburl = QString("http://douban.fm/j/mine/playlist?context=channel:0|subject_id:%1&sid=&channel=0&type=n&h=").arg(lrc);
        channeldb[channeldbNum].name = showList;
        channeldb[channeldbNum].id = dburl;
        all = all.mid(501);
        //qDebug()<<all;
        h2 = all.indexOf(head2);
        channeldbNum++;
        //qDebug()<<channeldbNum;
    }
    updateData("db",0);
}

void Widget::searchfinish(QNetworkReply *reply)
{
    //qDebug()<<"searchfinish";
    //    QTextCodec *codec = QTextCodec::codecForName("gb18030");
    //    QString all = codec->toUnicode(reply->readAll());
    QString all=reply->readAll();
    //  qDebug()<<all;
    QString head="http://music.douban.com/musician/";
    int h = all.indexOf(head);
    //    int t = all.indexOf(tail);
    QString lrc = all.mid(h+33,6);
    //    qDebug()<<all;

    QString dburl = QString("http://douban.fm/j/mine/playlist?context=channel:0|musician_id:%1&sid=&channel=0&type=n&h=").arg(lrc);

    if (h==-1)
    {
        head="http://music.douban.com/subject/";
        h = all.indexOf(head);
        //    int t = all.indexOf(tail);
        lrc = all.mid(h+32,7);
        dburl = QString("http://douban.fm/j/mine/playlist?context=channel:0|subject_id:%1&sid=&channel=0&type=n&h=").arg(lrc);
    }

    QUrl url(dburl);
    if (h==-1)
    {
        showMessage("没找着...");
        return;
    }

    totlenum=totlenum+dbfmNum;
    QNetworkAccessManager* Listmanager = new QNetworkAccessManager(this);  //新建QNetworkAccessManager对象
    connect(Listmanager,SIGNAL(finished(QNetworkReply*)),this,SLOT(downloadList(QNetworkReply*)));
    Listmanager->cookieJar()->setCookiesFromUrl(this->loginwidget->m_cookies,QUrl(url));
    //qDebug()<<this->loginwidget->m_cookies;
    Listmanager->get(QNetworkRequest(QUrl(url))); //发送请求

    //    qDebug()<<url;
}

void Widget::lastFile(int i)
{
    //qDebug()<<"lastFile";
    /*
    int index = sources.size();
    Phonon::MediaSource source(QUrl(nowPlayList[i].url));
    sources.append(source);
    totlenum++;
    mediaObject->stop();
    dbfm[index-totlenum]=nowPlayList[i];
    mediaObject->setCurrentSource(sources.at(index-1));
    mediaObject->play();
    qDebug()<<" "<<index<<totlenum;
    */
}


