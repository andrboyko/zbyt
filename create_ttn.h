#ifndef CREATE_TTN_H
#define CREATE_TTN_H

#include <QWidget>
#include <QSqlQueryModel>
#include <choise_goods.h>
#include <QSqlQuery>
#include <QDesktopWidget>
#include <QShortcut>
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

    void refreshTable_goods();

    void on_pushButton_3_clicked();

    void on_tableView_clicked(const QModelIndex &index);

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_comboBox_currentIndexChanged(int index);

    void moveToCenter();

private:
    Ui::create_ttn *ui;
    QSqlQueryModel *model;
    choise_goods *goods;
    QSqlQuery *query;
    QSqlQuery *query2;
    QString index_prod;
    double sum;
    QShortcut *keyCancel;


};

#endif // CREATE_TTN_H
