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
    int currentIndex;

public:
    Player();
    ~Player();

    void addHandlers();

    static Player *getInstance();
    QList<ISong> getSongs();
    QStringList parsePaths(QString);
    void changePlayerSong();

signals:
    void currentSongChanged(ISong song);
    void timeChanged(int time);
    void songsListChanged(QList<ISong> songs);
    void playChanged(bool isPlay);

public slots:
    void changeCurrentSong(ISong song);
    void setSongs(QList<ISong> songs);
    void changeTime(int time);
    void togglePlay();
    void nextSong();
    void prevSong();
    void changeState(QMediaPlayer::State);
};

#endif // PLAYER_H
