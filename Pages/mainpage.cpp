#include "mainpage.h"
#include "ui_mainpage.h"
#include "Components/burger.h"
#include "Common/database.h"

MainPage::MainPage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainPage)
{
    ui->setupUi(this);
    initUI();
    setHandlers();
}

void MainPage::setHandlers()
{
    connect(ui->burger, SIGNAL(change(bool)), this, SLOT(menuChange(bool)));
    connect(ui->search, SIGNAL(change(bool)), form, SLOT(changeVisible(bool)));
    connect(ui->burger, SIGNAL(change(bool)), sidebar, SLOT(changeSize(bool)));
}

void MainPage::initUI()
{
    this->ui->control->hide();

    //add sidebar
    sidebar = new SideBar(this);
    sidebar->setGeometry(0, 0, 0, height());

    //add search form
    form = new SearchForm(this);
    form->hide();
    auto eff = new QGraphicsOpacityEffect(this);
    eff->setOpacity(0);

    form->setGraphicsEffect(eff);

    //init songs
    player = Player::getInstance();
    connect(player, &Player::songsListChanged, this, &MainPage::showSongs);
}

void MainPage::showSongs(QList<ISong> songs)
{
    QVBoxLayout *layout = qobject_cast<QVBoxLayout*>(ui->scrollAreaWidgetContents->layout());

    foreach(ISong song, songs){
        //add song item
        SongItem* songItem = new SongItem(song);
        layout->addWidget(songItem);

        //add handler
        connect(songItem, &SongItem::songChoosed, player, &Player::changeCurrentSong);
    }

    layout->addStretch(10);
}

void MainPage::menuChange(bool isActive)
{
    sidebar->setGeometry(0, 50, isActive ? 200 : 0, height());
}

void MainPage::resizeEvent(QResizeEvent *)
{
    form->move(width() - form->width() - 20, 45);
    sidebar->setGeometry(0, 50, sidebar->width(), height());
}

MainPage::~MainPage()
{
    delete ui;
}
