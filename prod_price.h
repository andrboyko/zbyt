#ifndef PROD_PRICE_H
#define PROD_PRICE_H

#include <QWidget>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QDebug>
#include <prod_add.h>


namespace Ui {
class prod_price;
}

class prod_price : public QWidget
{
    Q_OBJECT

public:
    explicit prod_price(QWidget *parent = 0);
    ~prod_price();



private slots:
    void on_pushButton_clicked();
    void RefreshTabl_prod();

private:
    Ui::prod_price *ui;
    QSqlQueryModel *model;
    prod_add * prodadd;




};


#endif // PROD_PRICE_H
