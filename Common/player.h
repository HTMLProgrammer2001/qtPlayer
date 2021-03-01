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
#include "Interfaces/isource.h"
#include "database.h"
#include "songsmetaparser.h"

class Player: public QObject
{
    Q_OBJECT
private:
    QMediaPlayer *player;
    QList<ISong> songs;
    SongsMetaParser parser;
    static Player *instance;
    int currentIndex;
    QString filter = "";
    bool isReversed = false;
    bool isLoading = false;
    ISource *source = nullptr;
    qint64 position = 0;

public:
    Player();
    ~Player();

    void addHandlers();

    static Player *getInstance();
    QList<ISong> getSongs();
    bool getLoading();
    bool getSort();
    void changePlayerSong();
    void setSource(ISource*);
    qint64 getPosition();

signals:
    void currentSongChanged(ISong song);
    void timeChanged(int time);
    void songsListChanged(QList<ISong> songs);
    void playChanged(bool isPlay);
    void changeLoading(bool isLoading);

public slots:
    void changeCurrentSong(ISong song);
    void setSongs(QList<ISong> songs);
    void changeTime(int time);
    void changePosition(qint64);
    void togglePlay();
    void nextSong();
    void prevSong();
    void changeState(QMediaPlayer::State);
    void changeFilter(QString filter);
    void reload();
    void changeSort(bool isReversed);
    void toggleLike(QString path);
    void forward();
    void back();
};

#endif // PLAYER_H
