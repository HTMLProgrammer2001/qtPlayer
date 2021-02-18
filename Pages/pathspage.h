#ifndef PATHSPAGE_H
#define PATHSPAGE_H

#include <QWidget>
#include <QFileDialog>
#include <QMessageBox>

#include "Components/sidebar.h"
#include "Common/database.h"

namespace Ui {
class PathsPage;
}

class PathsPage : public QWidget
{
    Q_OBJECT

private:
    QSqlTableModel *model = nullptr;

public:
    explicit PathsPage(QWidget *parent = nullptr);
    void addHandlers();
    void initTable();
    void initUI();
    ~PathsPage();

private:
    Ui::PathsPage *ui;
    SideBar *sidebar;

public slots:
    void menuChange(bool);
    void addRow();
    void deleteRow();
    void editRow();
};

#endif // PATHSPAGE_H
