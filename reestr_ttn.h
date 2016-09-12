#ifndef REESTR_TTN_H
#define REESTR_TTN_H

#include <QMainWindow>
#include <QSqlQueryModel>
#include <QDebug>
#include <QDate>
#include <view_ttn.h>



namespace Ui {
class reestr_ttn;
}

class reestr_ttn : public QMainWindow
{
    Q_OBJECT

public:
    explicit reestr_ttn(QWidget *parent = 0);
    ~reestr_ttn();


signals:
    void sendData(int temp_nom);


private slots:
    void on_spinBox_valueChanged(int arg1);

    void findByDate();

    void on_comboBox_currentIndexChanged(int index);

    void on_lineEdit_editingFinished();

    void on_tableView_clicked(const QModelIndex &index);

    void on_pushButton_clicked();


    void on_tableView_doubleClicked(const QModelIndex &index);

private:
    Ui::reestr_ttn *ui;
    QSqlQueryModel *model;
    View_ttn *viewttn;


};

#endif // REESTR_TTN_H
