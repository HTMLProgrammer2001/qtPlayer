#ifndef ISONG_H
#define ISONG_H

#include <QString>


class ISong
{
private:
    QString path;
    QString author;
    QString album;
    QString name;
    uint duration;
    int size;
    bool isLiked = false;

public:
    ISong(QString path);
    bool operator==(const ISong);
    void parseData();

    QString getPath();
    QString getAuthor();
    QString getAlbum();
    QString getName();
    uint getDuration();
    bool getLiked();

    void setAuthor(QString);
    void setAlbum(QString);
    void setName(QString);
    void setDuration(uint);
    void setLiked(bool);

    int getSize();

    bool operator>(ISong &song);
    bool operator<(ISong &song);
};

#endif // ISONG_H
