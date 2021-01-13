#ifndef SEARCH_H
#define SEARCH_H

#include<QLabel>

class Search: public QLabel
{
    Q_OBJECT
public:
    Search(QWidget* parent = 0);
    void mousePressEvent(QMouseEvent *ev) override;

signals:
    void clicked();
};

#endif // SEARCH_H
