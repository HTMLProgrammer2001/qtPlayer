#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>

#include "searchform.h"
#include "ui_searchform.h"
#include "Common/player.h"

SearchForm::SearchForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SearchForm)
{
    ui->setupUi(this);
    this->addHandlers();
}

SearchForm::~SearchForm()
{
    delete ui;
}

void SearchForm::changeVisible(bool state)
{
    auto eff = new QGraphicsOpacityEffect(this);
    auto anim = new QPropertyAnimation(eff, "opacity");

    state ? show() : hide();

    setGraphicsEffect(eff);
    anim->setStartValue(state ? 0 : 1);
    anim->setEndValue(state ? 1 : 0);
    anim->setDuration(300);

    anim->start();
}

void SearchForm::addHandlers()
{
    auto player = Player::getInstance();
    connect(ui->lineEdit, &QLineEdit::returnPressed, [=](){
        player->changeFilter(ui->lineEdit->text());
    });
}
