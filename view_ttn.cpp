#include "view_ttn.h"
#include "ui_view_ttn.h"


View_ttn::View_ttn(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::View_ttn)
{
    ui->setupUi(this);


 }

View_ttn::~View_ttn()
{
    delete ui;
}

void View_ttn::viewByTNTid()
{
    QString sql;

    sql = "SELECT prod_name, ttn_item_price, ttn_item_quantity FROM products, ttn_items where ttn_items.prod_id =products.s_num  and ttn_id = 194046;";
    model = new QSqlQueryModel;
    model->setQuery(sql);
    ui->tableView->setModel(model);

}


