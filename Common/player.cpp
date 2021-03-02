#include "player.h"
#include "algorithm"

Player *Player::instance = nullptr;

Player::Player(): QObject(nullptr), gen(0, 0)
{
    player = new QMediaPlayer(this);
    this->addHandlers();
}

void Player::reload()
{
    //reset state
    this->songs = {};

    auto songPaths = this->source->getPaths();

    //start loading
    this->isLoading = true;
    emit changeLoading(this->isLoading);
    this->parser.setPaths(songPaths);
}

void Player::setSource(ISource *source)
{
    this->source = source;
    this->reload();
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
    connect(this->player, &QMediaPlayer::stateChanged, this, &Player::changeState);

    connect(this->player, &QMediaPlayer::positionChanged, this, &Player::changePosition);

    connect(this->player, &QMediaPlayer::mediaStatusChanged, this, [&](QMediaPlayer::MediaStatus status){
        if(status == QMediaPlayer::EndOfMedia)
            this->nextSong();
    });
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

bool Player::toggleMode()
{
    this->isMix = !this->isMix;

    if(this->isMix)
        this->nextSong();

    return this->isMix;
}

void Player::changePosition(qint64 pos)
{
    this->position = pos;
    emit timeChanged(pos);
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

qint64 Player::getPosition(){
    return this->position;
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
    this->gen = RandomGen(0, songs.size());
    emit songsListChanged(this->getSongs());

    //stop loading
    isLoading = false;
    emit changeLoading(isLoading);
}

void Player::changeTime(int position)
{
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
    if(this->isMix)
        this->currentIndex = this->gen.next();
    else
        this->currentIndex++;

    //reset it if current index more than size
    if(this->currentIndex >= this->getSongs().size())
        this->currentIndex = 0;

    this->changePlayerSong();
}

void Player::prevSong()
{
    //change index
    if(this->isMix)
        this->currentIndex = this->gen.prev();
    else
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

void Player::toggleLike(QString path)
{
    auto db = Database::getInstance();
    int index = 0;

    //error occured
    if(!db->toggleFavorite(path))
        return;

    //change song
    foreach(ISong song, songs){
        if(song.getPath() != path)
            index++;
        else{
            songs[index].setLiked(!song.getLiked());
            emit currentSongChanged(this->getSongs()[this->currentIndex]);
        }
    }
}

void Player::forward()
{
    ISong curSong = this->getSongs().at(this->currentIndex);
    qint64 pos = this->getPosition();
    qint64 dur = curSong.getDuration();

    pos += 5000;
    pos = qMin(pos, dur - 1);
    this->changeTime(pos);
}

void Player::back()
{
    int pos = this->getPosition();

    pos -= 5000;
    pos = qMax(pos, 0);
    this->changeTime(pos);
}

Player::~Player()
{
    delete instance;
}
