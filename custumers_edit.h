#ifndef CUSTUMERS_EDIT_H
#define CUSTUMERS_EDIT_H

#include <QWidget>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>
#include <QMessageBox>
#include <QShortcut>

namespace Ui {
class custumers_edit;
}

class custumers_edit : public QWidget
{
    Q_OBJECT

public:
    explicit custumers_edit(QWidget *parent = 0);
    ~custumers_edit();

signals:
    void buttonclicked();

public slots:
    void reciveData(int i);

private slots:
    void on_pushButton_clicked();



private:
    Ui::custumers_edit *ui;
    QSqlQuery *query;
    int index_cust;
    QShortcut *keyCancel;

};

#endif // CUSTUMERS_EDIT_H
