#ifndef CREATE_TTN_H
#define CREATE_TTN_H

#include <QWidget>
#include <QSqlQueryModel>
namespace Ui {
class create_ttn;
}

class create_ttn : public QWidget
{
    Q_OBJECT

public:
    explicit create_ttn(QWidget *parent = 0);
    ~create_ttn();

private:
    Ui::create_ttn *ui;
    QSqlQueryModel *model;



};

#endif // CREATE_TTN_H
