#include "songsmetaparser.h"

SongsMetaParser::SongsMetaParser(QStringList paths) : QObject(nullptr), paths(paths)
{
    player = new QMediaPlayer(this);
    connect(player, &QMediaPlayer::mediaStatusChanged, this, &SongsMetaParser::metaAvailable);

    songs = {};

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

    QString name = player->metaData(QMediaMetaData::Title).toString();
    QString author = player->metaData(QMediaMetaData::Author).toString();
    QString album = player->metaData(QMediaMetaData::AlbumArtist).toString();
    uint duration = player->metaData(QMediaMetaData::Duration).toInt();

    song.setName(!name.isNull() ? name : "Unknown");
    song.setAuthor(!author.isNull() ? author : "Unknown");
    song.setAlbum(!album.isNull() ? album : "Unknown");
    song.setDuration(duration);

    songs << song;

    this->cur++;
    parseCurrentData();
}
