#include "create_ttn.h"
#include "ui_create_ttn.h"


create_ttn::create_ttn(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::create_ttn)
{
    ui->setupUi(this);

    //Горячая клавиша Отмена=Esc
    keyCancel = new QShortcut(this);
    keyCancel->setKey(Qt::Key_Escape);
    connect(keyCancel, SIGNAL(activated()), this, SLOT(close()));



    //регулярное выражение для LineEdit ввода № накладной
    QRegExp exp("[0-9]{0,6}");
    ui->lineEdit->setValidator(new QRegExpValidator(exp, this));

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

        ui->comboBox->setCurrentIndex(-1);
        ui->comboBox_2->setCurrentIndex(-1);
        setFixedHeight(135);
        ui->groupBox->setHidden(true);
        ui->groupBox_2->setHidden(true);
}

create_ttn::~create_ttn()
{
     delete ui;
}

void create_ttn::on_pushButton_clicked()
{
    goods = new choise_goods;
    goods->setWindowFlags(Qt::Tool);
    connect(this, SIGNAL(sendData(int)), goods, SLOT(recieveData(int)));
    connect(goods, SIGNAL(buttonclicked()), this, SLOT(refreshTable_goods()));
    goods->show();
    goods->activateWindow();
    emit sendData(ui->lineEdit->text().toInt());
}


// обновление таблицы товаров
void create_ttn::refreshTable_goods()
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
void create_ttn::on_pushButton_3_clicked()
{
    query = new QSqlQuery();
    query->prepare("DELETE FROM ttn_items WHERE ttn_id = :ttn_id AND prod_id = :prod_id;");
    query->bindValue(":ttn_id", ui->lineEdit->text());
    query->bindValue(":prod_id", index_prod);
    query->exec();
    refreshTable_goods();
}


void create_ttn::on_tableView_clicked(const QModelIndex &index)
{
    index_prod = ui->tableView->model()->data(ui->tableView->model()->index(index.row(),0)).toString();
    qDebug() << index_prod;
}


//Запись накладной
void create_ttn::on_pushButton_4_clicked()
{
    query = new QSqlQuery();
    query2 = new QSqlQuery();

    query->prepare("INSERT INTO ttn(ttn_id, ttn_date, cust_id, operation_id, by_whom, sum, umova)VALUES(:ttn_id, :ttn_date,(select cust_id from custumers where cust_name=:cust_id), (SELECT operation_id FROM operations WHERE operation_name =:operation_id), :by_whom, :sum, :umova);");
    query->bindValue(":ttn_id", ui->lineEdit->text().toInt());
    query->bindValue(":ttn_date", ui->dateEdit->text());
    if (ui->comboBox_2->currentIndex() ==-1){
        query->bindValue(":cust_id", "Склад");
    }else{
        query->bindValue(":cust_id", ui->comboBox_2->currentText());

    }

    query->bindValue(":operation_id", ui->comboBox->currentText());
    query->bindValue(":by_whom", ui->lineEdit_2->text());
    query->bindValue(":sum", sum);
    query->bindValue(":umova", ui->lineEdit_3->text());
    query->exec();
    PushB4();


//    query->prepare("SELECT prod_quantity FROM products WHERE prod_id=:prod_id");
//    query->bindValue(":prod_id", ui->lineEdit->text().toInt());
//    query->exec();


    query->prepare("SELECT ttn_item_quantity, prod_id from ttn_items WHERE ttn_id=:ttn_id");
    query->bindValue(":ttn_id", ui->lineEdit->text().toInt());
    query->exec();
    while (query->next())
    {
        query2->exec("SELECT prod_quantity FROM products WHERE prod_id=" +query->value(1).toString()+ ";");
        query2->next();

        qDebug() << "prod_quantity = "+query2->value(0).toString();

        qDebug() << "ttn_item_quantity = "+query->value(0).toString();
        qDebug() << "prod_id = "+query->value(1).toString();
    }



    if (ui->comboBox->currentIndex()==1){





    }else{

    }

    close();
}

//кнопка отмена
void create_ttn::on_pushButton_5_clicked()
{
    query = new QSqlQuery();
    query->prepare("DELETE FROM ttn_items WHERE ttn_id = :ttn_id");
    query->bindValue(":ttn_id", ui->lineEdit->text().toInt());
    query->exec();
    close();
}




void create_ttn::on_comboBox_currentIndexChanged(int index)
{
    if (ui->comboBox->currentIndex()==0){
        ui->groupBox->setHidden(true);
        ui->groupBox_2->setHidden(false);
        ui->groupBox_2->move(0,130);
        setFixedHeight(630);
        ui->pushButton_4->move(340,580);
        ui->pushButton_5->move(480,580);
        moveToCenter();

    }else{
        if (ui->comboBox->currentIndex()!=0){
           ui->groupBox_2->move(0,240);
            ui->groupBox->setHidden(false);
            ui->groupBox_2->setHidden(false);
            setFixedHeight(735);

          ui->pushButton_4->move(340,685);
           ui->pushButton_5->move(480,685);
        }
    }
}

void create_ttn::moveToCenter()
{
        QDesktopWidget desktop;
        QRect rect = desktop.availableGeometry(desktop.primaryScreen()); // прямоугольник с размерами экрана
        QPoint center = rect.center(); //координаты центра экрана
        center.setX(center.x() - (this->width()/2));  // учитываем половину ширины окна
        center.setY(center.y() - (this->height()/2));  // .. половину высоты
        move(center);
}
