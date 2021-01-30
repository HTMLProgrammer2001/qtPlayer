#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Pages/mainpage.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //create layout and set
    QStackedWidget* stacked = new QStackedWidget;
    stacked->addWidget(new MainPage);
    this->setCentralWidget(stacked);

    this->stack = stacked;

    //add sidebar
    sidebar = new SideBar(this);
    sidebar->setGeometry(0, 0, 0, height());
}

void MainWindow::addHandlers()
{

}

void MainWindow::resizeEvent(QResizeEvent *ev)
{
    sidebar->setGeometry(0, 50, sidebar->width(), height());
}

MainWindow::~MainWindow()
{
    delete ui;
}
