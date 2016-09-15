#include "create_ttn.h"
#include "ui_create_ttn.h"

create_ttn::create_ttn(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::create_ttn)
{
    ui->setupUi(this);

    QString sql;

    ui->dateEdit->setDate(QDate::currentDate());

    model = new QSqlQueryModel(this);
    model->setQuery("select operation_name from operations;");
    ui->comboBox->setModel(model);
    ui->comboBox->setModelColumn(0);
    ui->comboBox->setMaxVisibleItems(ui->comboBox->count());

    model = new QSqlQueryModel(this);
    model->setQuery("select cust_name from custumers;");
    ui->comboBox_2->setModel(model);
    ui->comboBox_2->setModelColumn(0);
    ui->comboBox_2->setMaxVisibleItems(ui->comboBox_2->count());



    sql = "SELECT products.prod_id, prod_name, ttn_item_quantity, ttn_item_price, ttn_item_quantity*ttn_item_price FROM products, ttn_items where ttn_items.prod_id = products.prod_id  and ttn_id =194046;";
    model = new QSqlQueryModel(this);
    model->setQuery(sql);
    ui->tableView->setModel(model);
    model->setHeaderData(0,Qt::Horizontal, "Шифр");
    model->setHeaderData(1,Qt::Horizontal, "Найменування");
    model->setHeaderData(2,Qt::Horizontal, "Кількість");
    model->setHeaderData(3,Qt::Horizontal, "Ціна, грн.");
    model->setHeaderData(4,Qt::Horizontal, "Сума, грн.");
    ui->tableView->setColumnWidth(0,95);
    ui->tableView->setColumnWidth(1,300);
    ui->tableView->setColumnWidth(2,65);
    ui->tableView->setColumnWidth(3,65);
    ui->tableView->setColumnWidth(4,75);
}

create_ttn::~create_ttn()
{
    delete ui;
}
