#ifndef CUSTOMERS_H
#define CUSTOMERS_H

#include <QWidget>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QDebug>
#include <custumers_add.h>
#include <custumers_edit.h>

namespace Ui {
class customers;
}

class customers : public QWidget
{
    Q_OBJECT

public:
    explicit customers(QWidget *parent = 0);
    ~customers();



signals:
    void sendData(int i);

private slots:
    void on_pushButton_clicked();
     void RefreshTabl_customers();

     void on_pushButton_2_clicked();

     void on_tableView_clicked(const QModelIndex &index);

private:
    Ui::customers *ui;
    QSqlQueryModel *model;
    custumers_add *cust_add;
    custumers_edit *cust_edit;
    int index_cust;


};

#endif // CUSTOMERS_H
