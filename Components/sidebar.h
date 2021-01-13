#ifndef SIDEBAR_H
#define SIDEBAR_H

#include <QWidget>

namespace Ui {
class SideBar;
}

class SideBar : public QWidget
{
    Q_OBJECT

public:
    explicit SideBar(QWidget *parent = nullptr);
    ~SideBar();

private:
    Ui::SideBar *ui;

public slots:
    void changeSize(bool);
};

#endif // SIDEBAR_H
