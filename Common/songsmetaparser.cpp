#include "songsmetaparser.h"

SongsMetaParser::SongsMetaParser() : QObject(nullptr)
{
    //add handler
    player = new QMediaPlayer(this);
    connect(player, &QMediaPlayer::mediaStatusChanged, this, &SongsMetaParser::metaAvailable);
}

void SongsMetaParser::setPaths(QStringList paths)
{
    this->paths = paths;

    songs = {};
    cur = 0;
    parseCurrentData();
}

void SongsMetaParser::parseCurrentData()
{
    if(this->cur >= this->paths.size() - 1){
        emit songsParsed(songs);
        return;
    }

    player->setMedia(QUrl::fromLocalFile(paths.at(this->cur)));
}

void SongsMetaParser::metaAvailable(bool available){
    if(!available || !player->isAudioAvailable())
        return;

    ISong song(paths.at(this->cur));

    //parse song data
    QString name = player->metaData(QMediaMetaData::Title).toString();
    QString author = player->metaData(QMediaMetaData::Author).toString();
    QString album = player->metaData(QMediaMetaData::AlbumArtist).toString();
    uint duration = player->metaData(QMediaMetaData::Duration).toInt();

    //create song
    song.setName(!name.isNull() ? name : "Unknown");
    song.setAuthor(!author.isNull() ? author : "Unknown");
    song.setAlbum(!album.isNull() ? album : "Unknown");
    song.setDuration(duration);
    song.setLiked(Database::getInstance()->existsFavorite(paths.at(this->cur)));

    songs << song;

    //continue parsing
    this->cur++;
    parseCurrentData();
}
