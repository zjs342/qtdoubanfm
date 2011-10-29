#ifndef SONG_H
#define SONG_H

#include <QScriptEngine>
#include <QScriptValueIterator>
#include <QString>
#include <QDebug>

class Song
{
	public:
		Song();
		void init(QScriptValue,int);
		int num;
		QString picture;
		QString albumtitle;
		QString company;
		QString rating_avg;
		QString public_time;
		QString album;
		QString like;
		QString artist;
		QString url;
		QString title;
		QString subtype;
		QString length;
		QString sid;
		QString aid;
		Song& operator=(const Song&);
	private:

};

#endif // SONG_H
