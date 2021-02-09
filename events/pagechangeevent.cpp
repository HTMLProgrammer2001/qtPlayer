#include "pagechangeevent.h"

PageChangeEvent::PageChangeEvent(QString page): QEvent(Globals::eventType), page(page)
{}

QString PageChangeEvent::getPage()
{
    return page;
}
