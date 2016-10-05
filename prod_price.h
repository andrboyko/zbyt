#ifndef PROD_PRICE_H
#define PROD_PRICE_H

#include <QWidget>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QDebug>
#include <QHBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QDoubleSpinBox>
namespace Ui {
class prod_price;
}

class prod_price : public QWidget
{
    Q_OBJECT

public:
    explicit prod_price(QWidget *parent = 0);
    ~prod_price();
    void RefreshTabl_prod();

private slots:
    void on_pushButton_clicked();
    void prod_add();

private:
    Ui::prod_price *ui;
    QSqlQueryModel *model;
    QSqlQuery *query;
};

#endif // PROD_PRICE_H
