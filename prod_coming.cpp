#include "prod_coming.h"
#include "ui_prod_coming.h"

prod_coming::prod_coming(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::prod_coming)
{
    ui->setupUi(this);

    //Горячая клавиша Отмена=Esc
    keyCancel = new QShortcut(this);
    keyCancel->setKey(Qt::Key_Escape);
    connect(keyCancel, SIGNAL(activated()), this, SLOT(close()));

    ui->dateEdit->setDate(QDate::currentDate());
    model = new QSqlQueryModel(this);
    model->setQuery("select operation_id, operation_name from operations WHERE operation_id=1;");
    ui->comboBox->setModel(model);
    ui->comboBox->setModelColumn(1);

    //ttn_id
    query = new QSqlQuery();
    query->exec("SELECT ttn_id From ttn;");
    query->last();
    if (query->value(0).toString()==NULL){
        query2 = new QSqlQuery();
        query2->exec("ALTER TABLE ttn AUTO_INCREMENT=100200");
        ui->lineEdit->setText("100200");
    }else{
    ui->lineEdit->setText(QString::number(query->value(0).toInt()+1));
    }

}

prod_coming::~prod_coming()
{
    delete ui;
}
// Обновить таблицу найменований
void prod_coming::refreshTable_goods()
{
    model = new QSqlQueryModel;
    model->setQuery("SELECT products.prod_id, cipher, prod_name, ttn_item_quantity, ttn_item_price, ttn_item_quantity*ttn_item_price FROM products, ttn_items WHERE ttn_items.prod_id = products.prod_id AND ttn_id="+ui->lineEdit->text()+";");
    ui->tableView->setModel(model);
    model->setHeaderData(1,Qt::Horizontal, "Шифр");
    model->setHeaderData(2,Qt::Horizontal, "Найменування");
    model->setHeaderData(3,Qt::Horizontal, "Кількість");
    model->setHeaderData(4,Qt::Horizontal, "Ціна, грн.");
    model->setHeaderData(5,Qt::Horizontal, "Сума, грн.");
    ui->tableView->setColumnHidden(0,1);
    ui->tableView->setColumnWidth(1,95);
    ui->tableView->setColumnWidth(2,300);
    ui->tableView->setColumnWidth(3,65);
    ui->tableView->setColumnWidth(4,65);
    ui->tableView->setColumnWidth(5,75);
}
// Удалить найменование
void prod_coming::on_pushButton_3_clicked()
{
    query = new QSqlQuery();
    query->prepare("DELETE FROM ttn_items WHERE ttn_id = :ttn_id AND prod_id = :prod_id;");
    query->bindValue(":ttn_id", ui->lineEdit->text());
    query->bindValue(":prod_id", index_prod);
    query->exec();
    refreshTable_goods();
}

void prod_coming::on_tableView_clicked(const QModelIndex &index)
{
    index_prod = ui->tableView->model()->data(ui->tableView->model()->index(index.row(),0)).toInt();
}

void prod_coming::on_pushButton_clicked()
{
        goods = new choise_goods;
        goods->setWindowFlags(Qt::Tool);
        connect(this, SIGNAL(sendData(int)), goods, SLOT(recieveData(int)));
        connect(goods, SIGNAL(update_table()), this, SLOT(refreshTable_goods()));
        goods->show();
        goods->activateWindow();
        emit sendData(ui->lineEdit->text().toInt());
}

void prod_coming::on_pushButton_4_clicked()
{
    query = new QSqlQuery();
    query2 = new QSqlQuery();
    queryUpdate = new QSqlQuery;

    query->prepare("INSERT INTO ttn(ttn_date, cust_id, operation_id, sum)VALUES(:ttn_date, 0, 1, (SELECT sum(ttn_item_quantity*ttn_item_price) FROM zbyt.ttn_items WHERE ttn_id = :ttn_id));");
    query->bindValue(":ttn_id", ui->lineEdit->text());
    query->bindValue(":ttn_date", ui->dateEdit->text());
    query->exec();
    emit update_table();



    //количество продукции
        query->prepare("SELECT ttn_item_quantity, prod_id from ttn_items WHERE ttn_id=:ttn_id");
        query->bindValue(":ttn_id", ui->lineEdit->text().toInt());
        query->exec();
        while (query->next())
        {
            query2->exec("SELECT prod_quantity FROM products WHERE prod_id=" +query->value(1).toString()+ ";");
            query2->next();
            //        qDebug() << "prod_quantity = "+query2->value(0).toString();
            //        qDebug() << "ttn_item_quantity = "+query->value(0).toString();
            //        qDebug() << "prod_id = "+query->value(1).toString();
            int plus;
            plus=(query2->value(0).toInt())+(query->value(0).toInt());
            queryUpdate->prepare("UPDATE products SET prod_quantity=:prod_quantity  WHERE prod_id = :prod_id;");
            queryUpdate->bindValue(":prod_quantity", QString::number(plus) );
            queryUpdate->bindValue(":prod_id", query->value(1).toString() );
            queryUpdate->exec();
            //            qDebug() << "prod_quntity + ttn_item_quantity = " + QString::number(plus);
        }
    close();
}

void prod_coming::on_pushButton_5_clicked()
{
    query = new QSqlQuery();
    query->prepare("DELETE FROM ttn_items WHERE ttn_id = :ttn_id");
    query->bindValue(":ttn_id", ui->lineEdit->text().toInt());
    query->exec();
    close();
}
