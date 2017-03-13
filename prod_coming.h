#ifndef PROD_COMING_H
#define PROD_COMING_H

/*Локальные, пользовательские классы*/
#include "choise_goods.h"

/*Стандартные классы Qt*/
#include <QWidget>

#include <QDebug>
#include <QMessageBox>
#include <QShortcut>
#include <QFile>
#include <QDateTime>

#include <QDesktopWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QSpinBox>

#include <QSqlQueryModel>
#include <QSqlQuery>

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
    void sendData(int i, bool e);
    void update_table();
    void sendComingOperation(bool o);

private slots:
    void refreshTable_goods();

    void on_pushButton_3_clicked();

    void on_tableView_clicked(const QModelIndex &index);

    void on_pushButton_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void receiveData(int i, bool e);

    void on_pushButton_6_clicked();

    void updateprice();

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
    bool edit;
    double sum;
    int index_table;
    int prod_quantity;
    int ttn_item_quantity;
    QFile *logFile;
    QTextStream log;


    QWidget *editQuantity;
    QVBoxLayout *verticalLayout;
    QPushButton *pushButton;
    QSpinBox *spinBox;


};

#endif // PROD_COMING_H
