#include "choise_goods.h"
#include "ui_choise_goods.h"


choise_goods::choise_goods(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::choise_goods)
{

     ui->setupUi(this);

     //Горячая клавиша Отмена=Esc

     keyCancel = new QShortcut(this);
     keyCancel->setKey(Qt::Key_Escape);
     connect(keyCancel, SIGNAL(activated()), this, SLOT(close()));

    model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM prod_group;");
    ui->listView->setModel(model);
    ui->listView->setModelColumn(1);
}

choise_goods::~choise_goods()
{
    delete ui;
}

void choise_goods::on_listView_clicked(const QModelIndex &index)
{
    temp_nomlVc = ui->listView->model()->data(ui->listView->model()->index(index.row(),0)).toInt();

    model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM products WHERE prod_group_id = " + QString::number(temp_nomlVc) + ";");

    ui->listView_2->setModel(model);
    ui->listView_2->setModelColumn(2);
}

void choise_goods::on_pushButton_2_clicked()
{
    close();
}

void choise_goods::on_listView_2_clicked(const QModelIndex &index)
{
    prod_id = ui->listView_2->model()->data(ui->listView_2->model()->index(index.row(),0)).toInt();

    //вивід назва товару
    query = new QSqlQuery();
    query->prepare("SELECT prod_name FROM products WHERE prod_id = :prod_id;");
    query->bindValue(":prod_id", prod_id);
    query->exec();
    while (query->next())
    {
        ui->label_5->setText(query->value(0).toString());
    }

    // Вивід в поле залишок
    query = new QSqlQuery();
    query->prepare("SELECT prod_quantity FROM products WHERE prod_id =  :prod_id;");
    query->bindValue(":prod_id", prod_id);
    query->exec();
    while (query->next())
    {
        ui->lineEdit->setText(query->value(0).toString());
    }

    // Вивід в поле ціна
    query = new QSqlQuery();
    query->prepare("SELECT prod_price_retail FROM products WHERE prod_id =  :prod_id;");
    query->bindValue(":prod_id", prod_id);
    query->exec();
    while (query->next())
    {
        ui->doubleSpinBox->setValue(query->value(0).toDouble());
    }
}

    //вивід суми
void choise_goods::on_spinBox_valueChanged(int arg1)
{
    ui->lineEdit_2->setText(QString::number(arg1*  ui->doubleSpinBox->value()));
}

void choise_goods::on_doubleSpinBox_valueChanged(double arg1)
{
    ui->lineEdit_2->setText(QString::number(arg1*  ui->spinBox->value()));
}

void choise_goods::on_pushButton_clicked()
{
    query = new QSqlQuery();
    query2 = new QSqlQuery();
    queryUpdate = new QSqlQuery();

    query->exec("SELECT * FROM ttn_items WHERE ttn_id = "+QString::number(ttn_id)+" and prod_id = "+QString::number(prod_id)+";");
    query->next();

    if(!query->isValid()){

        query->prepare("INSERT INTO ttn_items(ttn_id, prod_id, ttn_item_quantity, ttn_item_price)VALUES(:ttn_id, :prod_id, :ttn_item_quantity, :ttn_item_price);");
        query->bindValue(":ttn_id", ttn_id);
        query->bindValue(":prod_id", prod_id);
        query->bindValue(":ttn_item_quantity", ui->spinBox->value());
        query->bindValue(":ttn_item_price", ui->doubleSpinBox->value());
        query->exec();
        emit update_table();

        if (edit==true){
            //подсчет количества продукции
            query->prepare("SELECT ttn_item_quantity from ttn_items WHERE ttn_id=:ttn_id and prod_id =:prod_id");
            query->bindValue(":ttn_id", ttn_id);
            query->bindValue(":prod_id", prod_id);
            query->exec();

            while (query->next())
            {
                query2->exec("SELECT prod_quantity FROM products WHERE prod_id=" +QString::number(prod_id)+ ";");
                query2->next();

                int x;
                if(comingBool==false){
                x=(query2->value(0).toInt())-(query->value(0).toInt());
                }else{
                x=(query2->value(0).toInt())+(query->value(0).toInt());
                }
                queryUpdate->prepare("UPDATE products SET prod_quantity=:prod_quantity  WHERE prod_id = :prod_id;");
                queryUpdate->bindValue(":prod_quantity", QString::number(x) );
                queryUpdate->bindValue(":prod_id", prod_id);
                queryUpdate->exec();
            }
        }
        close();
    }else{

        QMessageBox msgBox;
        msgBox.setWindowTitle("Увага");
        msgBox.setText("Цей товар уже є у списку, сумувати кількість");
        msgBox.setStandardButtons(QMessageBox::Yes);
        msgBox.addButton(QMessageBox::No);
        msgBox.setDefaultButton(QMessageBox::No);
        msgBox.setButtonText(QMessageBox::Yes, "Так");
        msgBox.setButtonText(QMessageBox::No, "Ні");
        if(msgBox.exec() == QMessageBox::Yes)
        {
            query->exec("SELECT ttn_item_quantity FROM ttn_items WHERE ttn_id="+QString::number(ttn_id)+" AND prod_id = "+QString::number(prod_id)+";");
            query->next();
            ttn_item_quantity=query->value(0).toInt();

            query->prepare("UPDATE ttn_items SET ttn_item_quantity =:ttn_item_quantity WHERE ttn_id=:ttn_id AND prod_id=:prod_id ");
            query->bindValue(":ttn_id", ttn_id);
            query->bindValue(":prod_id", prod_id);
            query->bindValue(":ttn_item_quantity", ui->spinBox->value()+ttn_item_quantity);
            query->exec();

            if(edit==true){
                int x;
                if(comingBool==false){
                x=(ui->lineEdit->text().toInt())-(ui->spinBox->value());
                }else{
                x=(ui->lineEdit->text().toInt())+(ui->spinBox->value());
                }
                queryUpdate->prepare("UPDATE products SET prod_quantity=:prod_quantity  WHERE prod_id = :prod_id;");
                queryUpdate->bindValue(":prod_quantity", QString::number(x) );
                queryUpdate->bindValue(":prod_id", prod_id);
                queryUpdate->exec();
            }

            emit update_table();

            close();
        }
    }
}

void choise_goods::recieveData(int i, bool e)
{
    ttn_id=i;
    edit = e;
}

void choise_goods::recieveComingOperation(bool o)
{
    comingBool=o;
}
