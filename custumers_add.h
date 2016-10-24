#ifndef CUSTUMERS_ADD_H
#define CUSTUMERS_ADD_H

#include <QWidget>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>

namespace Ui {
class custumers_add;
}

class custumers_add : public QWidget
{
    Q_OBJECT

public:
    explicit custumers_add(QWidget *parent = 0);
    ~custumers_add();

signals:
    void buttonclicked();

private slots:
    void on_pushButton_clicked();

private:
    Ui::custumers_add *ui;
    QSqlQuery *query;

};

#endif // CUSTUMERS_ADD_H
