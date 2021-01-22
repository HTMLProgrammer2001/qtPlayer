#include "playercontrol.h"
#include "ui_playercontrol.h"

#include <QDebug>

PlayerControl::PlayerControl(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PlayerControl)
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
    connect(this->ui->slider, &QSlider::sliderReleased, player, [=](){
        player->changeTime(duration * this->ui->slider->value() / 100);
    });
}

void PlayerControl::songChanged(ISong song)
{
    this->duration = song.getDuration();

    //update ui
    this->ui->totalTime->setText(QTime::fromMSecsSinceStartOfDay(song.getDuration()).toString("mm:ss"));
    this->ui->currentTime->setText("00:00");
    this->ui->author->setText(song.getAuthor());
    this->ui->name->setText(song.getName());

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

PlayerControl::~PlayerControl()
{
    delete ui;
}
