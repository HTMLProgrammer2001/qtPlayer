#include <QtSql/QSqlTableModel>

#include "pathspage.h"
#include "ui_pathspage.h"
#include "Common/database.h"

PathsPage::PathsPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PathsPage)
{
    ui->setupUi(this);
    this->db = Database::getInstance();

    initUI();
    initTable();
    addHandlers();
}

void PathsPage::initTable()
{
    this->model = new QSqlTableModel();
    this->model->setTable("paths");
    this->model->select();
    qDebug() << this->model->rowCount();
    ui->tableView->setModel(this->model);
}

void PathsPage::initUI()
{
    sidebar = new SideBar(this);
    sidebar->setGeometry(0, 0, 0, height());

    ui->tableView->horizontalHeader()->hide();
    ui->tableView->horizontalHeader()->setStretchLastSection(true);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void PathsPage::menuChange(bool isOpen)
{
    sidebar->setGeometry(0, 50, isOpen ? 200 : 0, height());
}

void PathsPage::addHandlers()
{
    connect(this->ui->add, &QPushButton::clicked, this, &PathsPage::addRow);
    connect(this->ui->remove, &QPushButton::clicked, this, &PathsPage::deleteRow);
    connect(this->ui->edit, &QPushButton::clicked, this, &PathsPage::editRow);
    connect(this->ui->burger, &IClickable::change, this, &PathsPage::menuChange);
}

void PathsPage::addRow()
{
    QString path = QFileDialog::getExistingDirectory(this);

    if(path.isEmpty()){
        QMessageBox::warning(this, "Error", "Select path");
        return;
    }

    if(db->addPath(path))
        this->model->select();
    else
        QMessageBox::warning(this, "Error", "No added");
}

void PathsPage::deleteRow()
{
    auto indexes = this->ui->tableView->selectionModel()->selectedIndexes();
    auto db = Database::getInstance();

    foreach(auto index, indexes){
        QString path = index.data().toString();
        qDebug() << path;

        if(!db->removePath(path))
            QMessageBox::warning(this, "Delete error", QString("Delete error for ?").arg(0, path));
    }

    this->model->select();
}

void PathsPage::editRow()
{
    auto db = Database::getInstance();
    auto indexes = this->ui->tableView->selectionModel()->selectedIndexes();

    if(indexes.size() != 1){
        QMessageBox::warning(this, "Edit error", "Select only 1 row");
        return;
    }

    QString newPath = QFileDialog::getExistingDirectory(this);

    if(db->editPath(indexes.at(0).data().toString(), newPath))
        this->model->select();
    else
        QMessageBox::warning(this, "Edit error", "Error in editing");
}

PathsPage::~PathsPage()
{
    delete ui;
}
