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

void View_ttn::recieveData(int temp_nom)
{

    // заповнення таблиці даними
    QString sql;
    sql = "SELECT products.prod_id, prod_name, ttn_item_quantity, ttn_item_price, ttn_item_quantity*ttn_item_price FROM products, ttn_items where ttn_items.prod_id = products.prod_id  and ttn_id =" +QString::number(temp_nom)+ ";";
    model = new QSqlQueryModel();
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

    ui->label->setText("ПЕРЕГЛЯД НАКЛАДНОЇ № " + QString::number(temp_nom));

    // дата ТТН
    query = new QSqlQuery();
    query->prepare("SELECT DATE_FORMAT(ttn_date,'%d.%m.%Y') FROM ttn WHERE ttn_id = (:ttn_id)");
    query->bindValue(":ttn_id", temp_nom);
    query->exec();
    while (query->next())
    {
        ui->label_6->setText(query->value(0).toString() + " року");
    }
    // Замовник
    query->prepare("SELECT cust_name from custumers, ttn where custumers.cust_id = ttn.cust_id AND ttn.ttn_id = (:ttn_id) ;");
    query->bindValue(":ttn_id", temp_nom);
    query->exec();
    while (query->next())
    {
        ui->lineEdit->setText(query->value(0).toString());
    }
    // через кого
    query->prepare("SELECT by_whom FROM ttn where ttn_id = (:ttn_id) ;");
    query->bindValue(":ttn_id", temp_nom);
    query->exec();
    while (query->next())
    {
        ui->lineEdit_2->setText(query->value(0).toString());
    }
    // Умова продажу
    query->prepare("SELECT umova FROM ttn where ttn_id = (:ttn_id) ;");
    query->bindValue(":ttn_id", temp_nom);
    query->exec();
    while (query->next())
    {
        ui->lineEdit_3->setText(query->value(0).toString());
    }

    // Умова продажу
    query->prepare("SELECT sum FROM ttn where ttn_id = (:ttn_id) ;");
    query->bindValue(":ttn_id", temp_nom);
    query->exec();
    while (query->next())
    {
        ui->label_5->setText("Сума " + query->value(0).toString() + " грн. ");
    }





}




