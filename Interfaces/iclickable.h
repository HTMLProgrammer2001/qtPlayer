#ifndef CLICKABLE_H
#define CLICKABLE_H


#include <QLabel>
#include <QMouseEvent>

class IClickable: public QLabel
{
protected:
    bool isActive = false;

Q_OBJECT
public:
    IClickable(QWidget *parent = 0);
    virtual void mousePressEvent(QMouseEvent *ev);

signals:
    void change(bool);
};

#endif
