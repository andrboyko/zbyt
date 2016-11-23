#ifndef PRODUCTS_H
#define PRODUCTS_H

#include <QWidget>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlError>
#include <QDebug>
#include <QMessageBox>
#include <QShortcut>
namespace Ui {
class products;
}

class products : public QWidget
{
    Q_OBJECT

public:
    explicit products(QWidget *parent = 0);
    ~products();

signals:
    void buttonclicked();


private slots:
    void on_pushButton_clicked();

    void receiveData(int i, bool e);

    void on_comboBox_currentIndexChanged(int index);

    void on_comboBox_2_currentIndexChanged(int index);

private:
    Ui::products *ui;
    QSqlQuery * query;
    QSqlQueryModel *model;
    QShortcut *keyCancel;
    int index_table;
    bool edit;
    int units_id;
    int prod_group_id;

};

#endif // PRODUCTS_H
