#ifndef SEARCHFORM_H
#define SEARCHFORM_H

#include <QWidget>
#include <QDebug>

namespace Ui {
class SearchForm;
}

class SearchForm : public QWidget
{
    Q_OBJECT

public:
    explicit SearchForm(QWidget *parent = nullptr);
    ~SearchForm();

private:
    Ui::SearchForm *ui;

public slots:
    void changeVisible(bool);

signals:
    void search(QString);
};

#endif // SEARCHFORM_H
