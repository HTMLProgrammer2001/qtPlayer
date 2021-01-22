#include "songitem.h"
#include "ui_songitem.h"
#include <QDebug>

SongItem::SongItem(ISong song, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SongItem),
    song(song)
{
    ui->setupUi(this);
    initUI();
}

void SongItem::initUI()
{
    ui->duration->setText(QTime::fromMSecsSinceStartOfDay(song.getDuration()).toString("mm:ss"));
    ui->name->setText(song.getName());
    ui->album->setText(song.getAlbum());
    ui->author->setText(song.getAuthor());
}

void SongItem::mousePressEvent(QMouseEvent *event)
{
    emit songChoosed(this->song);
}

SongItem::~SongItem()
{
    delete ui;
}
