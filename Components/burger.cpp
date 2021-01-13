#include <QVariantAnimation>

#include "burger.h"

Burger::Burger(QWidget* parent):IClickable(parent){}

void Burger::mousePressEvent(QMouseEvent *ev){
    IClickable::mousePressEvent(ev);

    auto pixmap = QPixmap(":/images/burger.png");

    auto anim = new QVariantAnimation;
    anim->setDuration(300);
    anim->setStartValue(isActive ? 0.0f : 90.0f);
    anim->setEndValue(isActive ? 90.0f : 0.0f);

    connect(anim, &QVariantAnimation::valueChanged, [=](const QVariant &value){
        QTransform t;
        t.rotate(value.toReal());
        this->setPixmap(pixmap.transformed(t));
    });

    anim->start();
}
