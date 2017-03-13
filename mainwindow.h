#ifndef MAINWINDOW_H
#define MAINWINDOW_H

/*Локальные, пользовательские классы*/
#include "custumers.h"
#include "ttn.h"
#include "products.h"
#include "print_ttn.h"
#include "prod_coming.h"

/*Стандартные классы Qt*/
#include <QMainWindow>
#include <QDebug>
#include <QMessageBox>
#include <QTextCodec>
#include <QWidget>
#include <QTableView>
#include <QVBoxLayout>

#include <QFile>
#include <QDateTime>

#include <QDate>
#include <QSortFilterProxyModel>

#include <QSqlQueryModel>
#include <QSqlTableModel>
#include <QSqlQuery>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:
    void sendData(int i, bool e);

private slots:

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_7_clicked();

    void on_lineEdit_textChanged(const QString &arg1);

    void on_action_triggered();

    void on_action_2_triggered();

    void RefreshTabl_prod();

    void RefreshTabl_cust();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void RefreshTabl_ttn();

    void RefreshTabl_coming();

    void on_pushButton_10_clicked();

    void on_tableView_doubleClicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_action_4_triggered();

    void on_tableView_clicked(const QModelIndex &index);

    void on_comboBox_currentIndexChanged(int index);

    void on_spinBox_valueChanged(int arg1);



private:
    Ui::MainWindow *ui;
    QSqlQueryModel *model;
    QSqlTableModel *tableModel;
    ttn *t_t_n;
    prod_coming *prodcoming;
    print_ttn *printttn;
    QSqlQuery *query;
    QSqlQuery *query2;
    QSqlQuery *queryUpdate;
    products *prod;
    custumers *cust;
    int index_table=0;
    QSortFilterProxyModel * proxyModel;
    QTableView *our_requisites;
    QVBoxLayout *verticalLayout;
    QWidget *widget;
    QFile *logFile;
    QTextStream log;

};

#endif // MAINWINDOW_H
