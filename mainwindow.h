#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QDebug>
#include <QDate>
#include <ttn.h>
#include <custumers.h>
#include <products.h>
#include <QSortFilterProxyModel>
#include <QMessageBox>
#include <prod_coming.h>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
public slots:
    void on_tableView_clicked(const QModelIndex &index);
    void on_comboBox_currentIndexChanged(int index);
    void on_spinBox_valueChanged(int arg1);


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



private:
    Ui::MainWindow *ui;
    QSqlQueryModel *model;
    ttn *t_t_n;
    prod_coming *prodcoming;
    QSqlQuery *query;
    QSqlQuery *query2;
    QSqlQuery *queryUpdate;
    products *prod;
    custumers *cust;
    int index_table;
    QSortFilterProxyModel * proxyModel;
};

#endif // MAINWINDOW_H
