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

    query = new QSqlQuery();
    query->prepare("SELECT sum(ttn_item_quantity*ttn_item_price) FROM ttn_items WHERE ttn_id="+ui->lineEdit->text()+";");
    query->exec();

    while (query->next())
    {
        sum=query->value(0).toDouble();
        ui->label_7->setText("Сума "+QString::number(sum)+" грн.");
    }

}
// Удалить найменование
void prod_coming::on_pushButton_3_clicked()
{
    if (edit==true){
        query = new QSqlQuery();
        query2 = new QSqlQuery();
        queryUpdate = new QSqlQuery();

        //подсчет количества продукции
        query->prepare("SELECT ttn_item_quantity from ttn_items WHERE ttn_id=:ttn_id and prod_id =:prod_id");
        query->bindValue(":ttn_id", ui->lineEdit->text());
        query->bindValue(":prod_id", index_prod);
        query->exec();

        while (query->next())
        {
            query2->exec("SELECT prod_quantity FROM products WHERE prod_id=" +QString::number(index_prod)+ ";");
            query2->next();

            int x;
            x=(query2->value(0).toInt())-(query->value(0).toInt());
            queryUpdate->prepare("UPDATE products SET prod_quantity=:prod_quantity  WHERE prod_id = :prod_id;");
            queryUpdate->bindValue(":prod_quantity", QString::number(x) );
            queryUpdate->bindValue(":prod_id", index_prod);
            queryUpdate->exec();
        }
    }


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
        connect(this, SIGNAL(sendData(int, bool)), goods, SLOT(recieveData(int, bool)));
        connect(goods, SIGNAL(update_table()), this, SLOT(refreshTable_goods()));
        connect(this, SIGNAL(sendComingOperation(bool)), goods, SLOT(recieveComingOperation(bool)));
        goods->show();
        goods->activateWindow();
        emit sendData(ui->lineEdit->text().toInt(), edit);
        emit sendComingOperation(true);
}

void prod_coming::on_pushButton_4_clicked()
{
    query = new QSqlQuery();
    query2 = new QSqlQuery();
    queryUpdate = new QSqlQuery;

    if(edit==false){
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

            int plus;
            plus=(query2->value(0).toInt())+(query->value(0).toInt());
            queryUpdate->prepare("UPDATE products SET prod_quantity=:prod_quantity  WHERE prod_id = :prod_id;");
            queryUpdate->bindValue(":prod_quantity", QString::number(plus) );
            queryUpdate->bindValue(":prod_id", query->value(1).toString() );
            queryUpdate->exec();
        }
    }else{
        query->prepare("UPDATE ttn SET ttn_date = :ttn_date"
                       " WHERE ttn_id=:ttn_id;");
        query->bindValue(":ttn_id", ui->lineEdit->text());
        query->bindValue(":ttn_date", ui->dateEdit->text());
        query->bindValue(":sum", sum);
        query->exec();
        emit update_table();
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

void prod_coming::receiveData(int i, bool e)
{
    index_table = i;
    edit = e;

    if(edit==true){
        ui->pushButton_5->hide();
        ui->pushButton_4->setFixedSize(260, 30);
        ui->pushButton_4->setText("Зберегти");
    }else{
        ui->pushButton_5->show();
        ui->pushButton_4->setFixedSize(125, 30);
        ui->pushButton_4->setText("ОК");
    }

    if(edit==false){
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
    }else{
        ui->lineEdit->setText(QString::number(index_table));
        query = new QSqlQuery();
        query->exec("SELECT ttn_date, cust_id, operation_id, sum FROM ttn WHERE ttn_id="+QString::number(index_table)+";");
        while (query->next())
        {
            ui->lineEdit->setText(QString::number(index_table));
            ui->dateEdit->setDate(query->value(0).toDate());
        }
    }
    refreshTable_goods();
}

void prod_coming::on_pushButton_6_clicked()
{

}
