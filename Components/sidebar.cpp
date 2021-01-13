#include <QPropertyAnimation>

#include "sidebar.h"
#include "ui_sidebar.h"

SideBar::SideBar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SideBar)
{
    ui->setupUi(this);
}

SideBar::~SideBar()
{
    delete ui;
}

void SideBar::changeSize(bool isActive)
{

    //animate change
    QPropertyAnimation* anim = new QPropertyAnimation(this, "geometry");
    anim->setStartValue(QRect(0, 50, isActive ? 0 : 200, height()));
    anim->setEndValue(QRect(0, 50, isActive ? 200 : 0, height()));
    anim->setDuration(300);

    anim->start();
}
