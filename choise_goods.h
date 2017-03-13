#ifndef CHOISE_GOODS_H
#define CHOISE_GOODS_H

/*Стандартные классы Qt*/
#include <QWidget>
#include <QDebug>
#include <QMessageBox>
#include <QShortcut>

#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QSqlError>

namespace Ui {
class choise_goods;
}

class choise_goods : public QWidget
{
    Q_OBJECT

public:
    explicit choise_goods(QWidget *parent = 0);
    ~choise_goods();


signals:
    void update_table();

private slots:
    void on_listView_clicked(const QModelIndex &index);

    void on_pushButton_2_clicked();

    void on_listView_2_clicked(const QModelIndex &index);

    void on_spinBox_valueChanged(int arg1);

    void on_doubleSpinBox_valueChanged(double arg1);

    void on_pushButton_clicked();

    void recieveData(int i, bool e);

    void recieveComingOperation(bool o);

private:
    Ui::choise_goods *ui;

    QSqlQueryModel *model;
    QSqlQuery *query;
    QSqlQuery *query2;
    QSqlQuery *queryUpdate;
    int ttn_id;
    int temp_nomlVc;
    int prod_id;
    int ttn_item_quantity;
    QShortcut *keyCancel;
    bool edit;
    bool comingBool;
};

#endif // CHOISE_GOODS_H
