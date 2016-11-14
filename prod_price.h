#ifndef PROD_PRICE_H
#define PROD_PRICE_H

#include <QWidget>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QDebug>
#include <prod_add.h>
#include <prod_edit.h>
#include <QShortcut>


namespace Ui {
class prod_price;
}

class prod_price : public QWidget
{
    Q_OBJECT

public:
    explicit prod_price(QWidget *parent = 0);
    ~prod_price();

signals:
    sendData(int i);

private slots:
    void on_pushButton_clicked();
    void RefreshTabl_prod();

    void on_pushButton_2_clicked();

    void on_tableView_clicked(const QModelIndex &index);

private:
    Ui::prod_price *ui;
    QSqlQueryModel *model;
    prod_add *prodadd;
    prod_edit *prodedit;
    int index_prod;
    QShortcut *keyCancel;




};


#endif // PROD_PRICE_H
