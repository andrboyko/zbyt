#ifndef EDIT_TTN_H
#define EDIT_TTN_H

#include <QWidget>
#include <QSqlQueryModel>
#include <choise_goods.h>
#include <QSqlQuery>
#include <QDesktopWidget>
#include <QShortcut>

namespace Ui {
class edit_ttn;
}

class edit_ttn : public QWidget
{
    Q_OBJECT

private slots:

    void recieveData(int i);

public:
    explicit edit_ttn(QWidget *parent = 0);
    ~edit_ttn();

private:
    Ui::edit_ttn *ui;
    QSqlQuery *query;
};

#endif // EDIT_TTN_H
