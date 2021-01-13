#ifndef DATABASE_H
#define DATABASE_H

#include <QtSql>
#include <QStringList>
#include <QDebug>

#include "globals.h"


class Database
{
private:
    QSqlQuery query;
    static Database *instance;

public:
    explicit Database();
    ~Database();
    static Database *getInstance();
    void createTables();

    QStringList getPaths();
    bool existsPath(QString path);
    bool addPath(QString path);
    bool remove(QString path);
};

#endif // DATABASE_H
