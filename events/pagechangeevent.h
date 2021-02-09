#ifndef PAGECHANGEEVENT_H
#define PAGECHANGEEVENT_H

#include "Common/globals.h"

#include <QEvent>


class PageChangeEvent: public QEvent
{
    QString page;

public:
    PageChangeEvent(QString);
    QString getPage();
};

#endif // PAGECHANGEEVENT_H
