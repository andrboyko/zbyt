#ifndef CUSTUMERS_ADD_H
#define CUSTUMERS_ADD_H

#include <QWidget>

namespace Ui {
class custumers_add;
}

class custumers_add : public QWidget
{
    Q_OBJECT

public:
    explicit custumers_add(QWidget *parent = 0);
    ~custumers_add();

private:
    Ui::custumers_add *ui;
};

#endif // CUSTUMERS_ADD_H
