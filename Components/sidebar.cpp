#include <QPropertyAnimation>
#include <QDebug>
#include <QMouseEvent>

#include "sidebar.h"
#include "ui_sidebar.h"
#include "Events/pagechangeevent.h"
#include "Interfaces/iclickable.h"

SideBar::SideBar(QWidget *parent) : QWidget(parent), ui(new Ui::SideBar)
{
    ui->setupUi(this);
    addHandlers();
}

void SideBar::addHandlers()
{
    QList<IClickable*> pageLabels = this->findChildren<IClickable*>(QRegExp("^*_page$"));

    foreach(IClickable* pageLbl, pageLabels)
        connect(pageLbl, &IClickable::change, this, &SideBar::changePage);
}

void SideBar::changePage(bool)
{
    QObject* elem = this;

    //find root element
    while(elem->parent())
        elem = elem->parent();

   QVariant page = this->sender()->property("page");

   if(page.isValid() && !page.isNull())
      QCoreApplication::sendEvent(elem, new PageChangeEvent(page.toString()));
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
