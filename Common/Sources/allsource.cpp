#include "allsongssource.h"

AllSource::AllSource()
{}

QStringList AllSource::getPaths(){
    //get dirs
    Database *db = Database::getInstance();
    QStringList savedPaths = db->getPaths();

    QSet<QString> songPaths = {};

    //parse songs paths
    foreach(QString savedPath, savedPaths){
        QStringList songs = this->parseDir(savedPath);

        foreach(QString path, songs){
            songPaths << path;
        }
    }

    return songPaths.values();
}

QStringList AllSource::parseDir(QString path)
{
    QStringList songsPaths;
    QDir dir(path);

    //check directory exists
    if(!dir.exists())
        return songsPaths;

    //set filters
    QStringList musicFiles = dir.entryList(QStringList() << "*.mp3", QDir::Readable | QDir::Files);

    //parse path
    foreach(QString filename, musicFiles){
        songsPaths << QDir::cleanPath(path + QDir::separator() + filename);
    }

    return songsPaths;
}
