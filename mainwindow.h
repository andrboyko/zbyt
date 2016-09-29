#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QDebug>
#include <QDate>
#include <view_ttn.h>
#include <create_ttn.h>


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
    void findByDate();

signals:
    void sendData(int temp_nom);



private slots:
    void on_pushButton_6_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_clicked();

    void on_pushButton_11_clicked();

    void on_tableView_doubleClicked(const QModelIndex &index);

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
    QSqlQueryModel *model;
    View_ttn *viewttn;
    create_ttn *createttn;
    QSqlQuery *query;
    int index_del;
};

#endif // MAINWINDOW_H
