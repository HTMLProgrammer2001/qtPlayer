#ifndef FAVORITEPAGE_H
#define FAVORITEPAGE_H

#include "Common/Sources/favoritesource.h"
#include "Interfaces/iclickable.h"
#include "Pages/mainpage.h"


class FavoritePage : public MainPage
{
    Q_OBJECT

public:
    explicit FavoritePage(QWidget *parent = nullptr);
    void showEvent(QShowEvent *event) override;
    ~FavoritePage();
};

#endif // FAVORITEPAGE_H
