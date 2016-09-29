#include "create_ttn.h"
#include "ui_create_ttn.h"


create_ttn::create_ttn(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::create_ttn)
{
    ui->setupUi(this);
    goods = new choise_goods;
    goods->setWindowFlags(Qt::Tool);

    connect(this, SIGNAL(sendData(int)), goods, SLOT(recieveData(int)));
    connect(goods, SIGNAL(buttonclicked()), this, SLOT(refreshTable()));

    refreshTable();


}

create_ttn::~create_ttn()
{
    delete ui;
}

void create_ttn::on_pushButton_clicked()
{

goods->show();
emit sendData(ui->lineEdit->text().toInt());

}


void create_ttn::refreshTable()
{

    QString sql;
    sql = "SELECT products.prod_id, prod_name, ttn_item_quantity, ttn_item_price, ttn_item_quantity*ttn_item_price FROM products, ttn_items WHERE ttn_items.prod_id = products.prod_id AND ttn_id="+ui->lineEdit->text()+";";
    model = new QSqlQueryModel;
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

    //вивід суми
    query = new QSqlQuery();
    query->prepare("SELECT sum(ttn_item_quantity*ttn_item_price) FROM ttn_items WHERE ttn_id="+ui->lineEdit->text()+";");
    query->exec();

    while (query->next())
    {
        sum=query->value(0).toDouble();
        ui->label_7->setText("Сума "+QString::number(sum)+" грн.");
    }






}


void create_ttn::on_lineEdit_returnPressed()
{
    emit ui->pushButton_2->clicked();
}

void create_ttn::on_pushButton_2_clicked()
{
    ui->comboBox->setEnabled(true);
    ui->comboBox_2->setEnabled(true);
    ui->lineEdit_2->setEnabled(true);
    ui->lineEdit_3->setEnabled(true);
    ui->pushButton->setEnabled(true);
    ui->pushButton_3->setEnabled(true);
    ui->pushButton_4->setEnabled(true);
    ui->dateEdit->setEnabled(true);
    ui->dateEdit->setDate(QDate::currentDate());
    model = new QSqlQueryModel(this);
    model->setQuery("select operation_name from operations;");
    ui->comboBox->setModel(model);
    ui->comboBox->setModelColumn(0);
    ui->comboBox->setMaxVisibleItems(ui->comboBox->count());

    model = new QSqlQueryModel(this);
    model->setQuery("select cust_name, cust_id from custumers;");
    ui->comboBox_2->setModel(model);
    ui->comboBox_2->setModelColumn(0);
    ui->comboBox_2->setMaxVisibleItems(ui->comboBox_2->count());
    refreshTable();


}
//видалити товар
void create_ttn::on_pushButton_3_clicked()
{

    query = new QSqlQuery();
    query->prepare("DELETE FROM ttn_items WHERE ttn_id = :ttn_id AND prod_id = :prod_id;");
    query->bindValue(":ttn_id", ui->lineEdit->text());
    query->bindValue(":prod_id", index_del);
    query->exec();
    refreshTable();

}

void create_ttn::on_tableView_clicked(const QModelIndex &index)
{
    index_del = ui->tableView->model()->data(ui->tableView->model()->index(index.row(),0)).toString();
}

void create_ttn::on_pushButton_4_clicked()
{
    query = new QSqlQuery();
    query->prepare("INSERT INTO ttn(ttn_id, ttn_date, cust_id, operation_id, by_whom, sum, umova)VALUES(:ttn_id, :ttn_date,(select cust_id from custumers where cust_name=:cust_id), (SELECT operation_id FROM operations WHERE operation_name =:operation_id), :by_whom, :sum, :umova);");
    query->bindValue(":ttn_id", ui->lineEdit->text().toInt());
    query->bindValue(":ttn_date", ui->dateEdit->text());
    query->bindValue(":cust_id", ui->comboBox_2->currentText());
    query->bindValue(":operation_id", ui->comboBox->currentText());
    query->bindValue(":by_whom", ui->lineEdit_2->text());
    query->bindValue(":sum", sum);
    query->bindValue(":umova", ui->lineEdit_3->text());
    query->exec();

    qDebug() <<query->lastError();
    close();
}
