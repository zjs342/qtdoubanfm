#include "song.h"


Song::Song()
{
}

void Song::init(QScriptValue it,int n)
{
	this->num = n ;
	this->picture=it.property("picture").toString();
	this->picture.replace(QString("mpic"),QString("lpic"));
	this->albumtitle=it.property("albumtitle").toString();
	this->company=it.property("company").toString();
	this->rating_avg=it.property("rating_avg").toString();
	this->public_time=it.property("public_time").toString();
	this->album=it.property("album").toString();
	this->like=it.property("like").toString();
	this->artist=it.property("artist").toString();
	this->url=it.property("url").toString();
	this->title=it.property("title").toString();
	this->subtype=it.property("subtype").toString();
	this->length=it.property("length").toString();
	this->sid=it.property("sid").toString();
	this->aid=it.property("aid").toString();
}

Song& Song::operator=(const Song& a)
{
	this->picture=a.picture;
	this->aid=a.aid;
	this->album=a.album;
	this->albumtitle=a.albumtitle;
	this->artist=a.artist;
	this->company=a.company;
	this->rating_avg=a.rating_avg;
	this->public_time=a.public_time;
	this->length=a.length;
	this->like=a.like;
	this->url=a.url;
	this->title=a.title;
	this->sid=a.sid;
	this->subtype=a.subtype;
	return *this;
}
