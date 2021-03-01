#include "playercontrol.h"
#include "ui_playercontrol.h"
#include "Interfaces/iclickable.h"

#include <QDebug>

PlayerControl::PlayerControl(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PlayerControl),
    song("")
{
    ui->setupUi(this);
    QCommonStyle style;

    //set pixmaps
    ui->next->setPixmap(style.standardPixmap(QStyle::SP_MediaSeekForward).scaledToWidth(20));
    ui->prev->setPixmap(style.standardPixmap(QStyle::SP_MediaSeekBackward).scaledToWidth(20));
    ui->stop->setPixmap(style.standardPixmap(QStyle::SP_MediaStop).scaledToWidth(20));

    this->addHandlers();
}

void PlayerControl::addHandlers()
{
    //get player instance
    Player *player = Player::getInstance();

    //add handlers
    connect(player, &Player::currentSongChanged, this, &PlayerControl::songChanged);
    connect(player, &Player::timeChanged, this, &PlayerControl::changeTime);
    connect(player, &Player::playChanged, this, &PlayerControl::playChange);

    connect(ui->prev, &IClickable::change, player, [=](bool){player->prevSong();});
    connect(ui->next, &IClickable::change, player, [=](bool){player->nextSong();});
    connect(ui->stop, &IClickable::change, player, [=](bool){player->togglePlay();});

    connect(ui->like, &IClickable::change, player, [=](bool){
        player->toggleLike(this->song.getPath());
    });

    connect(this->ui->slider, &QSlider::sliderReleased, player, [=](){
        player->changeTime(duration * this->ui->slider->value() / 100);
    });

    QShortcut *forward = new QShortcut(QKeySequence(QKeySequence::MoveToNextChar), this);
    connect(forward, &QShortcut::activated, this, [=](){player->forward();});

    QShortcut *back = new QShortcut(QKeySequence(QKeySequence::MoveToPreviousChar), this);
    connect(back, &QShortcut::activated, this, [=](){player->back();});
}

void PlayerControl::songChanged(ISong song)
{
    this->duration = song.getDuration();

    //update ui
    this->ui->totalTime->setText(QTime::fromMSecsSinceStartOfDay(song.getDuration()).toString("mm:ss"));
    this->ui->currentTime->setText("00:00");
    this->ui->author->setText(song.getAuthor());
    this->ui->name->setText(song.getName());

    QString path = QString(":/images/%1").arg(song.getLiked() ? "redHeart.png" : "blackHeart.png");
    ui->like->setPixmap(QPixmap(path).scaledToWidth(20));
    ui->like->adjustSize();

    this->song = song;

    //show player
    this->show();
}

void PlayerControl::changeTime(int time)
{
    if(duration == 0)
        return;

    //change player state
    this->ui->slider->setValue((float)time/duration * 100);
    this->ui->currentTime->setText(QTime::fromMSecsSinceStartOfDay(time).toString("mm:ss"));
}

void PlayerControl::playChange(bool isPlay)
{
    QCommonStyle style;
    ui->stop->setPixmap(style.standardPixmap(!isPlay ? QStyle::SP_MediaPlay : QStyle::SP_MediaStop).scaledToWidth(20));
}

PlayerControl::~PlayerControl()
{
    delete ui;
}
