#ifndef PATHSPAGE_H
#define PATHSPAGE_H

#include <QWidget>

namespace Ui {
class PathsPage;
}

class PathsPage : public QWidget
{
    Q_OBJECT

public:
    explicit PathsPage(QWidget *parent = nullptr);
    ~PathsPage();

private:
    Ui::PathsPage *ui;
};

#endif // PATHSPAGE_H
