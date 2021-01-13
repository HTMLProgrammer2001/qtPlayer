#ifndef PLAYER_H
#define PLAYER_H

#include <QString>
#include <QList>
#include <QStringList>
#include <QObject>
#include <QDir>
#include <QDirIterator>
#include <QSet>
#include <QtMultimedia/QMediaPlayer>

#include "Interfaces/isong.h"
#include "database.h"
#include "songsmetaparser.h"

class Player: public QObject
{
    Q_OBJECT
private:
    QMediaPlayer *player;
    QList<ISong> songs;
    SongsMetaParser *parser;
    static Player *instance;

public:
    Player();
    ~Player();

    static Player *getInstance();
    QList<ISong> getSongs();
    QStringList parsePaths(QString);

signals:
    void currentSongChanged(ISong song);
    void timeChanged(int time);
    void songsListChanged(QList<ISong> songs);

public slots:
    void changeCurrentSong(ISong song);
    void setSongs(QList<ISong> songs);
};

#endif // PLAYER_H
