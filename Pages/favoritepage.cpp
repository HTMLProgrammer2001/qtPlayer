#include "favoritepage.h"
#include "ui_favoritepage.h"

FavoritePage::FavoritePage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FavoritePage)
{
    ui->setupUi(this);
    initUI();

    this->player = Player::getInstance();
//    this->player->setSource(new FavoriteSource);

    addHandlers();
}

void FavoritePage::addHandlers()
{
    connect(ui->burger, &IClickable::change, this, &FavoritePage::menuChange);
}

void FavoritePage::initUI()
{
    sidebar = new SideBar(this);
    sidebar->setGeometry(0, 0, 0, height());
}

void FavoritePage::menuChange(bool isOpen)
{
    sidebar->setGeometry(0, 50, isOpen ? 200 : 0, height());
}

void FavoritePage::showEvent(QShowEvent *event)
{
    this->player->setSource(new FavoriteSource);
}

FavoritePage::~FavoritePage()
{
    delete ui;
}
