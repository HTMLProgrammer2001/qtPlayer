#ifndef GLOBALS_H
#define GLOBALS_H

#include <QString>
#include <QEvent>


struct Globals{
    static QString dbName;
    static QString user;
    static QString passwd;

    static QEvent::Type eventType;
};

#endif // GLOBALS_H
