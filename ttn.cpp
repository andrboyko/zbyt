#include "ttn.h"
#include "ui_ttn.h"


ttn::ttn(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ttn)
{
    ui->setupUi(this);



    //Горячая клавиша Отмена=Esc
    keyCancel = new QShortcut(this);
    keyCancel->setKey(Qt::Key_Escape);
    connect(keyCancel, SIGNAL(activated()), this, SLOT(close()));

        ui->dateEdit->setDate(QDate::currentDate());
        model = new QSqlQueryModel(this);
        model->setQuery("select operation_id, operation_name from operations WHERE NOT(operation_id=1);");
        ui->comboBox->setModel(model);
        ui->comboBox->setModelColumn(1);
        ui->comboBox->setCurrentIndex(-1);
        ui->comboBox->setMaxVisibleItems(ui->comboBox->maxCount());

        model = new QSqlQueryModel(this);
        model->setQuery("select cust_name, cust_id from custumers WHERE NOT(cust_id=0);");
        ui->comboBox_2->setModel(model);
        ui->comboBox_2->setModelColumn(0);
        ui->comboBox_2->setCurrentIndex(-1);

}

ttn::~ttn()
{
   delete ui;
}
// добавить товары
void ttn::on_pushButton_clicked()
{
    goods = new choise_goods;
    goods->setWindowFlags(Qt::Tool);
    connect(this, SIGNAL(sendData(int, bool)), goods, SLOT(recieveData(int, bool)));
    connect(goods, SIGNAL(update_table()), this, SLOT(refreshTable_goods()));
    connect(this, SIGNAL(sendComingOperation(bool)), goods, SLOT(recieveComingOperation(bool)));
    goods->show();
    goods->activateWindow();

    emit sendComingOperation(false);
    if (edit==true){
    emit sendData(ui->lineEdit->text().toInt(), true);
    }else {
    emit sendData(ui->lineEdit->text().toInt(), false);
    }
}


// обновление таблицы товаров
void ttn::refreshTable_goods()
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


//видалити товар
void ttn::on_pushButton_3_clicked()
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
            x=(query2->value(0).toInt())+(query->value(0).toInt());
            queryUpdate->prepare("UPDATE products SET prod_quantity=:prod_quantity  WHERE prod_id = :prod_id;");
            queryUpdate->bindValue(":prod_quantity", QString::number(x) );
            queryUpdate->bindValue(":prod_id", index_prod);
            queryUpdate->exec();
        }
    }


    query = new QSqlQuery();
    query->prepare("DELETE FROM ttn_items WHERE ttn_id = :ttn_id AND prod_id = :prod_id;");
    query->bindValue(":ttn_id", ui->lineEdit->text());
    query->bindValue(":prod_id", QString::number(index_prod));
    query->exec();
    refreshTable_goods();
}


void ttn::on_tableView_clicked(const QModelIndex &index)
{
    index_prod = ui->tableView->model()->data(ui->tableView->model()->index(index.row(),0)).toInt();
}


//Запись накладной
void ttn::on_pushButton_4_clicked()
{
    if((ui->comboBox_2->currentIndex()!=-1)&&(ui->comboBox->currentIndex()!=-1)) {

        query = new QSqlQuery();
        query2 = new QSqlQuery();
        queryUpdate = new QSqlQuery;

        if(edit==false){


            query->prepare("INSERT INTO ttn(ttn_date, cust_id, operation_id, by_whom, sum, umova)VALUES(:ttn_date, :cust_id, :operation_id, :by_whom, :sum, :umova);");
            query->bindValue(":ttn_date", ui->dateEdit->text());
            query->bindValue(":cust_id", ui->comboBox_2->model()->data(ui->comboBox_2->model()->index(cust_id,1)).toString());
            query->bindValue(":operation_id", ui->comboBox->model()->data(ui->comboBox->model()->index(operation_id,0)).toString());
            query->bindValue(":by_whom", ui->lineEdit_2->text());
            query->bindValue(":sum", sum);
            query->bindValue(":umova", ui->lineEdit_3->text());
            query->exec();
            emit update_table();


            query->prepare("SELECT ttn_item_quantity, prod_id from ttn_items WHERE ttn_id=:ttn_id");
            query->bindValue(":ttn_id", ui->lineEdit->text().toInt());
            query->exec();
            while (query->next())
            {
                query2->exec("SELECT prod_quantity FROM products WHERE prod_id=" +query->value(1).toString()+ ";");
                query2->next();

                int x;
                x=(query2->value(0).toInt())-(query->value(0).toInt());
                queryUpdate->prepare("UPDATE products SET prod_quantity=:prod_quantity  WHERE prod_id = :prod_id;");
                queryUpdate->bindValue(":prod_quantity", QString::number(x) );
                queryUpdate->bindValue(":prod_id", query->value(1).toString() );
                queryUpdate->exec();
            }
        }else{

            query->prepare("UPDATE ttn SET ttn_date = :ttn_date, cust_id = :cust_id, operation_id = :operation_id,"
                           " by_whom = :by_whom, sum = :sum, umova = :umova WHERE ttn_id=:ttn_id;");
            query->bindValue(":ttn_id", ui->lineEdit->text());
            query->bindValue(":ttn_date", ui->dateEdit->text());
            query->bindValue(":cust_id", ui->comboBox_2->model()->data(ui->comboBox_2->model()->index(cust_id,1)).toString());
            query->bindValue(":operation_id", ui->comboBox->model()->data(ui->comboBox->model()->index(operation_id,0)).toString());
            query->bindValue(":by_whom", ui->lineEdit_2->text());
            query->bindValue(":sum", sum);
            query->bindValue(":umova", ui->lineEdit_3->text());
            query->exec();
            emit update_table();

        }

        close();
    }else{
        QMessageBox::information(this, "Увага", "Не заповнені всі поля ");
    }

}

//кнопка отмена
void ttn::on_pushButton_5_clicked()
{
    query = new QSqlQuery();
    query->exec("DELETE FROM ttn_items WHERE ttn_id = " +ui->lineEdit->text()+ ";");
    query->exec("DELETE FROM ttn WHERE ttn_id = " +ui->lineEdit->text()+ ";");
    close();
}

void ttn::on_comboBox_2_currentIndexChanged(int index)
{
    cust_id=index;
}


void ttn::on_comboBox_currentIndexChanged(int index)
{
    operation_id=index;
}

void ttn::receiveData(int i, bool e)
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
        query->exec("SELECT ttn_date, cust_id, operation_id, by_whom, sum, umova  FROM ttn WHERE ttn_id="+QString::number(index_table)+";");
        while (query->next())
        {
            ui->lineEdit->setText(QString::number(index_table));
            ui->lineEdit_3->setText(query->value(5).toString());
            ui->lineEdit_2->setText(query->value(3).toString());
            ui->dateEdit->setDate(query->value(0).toDate());
        }
        query->exec("SELECT operations.operation_name FROM ttn, operations WHERE ttn.ttn_id="+QString::number(index_table)+" AND operations.operation_id = ttn.operation_id;");
        while (query->next())
        {
            ui->comboBox->setCurrentText(query->value(0).toString());
        }

        query->exec("SELECT custumers.cust_name FROM ttn, custumers WHERE ttn.ttn_id="+QString::number(index_table)+" AND custumers.cust_id = ttn.cust_id;");
        while (query->next())
        {
            ui->comboBox_2->setCurrentText(query->value(0).toString());
        }
    }
    refreshTable_goods();
}

// кнопка количество
void ttn::on_pushButton_6_clicked()
{
    editQuantity = new QWidget;
    editQuantity->setWindowFlags(Qt::Tool);
    verticalLayout = new QVBoxLayout;
    pushButton = new QPushButton;
    spinBox = new QSpinBox;
    query = new QSqlQuery;
    spinBox->setMinimum(1);


    query->exec("SELECT prod_quantity FROM products WHERE prod_id = "+QString::number(index_prod)+";");
    query->next();
    prod_quantity=query->value(0).toInt();

    query->exec("SELECT ttn_item_quantity FROM ttn_items WHERE ttn_id= " +ui->lineEdit->text()+ " AND prod_id= " +QString::number(index_prod)+ ";");
    while (query->next()){
        ttn_item_quantity=query->value(0).toInt();
    }
    spinBox->setValue(ttn_item_quantity);
    spinBox->setMaximum(ttn_item_quantity+prod_quantity);
    QFont timesFont("Times New Roman", 12);
    editQuantity->setFont(timesFont);
    editQuantity->setWindowTitle("Кількість");
    editQuantity->setWindowModality(Qt::ApplicationModal);

    pushButton->setText("Зберегти");

    connect(pushButton, SIGNAL (clicked()), this, SLOT (updateprice()));


    verticalLayout->addWidget(spinBox);
    verticalLayout->addWidget(pushButton);
    editQuantity->setLayout(verticalLayout);
    editQuantity->show();
    editQuantity->activateWindow();

    QDesktopWidget desktop;
    QRect rect = desktop.availableGeometry(desktop.primaryScreen()); // прямоугольник с размерами экрана
    QPoint center = rect.center(); //координаты центра экрана
    center.setX(center.x() - (editQuantity->width()/2));  // учитываем половину ширины окна
    center.setY(center.y() - (editQuantity->height()/2));  // .. половину высоты
    editQuantity->move(center);
}
//функция измимения количества
void ttn::updateprice()
{
    query = new QSqlQuery;
    query2 = new QSqlQuery;
    queryUpdate = new QSqlQuery;

    query->exec("UPDATE ttn_items SET ttn_item_quantity ="+QString::number(spinBox->value())+" WHERE ttn_id= " +ui->lineEdit->text()+ " AND prod_id ="+QString::number(index_prod)+";");
    editQuantity->close();

    if(edit==true){
        if(spinBox->value()>ttn_item_quantity){
            int x;
                x=(prod_quantity)-(spinBox->value()-ttn_item_quantity);
                queryUpdate->prepare("UPDATE products SET prod_quantity=:prod_quantity  WHERE prod_id = :prod_id;");
                queryUpdate->bindValue(":prod_quantity", QString::number(x) );
                queryUpdate->bindValue(":prod_id", index_prod);
                queryUpdate->exec();
        }else if(spinBox->value()<ttn_item_quantity){
            int x;
            x=(prod_quantity)+(ttn_item_quantity-(spinBox->value()));
            queryUpdate->prepare("UPDATE products SET prod_quantity=:prod_quantity  WHERE prod_id = :prod_id;");
            queryUpdate->bindValue(":prod_quantity", QString::number(x) );
            queryUpdate->bindValue(":prod_id", index_prod);
            queryUpdate->exec();
        }else{

        }
    }
    refreshTable_goods();
}

void ttn::on_tableView_doubleClicked()
{
    ui->pushButton_6->clicked();
}
