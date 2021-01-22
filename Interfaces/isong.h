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

public:
    ISong(QString path);
    bool operator==(const ISong);
    void parseData();

    QString getPath();
    QString getAuthor();
    QString getAlbum();
    QString getName();
    uint getDuration();

    void setAuthor(QString);
    void setAlbum(QString);
    void setName(QString);
    void setDuration(uint);

    int getSize();
};

#endif // ISONG_H
