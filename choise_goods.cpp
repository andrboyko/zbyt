#include "choise_goods.h"
#include "ui_choise_goods.h"

choise_goods::choise_goods(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::choise_goods)
{
    ui->setupUi(this);
}

choise_goods::~choise_goods()
{
    delete ui;
}
