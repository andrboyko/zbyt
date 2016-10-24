#ifndef CUSTOMERS_H
#define CUSTOMERS_H

#include <QWidget>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QDebug>
#include <custumers_add.h>

namespace Ui {
class customers;
}

class customers : public QWidget
{
    Q_OBJECT

public:
    explicit customers(QWidget *parent = 0);
    ~customers();


private slots:
    void on_pushButton_clicked();
     void RefreshTabl_customers();

private:
    Ui::customers *ui;
    QSqlQueryModel *model;
    custumers_add *cust_add;

};

#endif // CUSTOMERS_H
