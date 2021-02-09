#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>

#include "Components/sidebar.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow;}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    QStackedWidget* stack;
    SideBar* sidebar;

public:
    MainWindow(QWidget *parent = nullptr);
    void addHandlers();
    void resizeEvent(QResizeEvent* ev) override;
    bool event(QEvent *event) override;
    ~MainWindow();

private:
    Ui::MainWindow *ui;

signals:
    void pageChanged(int);
};
#endif // MAINWINDOW_H
