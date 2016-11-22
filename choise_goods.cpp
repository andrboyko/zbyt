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
    query->prepare("INSERT INTO ttn_items(ttn_id, prod_id, ttn_item_quantity, ttn_item_price)VALUES(:ttn_id, :prod_id, :ttn_item_quantity, :ttn_item_price);");
    query->bindValue(":ttn_id", ttn_id);
    query->bindValue(":prod_id", prod_id);
    query->bindValue(":ttn_item_quantity", ui->spinBox->value());
    query->bindValue(":ttn_item_price", ui->doubleSpinBox->value());
    query->exec();
    emit buttonclicked();
    close();
}

void choise_goods::recieveData(int r_ttn_id)
{
    ttn_id=r_ttn_id;
}
