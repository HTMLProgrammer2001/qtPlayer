#include "player.h"

Player *Player::instance = nullptr;

Player::Player(): QObject(nullptr)
{
    songs = {};
    player = new QMediaPlayer(this);

    Database *db = Database::getInstance();
    QStringList savedPaths = db->getPaths();

    QSet<QString> songPaths = {};

    foreach(QString savedPath, savedPaths){
        QStringList songs = parsePaths(savedPath);

        foreach(QString path, songs){
            songPaths << path;
        }
    }

    parser = new SongsMetaParser(songPaths.toList());
    connect(parser, &SongsMetaParser::songsParsed, this, &Player::setSongs);
}

QList<ISong> Player::getSongs()
{
    return songs;
}

QStringList Player::parsePaths(QString path)
{
    QStringList songsPaths;
    QDir dir(path);

    if(!dir.exists())
        return songsPaths;

    QStringList musicFiles = dir.entryList(QStringList() << "*.mp3", QDir::Readable | QDir::Files);

    foreach(QString filename, musicFiles){
        songsPaths << QDir::cleanPath(path + QDir::separator() + filename);
    }

    return songsPaths;
}

Player *Player::getInstance()
{
    if(instance == nullptr)
        instance = new Player;

    return instance;
}

void Player::changeCurrentSong(ISong song)
{
    qDebug() << song.getPath();
}

void Player::setSongs(QList<ISong> songs)
{
    this->songs = songs;
    emit songsListChanged(songs);
}

Player::~Player()
{
    delete instance;
}
