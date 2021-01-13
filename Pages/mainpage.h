#ifndef MAINPAGE_H
#define MAINPAGE_H

#include <QList>
#include <QWidget>
#include <QVBoxLayout>
#include <QGraphicsOpacityEffect>
#include <QVariantAnimation>

#include "Components/searchform.h"
#include "Components/sidebar.h"
#include "Components/songitem.h"
#include "Common/player.h"
#include "Interfaces/isong.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainPage;}
QT_END_NAMESPACE

class MainPage : public QWidget
{
    Q_OBJECT

public:
    MainPage(QWidget *parent = nullptr);
    void resizeEvent(QResizeEvent*) override;
    void setHandlers();
    void initUI();
    ~MainPage();

private:
    Ui::MainPage *ui;
    SearchForm* form;
    SideBar* sidebar;
    Player *player;

private slots:
    void menuChange(bool);
    void showSongs(QList<ISong> songs);
};
#endif // MAINPAGE_H
