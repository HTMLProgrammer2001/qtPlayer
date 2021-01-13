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
}

MainWindow::~MainWindow()
{
    delete ui;
}
