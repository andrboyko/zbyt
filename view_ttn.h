#ifndef VIEW_TTN_H
#define VIEW_TTN_H

#include <QWidget>
#include <QSqlQueryModel>
#include <QDebug>

namespace Ui {
class View_ttn;
}

class View_ttn : public QWidget
{
    Q_OBJECT

public:
    explicit View_ttn(QWidget *parent = 0);
    ~View_ttn();

private slots:
    void viewByTNTid();

private:
    Ui::View_ttn *ui;
    QSqlQueryModel * model;



};

#endif // VIEW_TTN_H
