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
    showSongs({});
}

void MainPage::setHandlers()
{
    connect(ui->burger, &IClickable::change, this, &MainPage::menuChange);
    connect(ui->search, &IClickable::change, form, &SearchForm::changeVisible);
    connect(ui->burger, &IClickable::change, sidebar, &SideBar::changeSize);
    connect(ui->sort, &IClickable::change, player, &Player::changeSort);

    connect(player, &Player::changeLoading, this, [&](bool){
        showSongs(player->getSongs());
    });

    connect(ui->reload, &IClickable::change, player, [&](bool){
        player->reload();
    });
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
    QVBoxLayout *oldLayout = qobject_cast<QVBoxLayout*>(ui->scrollAreaWidgetContents->layout());
    delete oldLayout;
    qDeleteAll(ui->scrollAreaWidgetContents->children());

    QVBoxLayout* layout = new QVBoxLayout();

    while(layout->count() > 0){
        auto item = layout->takeAt(0);
        layout->removeItem(item);
    }

    if(player->getLoading()){
        //set label
        QLabel *label = new QLabel("Loading...");
        label->setAlignment(Qt::AlignCenter);
        label->setStyleSheet("color: #aaa; font-size: 12pt");

        layout->addWidget(label);
    }
    else{
        if(songs.size() == 0){
            //set label
            QLabel *label = new QLabel("No items");
            label->setAlignment(Qt::AlignCenter);
            label->setStyleSheet("color: #aaa; font-size: 12pt");

            layout->addWidget(label);
        }
        else{
            foreach(ISong song, songs){
                //add song item
                SongItem* songItem = new SongItem(song);
                layout->addWidget(songItem);

                //add handler
                connect(songItem, &SongItem::songChoosed, player, &Player::changeCurrentSong);
            }
        }
    }

    layout->addStretch(10);
    ui->scrollAreaWidgetContents->setLayout(layout);
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
