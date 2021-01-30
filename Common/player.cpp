#include "player.h"
#include "algorithm"

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

    this->parser = new SongsMetaParser(songPaths.values());
    this->addHandlers();
}

void Player::addHandlers()
{
    connect(this->parser, &SongsMetaParser::songsParsed, this, &Player::setSongs);
    connect(this->player, &QMediaPlayer::positionChanged, this, &Player::timeChanged);
    connect(this->player, &QMediaPlayer::stateChanged, this, &Player::changeState);
}

QList<ISong> Player::getSongs()
{
    QList<ISong> filteredList;

    //filter list
    foreach(ISong song, songs){
        if(song.getName().toLower().indexOf(this->filter) != -1)
            filteredList << song;
    }

    //sort list
    std::sort(filteredList.begin(), filteredList.end());
    return filteredList;
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

void Player::changePlayerSong()
{
    auto song = this->getSongs().at(this->currentIndex);

    this->player->setMedia(QUrl::fromLocalFile(song.getPath()));
    this->player->play();

    emit currentSongChanged(song);
}

Player *Player::getInstance()
{
    if(instance == nullptr)
        instance = new Player;

    return instance;
}

void Player::changeCurrentSong(ISong song)
{
    int index = this->getSongs().indexOf(song);

    if(index == -1)
        return;

    this->currentIndex = index;
    this->changePlayerSong();
}

void Player::setSongs(QList<ISong> songs)
{
    this->songs = songs;
    emit songsListChanged(this->getSongs());
}

void Player::changeTime(int position)
{
    qDebug() << "Change" << position;
    this->player->setPosition(position);
}

void Player::togglePlay()
{
    bool isPlay = this->player->state() == QMediaPlayer::PlayingState;

    if(isPlay)
        this->player->pause();
    else
        this->player->play();
}

void Player::nextSong()
{
    //change index
    this->currentIndex++;

    //reset it if current index more than size
    if(this->currentIndex >= this->songs.size())
        this->currentIndex = 0;

    this->changePlayerSong();
}

void Player::prevSong()
{
    //change index
    this->currentIndex--;

    //reset it if current index more than size
    if(this->currentIndex < 0)
        this->currentIndex = this->songs.size() - 1;

    this->changePlayerSong();
}

void Player::changeState(QMediaPlayer::State state)
{
    emit playChanged(state == QMediaPlayer::PlayingState);
}

void Player::changeFilter(QString filter)
{
    this->filter = filter;
    emit songsListChanged(this->getSongs());
}

Player::~Player()
{
    delete instance;
}
