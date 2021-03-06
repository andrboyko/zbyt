#ifndef CUSTUMERS_H
#define CUSTUMERS_H

/*Стандартные классы Qt*/
#include <QWidget>
#include <QDebug>
#include <QMessageBox>
#include <QShortcut>

#include <QSqlQuery>
#include <QSqlError>

namespace Ui {
class custumers;
}

class custumers : public QWidget
{
    Q_OBJECT

public:
    explicit custumers(QWidget *parent = 0);
    ~custumers();

signals:
    void update_table();

private slots:
    void on_pushButton_clicked();

    void receiveData(int i, bool e);

private:
    Ui::custumers *ui;
    QSqlQuery *query;
    QShortcut *keyCancel;
    int index_table;
    bool edit;

};

#endif // CUSTUMERS_H
