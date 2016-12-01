#ifndef TTN_H
#define TTN_H

#include <QWidget>
#include <QSqlQueryModel>
#include <choise_goods.h>
#include <QSqlQuery>
#include <QDesktopWidget>
#include <QShortcut>
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
    void sendData(int r_ttn_id);
    void PushB4();



private slots:
    void on_pushButton_clicked();

    void refreshTable_goods();

    void on_pushButton_3_clicked();

    void on_tableView_clicked(const QModelIndex &index);

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void moveToCenter();

    void on_comboBox_2_currentIndexChanged(int index);

    void on_comboBox_currentIndexChanged(int index);

    void receiveData(int i, bool e);

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
    bool edit;


};

#endif // TTN_H
