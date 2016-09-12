#ifndef VIEW_TTN_H
#define VIEW_TTN_H

#include <QWidget>
#include <QSqlQueryModel>
#include <QDebug>
#include <QSqlQuery>



namespace Ui {
class View_ttn;
}

class View_ttn : public QWidget
{
    Q_OBJECT

public:
    explicit View_ttn(QWidget *parent = 0);
    ~View_ttn();


public slots:
    void recieveData(int temp_nom);


private:
    Ui::View_ttn *ui;
    QSqlQueryModel *model;
    QSqlQuery *query;



};

#endif // VIEW_TTN_H
