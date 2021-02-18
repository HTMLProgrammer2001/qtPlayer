#ifndef FAVORITEPAGE_H
#define FAVORITEPAGE_H

#include <QWidget>

namespace Ui {
class FavoritePage;
}

class FavoritePage : public QWidget
{
    Q_OBJECT

public:
    explicit FavoritePage(QWidget *parent = nullptr);
    ~FavoritePage();

private:
    Ui::FavoritePage *ui;
};

#endif // FAVORITEPAGE_H
