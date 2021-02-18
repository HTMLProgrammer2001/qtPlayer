#ifndef FAVORITEPAGE_H
#define FAVORITEPAGE_H

#include <QWidget>

#include "Components/sidebar.h"

namespace Ui {
class FavoritePage;
}

class FavoritePage : public QWidget
{
    Q_OBJECT

public:
    explicit FavoritePage(QWidget *parent = nullptr);
    void addHandlers();
    void initUI();
    ~FavoritePage();

public slots:
    void menuChange(bool);

private:
    Ui::FavoritePage *ui;
    SideBar* sidebar;
};

#endif // FAVORITEPAGE_H
