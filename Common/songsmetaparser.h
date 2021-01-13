#ifndef SONGSMETAPARSER_H
#define SONGSMETAPARSER_H

#include <QObject>
#include <QStringList>
#include <QList>
#include <QMediaPlayer>
#include <QMediaMetaData>
#include <QUrl>

#include "Interfaces/isong.h"

class SongsMetaParser: public QObject
{
    Q_OBJECT

private:
    int cur = 0;
    QStringList paths;
    QList<ISong> songs;
    QMediaPlayer *player;

public:
    explicit SongsMetaParser(QStringList paths);
    void parseCurrentData();

signals:
    void songsParsed(QList<ISong> songs);

private slots:
    void metaAvailable(bool);
};

#endif // SONGSMETAPARSER_H
