#include "search.h"

Search::Search(QWidget* parent): QLabel(parent)
{}

void Search::mousePressEvent(QMouseEvent *ev)
{
    emit clicked();
}
