#include "player.h"
#include "algorithm"

Player *Player::instance = nullptr;

Player::Player(): QObject(nullptr)
{
    player = new QMediaPlayer(this);
    this->addHandlers();
    this->reload();
}

void Player::reload()
{
    //reset state
    songs = {};

    //get dirs
    Database *db = Database::getInstance();
    QStringList savedPaths = db->getPaths();

    QSet<QString> songPaths = {};

    //parse songs paths
    foreach(QString savedPath, savedPaths){
        QStringList songs = parsePaths(savedPath);

        foreach(QString path, songs){
            songPaths << path;
        }
    }

    //start loading
    isLoading = true;
    emit changeLoading(isLoading);
    this->parser.setPaths(songPaths.values());
}

bool Player::getLoading()
{
    return isLoading;
}

void Player::changeSort(bool isReversed)
{
    this->isReversed = isReversed;
    emit songsListChanged(this->getSongs());
}

void Player::addHandlers()
{
    connect(&this->parser, &SongsMetaParser::songsParsed, this, &Player::setSongs);
    connect(this->player, &QMediaPlayer::positionChanged, this, &Player::timeChanged);
    connect(this->player, &QMediaPlayer::stateChanged, this, &Player::changeState);
}

QList<ISong> Player::getSongs()
{
    QList<ISong> filteredList;

    //filter list
    foreach(ISong song, songs){
        if(song.getName().toLower().indexOf(this->filter.toLower()) != -1)
            filteredList << song;
    }

    //sort list
    std::sort(filteredList.begin(), filteredList.end());

    if(isReversed)
        std::reverse(filteredList.begin(), filteredList.end());

    return filteredList;
}

QStringList Player::parsePaths(QString path)
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
    //change songs
    this->songs = songs;
    emit songsListChanged(this->getSongs());

    //stop loading
    isLoading = false;
    emit changeLoading(isLoading);
}

void Player::changeTime(int position)
{
    qDebug() << "Change" << position;
    this->player->setPosition(position);
}

void Player::togglePlay()
{
    bool isPlay = this->player->state() == QMediaPlayer::PlayingState;
    isPlay ? this->player->pause() : this->player->play();
}

void Player::nextSong()
{
    //change index
    this->currentIndex++;

    //reset it if current index more than size
    if(this->currentIndex >= this->getSongs().size())
        this->currentIndex = 0;

    this->changePlayerSong();
}

void Player::prevSong()
{
    //change index
    this->currentIndex--;

    //reset it if current index more than size
    if(this->currentIndex < 0)
        this->currentIndex = this->getSongs().size() - 1;

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
