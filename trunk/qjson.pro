#-------------------------------------------------
#
# Project created by QtCreator 2011-06-08T14:41:04
#
#-------------------------------------------------

QT       += core gui declarative network script phonon

TARGET = qjson
TEMPLATE = app

include(qxtglobalshortcut/qxtglobalshortcut.pri)
SOURCES += main.cpp\
        widget.cpp \
    song.cpp \
    ShortCutLineEdit.cpp \
    shortcut.cpp \
    myproxy.cpp \
    login.cpp \
    declarativeprogressbar.cpp \
    declarativewidget.cpp \
    lrcshow.cpp \
    lrcdesktop.cpp \
    lrcwidget.cpp


HEADERS  += widget.h \
    song.h \
    ShortCutLineEdit.h \
    shortcut.h \
    myproxy.h \
    login.h \
    declarativeprogressbar.h \
    nativequickwidgets.h \
    declarativewidget.h \
    lrcshow.h \
    lrcdesktop.h \
    lrcwidget.h


OTHER_FILES += \
    ui.qml \
    ProgressBar.qml \
    Channellist.qml

RESOURCES += \
    ico.qrc

FORMS += \
    shortcut.ui \
    myproxy.ui \
    login.ui

RC_FILE = myapp.rc
