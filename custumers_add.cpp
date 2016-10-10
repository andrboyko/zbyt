#include "custumers_add.h"
#include "ui_custumers_add.h"

custumers_add::custumers_add(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::custumers_add)
{
    ui->setupUi(this);

}

custumers_add::~custumers_add()
{
    delete ui;
}
