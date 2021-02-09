#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Pages/mainpage.h"
#include "Pages/pathspage.h"
#include "Common/globals.h"
#include "Events/pagechangeevent.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //create layout and set
    QStackedWidget* stacked = new QStackedWidget;
    stacked->addWidget(new MainPage);
    stacked->addWidget(new PathsPage());
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

bool MainWindow::event(QEvent *event)
{
    if(event->type() != Globals::eventType)
        return QWidget::event(event);

    qDebug() << "Page change";

    PageChangeEvent* pageEvent = static_cast<PageChangeEvent*>(event);

    if(pageEvent->getPage() == "resources")
        this->stack->setCurrentIndex(1);
    else
        this->stack->setCurrentIndex(0);

    return true;
}

MainWindow::~MainWindow()
{
    delete ui;
}
