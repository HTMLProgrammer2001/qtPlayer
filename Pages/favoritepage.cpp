#include "favoritepage.h"
#include "ui_favoritepage.h"

FavoritePage::FavoritePage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FavoritePage)
{
    ui->setupUi(this);
}

FavoritePage::~FavoritePage()
{
    delete ui;
}
