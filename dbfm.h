#ifndef DBFM_H
#define DBFM_H

#include "song.h"
#include <QStringList>
//#include <QStringList>
#include <QScriptEngine>
#include <QScriptValueIterator>
#include <QMap>

class Dbfm
{
	public:
		Dbfm();
		void init(QString);
		void channels(QString);
		Song song[225];
		int num;
		void add(song);
};

#endif // DBFM_H
