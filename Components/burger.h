#ifndef BURGER_H
#define BURGER_H


#include "../Interfaces/iclickable.h"

class Burger: public IClickable
{
Q_OBJECT
public:
    Burger(QWidget *parent = 0);
    void mousePressEvent(QMouseEvent *ev) override;
};

#endif // BURGER_H
