#ifndef PLAYERCONTROL_H
#define PLAYERCONTROL_H

#include <QWidget>
#include<QStyle>
#include<QCommonStyle>
#include<QIcon>

#include "Interfaces/isong.h"
#include "Common/player.h"

namespace Ui {
class PlayerControl;
}

class PlayerControl : public QWidget
{
    Q_OBJECT

public:
    explicit PlayerControl(QWidget *parent = nullptr);
    ~PlayerControl();
    void addHandlers();

private:
    Ui::PlayerControl *ui;
    int duration = 0;

signals:
    void timeChanged(int time);
    void nextSong();
    void prevSong();

private slots:
    void songChanged(ISong song);
    void changeTime(int time);
    void playChange(bool isPlay);
};

#endif // PLAYERCONTROL_H
