#include "prod_price.h"
#include "ui_prod_price.h"

prod_price::prod_price(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::prod_price)
{
    ui->setupUi(this);
    RefreshTabl_prod();


}

prod_price::~prod_price()
{
    delete ui;
}

void prod_price::RefreshTabl_prod()
{
    model = new QSqlQueryModel;
    model->setQuery("SELECT prod_id, prod_name, prod_price_retail, prod_price_barter, prod_price_wholesale FROM zbyt.products;");
    ui->tableView->setModel(model);
    model->setHeaderData(0,Qt::Horizontal, "Шифр");
    model->setHeaderData(1,Qt::Horizontal, "Назва");
    model->setHeaderData(2,Qt::Horizontal, "Ціна,роздр.");
    model->setHeaderData(3,Qt::Horizontal, "Ціна,бартер");
    model->setHeaderData(4,Qt::Horizontal, "Ціна,опт");
    ui->tableView->setColumnWidth(0,100);
    ui->tableView->setColumnWidth(1,175);
    ui->tableView->setColumnWidth(2,80);
    ui->tableView->setColumnWidth(3,80);
    ui->tableView->setColumnWidth(4,80);
}


void prod_price::on_pushButton_clicked()
{
    prodadd = new prod_add;
    prodadd->setWindowFlags(Qt::Tool);
    connect(prodadd, SIGNAL(buttonclicked()), this, SLOT(RefreshTabl_prod()));
    prodadd->show();
    prodadd->activateWindow();


}

