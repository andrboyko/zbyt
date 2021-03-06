#ifndef TTN_H
#define TTN_H

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
class ttn;
}

class ttn : public QWidget
{
    Q_OBJECT

public:
    explicit ttn(QWidget *parent = 0);
    ~ttn();

signals:
    void sendData(int i, bool e);
    void update_table();
    void sendComingOperation(bool o);



private slots:
    void on_pushButton_clicked();

    void refreshTable_goods();

    void on_pushButton_3_clicked();

    void on_tableView_clicked(const QModelIndex &index);

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_comboBox_2_currentIndexChanged(int index);

    void on_comboBox_currentIndexChanged(int index);

    void receiveData(int i, bool e);

    void on_pushButton_6_clicked();

    void updateprice();

    void on_tableView_doubleClicked();

private:
    Ui::ttn *ui;
    QSqlQueryModel *model;
    choise_goods *goods;
    QSqlQuery *query;
    QSqlQuery *query2;
    QSqlQuery *queryUpdate;
    int index_prod;
    double sum;
    QShortcut *keyCancel;
    int operation_id;
    int cust_id;
    int index_table;
    int prod_quantity;
    int ttn_item_quantity;
    bool edit;
    QFile *logFile;
    QTextStream log;

    QWidget *editQuantity;
    QVBoxLayout *verticalLayout;
    QPushButton *pushButton;
    QSpinBox *spinBox;




};

#endif // TTN_H
