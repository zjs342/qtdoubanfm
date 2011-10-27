#include "dbfm.h"

Dbfm::Dbfm()
{
}

void Dbfm::init(QString json)
{
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
                 song[i].init(it.value(),i);
                 i++;
             }
    }
    num = i-1;
}



