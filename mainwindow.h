#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QDebug>
#include <QDate>
#include <create_ttn.h>
#include <prod_price.h>
#include <customers.h>


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
    void on_lineEdit_editingFinished();
    void on_comboBox_currentIndexChanged(int index);
    void on_spinBox_valueChanged(int arg1);
    void RefreshTabl_ttn();

signals:
    void sendData(int temp_nom);



private slots:

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_7_clicked();

private:
    Ui::MainWindow *ui;
    QSqlQueryModel *model;
    create_ttn *createttn;
    QSqlQuery *query;
    prod_price *prodprice;
    customers *cust;
    int index_ttn;
};

#endif // MAINWINDOW_H
