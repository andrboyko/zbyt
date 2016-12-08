#ifndef PROD_COMING_H
#define PROD_COMING_H

#include <QWidget>
#include <QSqlQueryModel>
#include <choise_goods.h>
#include <QSqlQuery>
#include <QDesktopWidget>
#include <QShortcut>
#include <choise_goods.h>

namespace Ui {
class prod_coming;
}

class prod_coming : public QWidget
{
    Q_OBJECT

public:
    explicit prod_coming(QWidget *parent = 0);
    ~prod_coming();

signals:
    void sendData(int i);
    void update_table();

private slots:
    void refreshTable_goods();

    void on_pushButton_3_clicked();

    void on_tableView_clicked(const QModelIndex &index);

    void on_pushButton_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

private:
    Ui::prod_coming *ui;
    QShortcut *keyCancel;
    QSqlQueryModel *model;
    QSqlQuery *query;
    QSqlQuery *query2;
    QSqlQuery *queryUpdate;
    choise_goods *goods;
    int index_prod;
    int operation_id;
};

#endif // PROD_COMING_H
