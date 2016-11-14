#ifndef PROD_EDIT_H
#define PROD_EDIT_H

#include <QWidget>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlError>
#include <QDebug>
#include <QMessageBox>
#include <QShortcut>

namespace Ui {
class prod_edit;
}

class prod_edit : public QWidget
{
    Q_OBJECT

public:
    explicit prod_edit(QWidget *parent = 0);
    ~prod_edit();

signals:
       void buttonclicked();

private slots:
       void on_pushButton_clicked();
       void recieveData(int i);


private:
    Ui::prod_edit *ui;
    QSqlQuery *query;
    int index_prod;
    QShortcut *keyCancel;
};

#endif // PROD_EDIT_H
