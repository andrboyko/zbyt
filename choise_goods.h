#ifndef CHOISE_GOODS_H
#define CHOISE_GOODS_H

#include <QWidget>

namespace Ui {
class choise_goods;
}

class choise_goods : public QWidget
{
    Q_OBJECT

public:
    explicit choise_goods(QWidget *parent = 0);
    ~choise_goods();

private:
    Ui::choise_goods *ui;
};

#endif // CHOISE_GOODS_H
