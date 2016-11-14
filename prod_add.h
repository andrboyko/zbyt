#ifndef PROD_ADD_H
#define PROD_ADD_H

#include <QWidget>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlError>
#include <QDebug>
#include <QMessageBox>
#include <QShortcut>
namespace Ui {
class prod_add;
}

class prod_add : public QWidget
{
    Q_OBJECT

public:
    explicit prod_add(QWidget *parent = 0);
    ~prod_add();

signals:
    void buttonclicked();


private slots:
    void on_pushButton_clicked();

private:
    Ui::prod_add *ui;
    QSqlQuery * query;
    QSqlQueryModel *model;
    QShortcut *keyCancel;
};

#endif // PROD_ADD_H
