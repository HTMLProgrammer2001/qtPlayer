#include "playercontrol.h"
#include "ui_playercontrol.h"

#include<QStyle>
#include<QCommonStyle>
#include<QIcon>

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
}

PlayerControl::~PlayerControl()
{
    delete ui;
}
