#include "database.h"


Database* Database::instance = nullptr;

Database::Database(){
    //open connection
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");

    db.setDatabaseName(Globals::dbName);
    db.setUserName(Globals::user);
    db.setPassword(Globals::passwd);

    if(!db.open()){
        qDebug() << "Error in DB open";
        exit(1);
    }

    //create tables
    query = QSqlQuery();
    createTables();
}

Database* Database::getInstance(){
    //get singleton
    if(instance == nullptr)
        instance = new Database();

    return instance;
}

Database::~Database(){
    delete instance;
}

void Database::createTables(){
    //create tables
    bool res1 = query.exec("CREATE TABLE IF NOT EXISTS `paths`(`path` TEXT);");
    bool res2 = query.exec("CREATE TABLE IF NOT EXISTS `favorites`(`path` TEXT);");

    //check errors
    if(!res1 || !res2){
        qDebug() << "Error in create tables: " << query.lastError();
        exit(1);
    }
}

QStringList Database::getPaths(){
    QStringList paths;

    //make query
    query.exec("SELECT * FROM `paths`;");
    QSqlRecord rec = query.record();

    //parse data
    while(query.next())
        paths << query.value(rec.indexOf("path")).toString();

    return paths;
}

bool Database::addPath(QString path){
    if(this->existsPath(path)){
        qDebug() << "Exists";
        return false;
    }

    query.prepare("INSERT INTO `paths` (`path`) VALUES (?);");
    query.bindValue(0, path);

    return query.exec();
}

bool Database::removePath(QString path){
    if(!this->existsPath(path))
        return false;

    query.prepare("DELETE FROM `paths` WHERE `path` = ?;");
    query.bindValue(0, path);

    return query.exec();
}

bool Database::existsPath(QString path){
    query.prepare("SELECT * FROM `paths` WHERE `path` = ?;");
    query.bindValue(0, path);
    query.exec();

    return query.next();
}

bool Database::editPath(QString curPath, QString newPath)
{
    if(!this->existsPath(curPath))
        return false;

    query.prepare("UPDATE `paths` SET `path` = ? WHERE `path` = ?");
    query.bindValue(0, newPath);
    query.bindValue(1, curPath);

    return query.exec();
}

QStringList Database::getFavorites(){
    QStringList paths;

    //make query
    query.exec("SELECT * FROM `favorites`;");
    QSqlRecord rec = query.record();

    //parse data
    while(query.next())
        paths << query.value(rec.indexOf("path")).toString();

    return paths;
}

bool Database::addFavorite(QString path){
    if(this->existsFavorite(path)){
        qDebug() << "Exists";
        return false;
    }

    query.prepare("INSERT INTO `favorites` (`path`) VALUES (?);");
    query.bindValue(0, path);

    return query.exec();
}

bool Database::removeFavorite(QString path){
    if(!this->existsFavorite(path))
        return false;

    query.prepare("DELETE FROM `favorites` WHERE `path` = ?;");
    query.bindValue(0, path);

    return query.exec();
}

bool Database::existsFavorite(QString path){
    query.prepare("SELECT * FROM `favorites` WHERE `path` = ?;");
    query.bindValue(0, path);
    query.exec();

    return query.next();
}

bool Database::toggleFavorite(QString path){
    if(this->existsFavorite(path))
        return this->removeFavorite(path);
    else
        return this->addFavorite(path);
}
