#include "favoritepage.h"
#include "ui_mainpage.h"

FavoritePage::FavoritePage(QWidget *parent): MainPage(parent)
{
}

void FavoritePage::showEvent(QShowEvent *event)
{
    this->player->setSource(new FavoriteSource);
    this->ui->label->setText("Favorite");
}

FavoritePage::~FavoritePage()
{
}
