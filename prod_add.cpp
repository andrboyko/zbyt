#include "prod_add.h"
#include "ui_prod_add.h"

prod_add::prod_add(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::prod_add)
{
    ui->setupUi(this);

    //Горячая клавиша Отмена=Esc
    keyCancel = new QShortcut(this);
    keyCancel->setKey(Qt::Key_Escape);
    connect(keyCancel, SIGNAL(activated()), this, SLOT(close()));



    model = new QSqlQueryModel(this);
    model->setQuery("select units_name FROM units;");
    ui->comboBox->setModel(model);
    ui->comboBox->setModelColumn(0);
    ui->comboBox->setMaxVisibleItems(ui->comboBox->count());

    model = new QSqlQueryModel(this);
    model->setQuery("select type_name FROM prod_group;");
    ui->comboBox_2->setModel(model);
    ui->comboBox_2->setModelColumn(0);
    ui->comboBox_2->setMaxVisibleItems(ui->comboBox_2->count());

}

prod_add::~prod_add()
{
    delete ui;
}
// Добавление нового товара в справочник
void prod_add::on_pushButton_clicked()
{

    if (ui->lineEdit->text().count()>2 && ui->lineEdit_2->text().count()>2 )
    {
        query = new QSqlQuery();
        query->prepare("INSERT INTO products(cipher, prod_name, units_id, prod_price_retail, prod_price_barter,"
                       "prod_price_wholesale, prod_quantity_residual, prod_date, prod_group_id)"
                       "VALUES"
                       "(:cipher, :prod_name, (select units_id from units where units_name=:units_id), :prod_price_retail, :prod_price_barter,"
                       ":prod_price_wholesale, :prod_quantity_residual, :prod_date, (select prod_group_id from prod_group where type_name=:prod_group));");
        query->bindValue(":cipher", ui->lineEdit->text());
        query->bindValue(":prod_name", ui->lineEdit_2->text());
        query->bindValue(":units_id", ui->comboBox->currentText());
        query->bindValue(":prod_price_retail", ui->doubleSpinBox->value());
        query->bindValue(":prod_price_barter", ui->doubleSpinBox_2->value());
        query->bindValue(":prod_price_wholesale", ui->doubleSpinBox_3->value());
        query->bindValue(":prod_date", ui->dateEdit->text());
        query->bindValue(":prod_group", ui->comboBox_2->currentText() );
        query->exec();
        emit buttonclicked();
        close();

    }else
        QMessageBox::information(this, "Увага", "Не заповнені всі поля ");


}
