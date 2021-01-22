#ifndef SONGITEM_H
#define SONGITEM_H

#include <QWidget>
#include <QTime>

#include "Interfaces/isong.h"

namespace Ui {
class SongItem;
}

class SongItem : public QWidget
{
    Q_OBJECT

public:
    explicit SongItem(ISong song, QWidget *parent = nullptr);
    void mousePressEvent(QMouseEvent *event) override;
    void initUI();
    ~SongItem();

signals:
    void songChoosed(ISong);

private:
    Ui::SongItem *ui;
    ISong song;
};

#endif // SONGITEM_H
