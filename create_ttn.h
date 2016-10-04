#ifndef CREATE_TTN_H
#define CREATE_TTN_H

#include <QWidget>
#include <QSqlQueryModel>
#include <choise_goods.h>
#include <QSqlQuery>
namespace Ui {
class create_ttn;
}

class create_ttn : public QWidget
{
    Q_OBJECT

public:
    explicit create_ttn(QWidget *parent = 0);
    ~create_ttn();

signals:
    void sendData(int r_ttn_id);
    void PushB4();



private slots:
    void on_pushButton_clicked();

    void refreshTable();

    void on_lineEdit_returnPressed();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_tableView_clicked(const QModelIndex &index);

    void on_pushButton_4_clicked();

private:
    Ui::create_ttn *ui;
    QSqlQueryModel *model;
    choise_goods *goods;
    QSqlQuery *query;
    QString index_del;
    double sum;


};

#endif // CREATE_TTN_H
