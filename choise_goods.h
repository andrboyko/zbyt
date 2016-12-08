#ifndef CHOISE_GOODS_H
#define CHOISE_GOODS_H

#include <QWidget>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>
#include <QShortcut>

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

public slots:
    void recieveData(int i, bool e);

private:
    Ui::choise_goods *ui;
    QSqlQueryModel *model;
    QSqlQuery *query;
    QSqlQuery *query2;
    QSqlQuery *queryUpdate;
    int ttn_id;
    int temp_nomlVc;
    int prod_id;
    QShortcut *keyCancel;
    bool edit;
};

#endif // CHOISE_GOODS_H
