#include "iclickable.h"
#include<QDebug>

IClickable::IClickable(QWidget* parent):QLabel(parent)
{
    QVariant defaultValue = property("default");

    if(defaultValue.isNull() || !defaultValue.toBool())
        isActive = false;
}

void IClickable::mousePressEvent(QMouseEvent *ev)
{
    this->isActive = !this->isActive;
    emit change(this->isActive);
}
