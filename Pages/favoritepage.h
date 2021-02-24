#ifndef FAVORITEPAGE_H
#define FAVORITEPAGE_H

#include <QWidget>

#include "Components/sidebar.h"
#include "Common/player.h"
#include "Common/Sources/favoritesource.h"

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
    void showEvent(QShowEvent *event) override;
    ~FavoritePage();

public slots:
    void menuChange(bool);

private:
    Ui::FavoritePage *ui;
    SideBar* sidebar;
    Player *player;
};

#endif // FAVORITEPAGE_H
