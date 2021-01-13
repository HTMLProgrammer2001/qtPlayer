#include "isong.h"

ISong::ISong(QString path): path(path)
{}

QString ISong::getName()
{
    return name;
}

QString ISong::getPath()
{
    return path;
}

QString ISong::getAlbum()
{
    return album;
}

QString ISong::getAuthor()
{
    return author;
}

uint ISong::getDuration()
{
    return duration;
}

int ISong::getSize()
{
    return size;
}

void ISong::setName(QString name)
{
    this->name = name;
}

void ISong::setAlbum(QString album)
{
    this->album = album;
}

void ISong::setAuthor(QString author)
{
    this->author = author;
}

void ISong::setDuration(uint dur)
{
    this->duration = dur;
}
