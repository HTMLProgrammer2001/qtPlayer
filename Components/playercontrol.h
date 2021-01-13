#ifndef PLAYERCONTROL_H
#define PLAYERCONTROL_H

#include <QWidget>

namespace Ui {
class PlayerControl;
}

class PlayerControl : public QWidget
{
    Q_OBJECT

public:
    explicit PlayerControl(QWidget *parent = nullptr);
    ~PlayerControl();

private:
    Ui::PlayerControl *ui;
};

#endif // PLAYERCONTROL_H
