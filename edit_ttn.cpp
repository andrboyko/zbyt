#include "edit_ttn.h"
#include "ui_edit_ttn.h"



edit_ttn::edit_ttn(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::edit_ttn)
{
    ui->setupUi(this);
}

edit_ttn::~edit_ttn()
{
    delete ui;
}

void edit_ttn::recieveData(int i)
{


    query = new QSqlQuery();
    query->exec(" ");

    while (query->next())
    {

    }
}
