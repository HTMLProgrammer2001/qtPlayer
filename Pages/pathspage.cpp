#include "pathspage.h"
#include "ui_pathspage.h"

PathsPage::PathsPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PathsPage)
{
    ui->setupUi(this);
}

PathsPage::~PathsPage()
{
    delete ui;
}
