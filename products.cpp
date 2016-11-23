#include "products.h"
#include "ui_products.h"

products::products(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::products)
{
    ui->setupUi(this);

    //Горячая клавиша Отмена=Esc
    keyCancel = new QShortcut(this);
    keyCancel->setKey(Qt::Key_Escape);
    connect(keyCancel, SIGNAL(activated()), this, SLOT(close()));

    model = new QSqlQueryModel(this);
    model->setQuery("select units_name, units_id FROM units;");
    ui->comboBox->setModel(model);
    ui->comboBox->setModelColumn(0);
    ui->comboBox->setMaxVisibleItems(ui->comboBox->count());

    model = new QSqlQueryModel(this);
    model->setQuery("select type_name, prod_group_id FROM prod_group;");
    ui->comboBox_2->setModel(model);
    ui->comboBox_2->setModelColumn(0);
}

products::~products()
{
    delete ui;
}
// Добавление нового товара в справочник
void products::on_pushButton_clicked()
{
    if (edit==false){
    if (ui->lineEdit->text().count()>2 && ui->lineEdit_2->text().count()>2 ){
        query = new QSqlQuery();
        query->prepare("INSERT INTO products(cipher, prod_name, units_id, prod_price_retail, prod_price_barter,"
                       "prod_price_wholesale, prod_quantity_residual, prod_date, prod_group_id)"
                       "VALUES"
                       "(:cipher, :prod_name, :units_id, :prod_price_retail, :prod_price_barter,"
                       ":prod_price_wholesale, :prod_quantity_residual, :prod_date, :prod_group_id);");
        query->bindValue(":cipher", ui->lineEdit->text());
        query->bindValue(":prod_name", ui->lineEdit_2->text());
        query->bindValue(":units_id", ui->comboBox->model()->data(ui->comboBox->model()->index(units_id, 1)).toString());
        query->bindValue(":prod_price_retail", ui->doubleSpinBox->value());
        query->bindValue(":prod_price_barter", ui->doubleSpinBox_2->value());
        query->bindValue(":prod_price_wholesale", ui->doubleSpinBox_3->value());
        query->bindValue(":prod_date", ui->dateEdit->text());
        query->bindValue(":prod_group_id", ui->comboBox_2->model()->data(ui->comboBox_2->model()->index(prod_group_id, 1)).toString());
        query->exec();
        emit buttonclicked();
        close();

    }else
        QMessageBox::information(this, "Увага", "Не заповнені всі поля ");
    }else{

        if (ui->lineEdit->text().count()>2 && ui->lineEdit_2->text().count()>2 ){
        query = new QSqlQuery();
        query->prepare("UPDATE products "
                       "SET prod_name = :prod_name, units_id = :units_id, prod_price_retail = :prod_price_retail, prod_price_barter = :prod_price_barter, "
                       "prod_price_wholesale = :prod_price_wholesale, prod_date = :prod_date, prod_group_id = :prod_group_id WHERE prod_id=:prod_id;");
        query->bindValue(":cipher", ui->lineEdit->text());
        query->bindValue(":prod_name", ui->lineEdit_2->text());
        query->bindValue(":units_id", ui->comboBox->model()->data(ui->comboBox->model()->index(units_id, 1)).toString());
        query->bindValue(":prod_price_retail", ui->doubleSpinBox->value());
        query->bindValue(":prod_price_barter", ui->doubleSpinBox_2->value());
        query->bindValue(":prod_price_wholesale", ui->doubleSpinBox_3->value());
        query->bindValue(":prod_date", ui->dateEdit->text());
        query->bindValue(":prod_group_id", ui->comboBox_2->model()->data(ui->comboBox_2->model()->index(prod_group_id, 1)).toString());
        query->bindValue(":prod_id", index_table);
        query->exec();
        emit buttonclicked();
        close();

    }else
        QMessageBox::information(this, "Увага", "Не заповнені всі поля ");
    }
}

void products::receiveData(int i, bool e)
{
    index_table = i;
    edit=e;

    if(edit==true){
        ui->pushButton->setText("Редагувати");
        ui->lineEdit->setEnabled(false);
        setWindowTitle("Редагувати");
    }else{
            ui->pushButton->setText("Додати");
            ui->lineEdit->setEnabled(true);
            setWindowTitle("Додати");
    }

    if(edit==true){
    query = new QSqlQuery();
    query->exec("SELECT cipher, prod_name, prod_price_retail, prod_price_barter, prod_price_wholesale, prod_date FROM products WHERE prod_id  = '"+QString::number(index_table) +"';");
    while (query->next())
    {
       ui->lineEdit->setText(query->value(0).toString());
       ui->lineEdit_2->setText(query->value(1).toString());
       ui->doubleSpinBox->setValue(query->value(2).toInt());
       ui->doubleSpinBox_2->setValue(query->value(3).toDouble());
       ui->doubleSpinBox_3->setValue(query->value(4).toDouble());
       ui->dateEdit->setDate(query->value(5).toDate());
    }
    }
}

void products::on_comboBox_currentIndexChanged(int index)
{
    units_id=index;
}

void products::on_comboBox_2_currentIndexChanged(int index)
{
    prod_group_id=index;
}

