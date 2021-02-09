#include <QPropertyAnimation>
#include <QDebug>
#include <QMouseEvent>

#include "sidebar.h"
#include "ui_sidebar.h"
#include "Events/pagechangeevent.h"

SideBar::SideBar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SideBar)
{
    ui->setupUi(this);
}

void SideBar::mousePressEvent(QMouseEvent *event)
{
    QObject* elem = this;

    //find root element
    while(elem->parent())
        elem = elem->parent();

    qDebug() << sender();

    return;

    QVariant pageProp = this->sender()->property("page");

    if(pageProp.isNull() || !pageProp.isValid())
        return;

    QCoreApplication::sendEvent(elem, new PageChangeEvent(pageProp.toString()));
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
