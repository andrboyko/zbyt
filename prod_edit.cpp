#include "prod_edit.h"
#include "ui_prod_edit.h"

prod_edit::prod_edit(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::prod_edit)
{
    ui->setupUi(this);

    //Горячая клавиша Отмена=Esc
    keyCancel = new QShortcut(this);
    keyCancel->setKey(Qt::Key_Escape);
    connect(keyCancel, SIGNAL(activated()), this, SLOT(close()));
}

prod_edit::~prod_edit()
{
    delete ui;
}
// кнопка обновления цены товара из справочника
void prod_edit::on_pushButton_clicked()
{

    query = new QSqlQuery();
    query->prepare("UPDATE products "
                   "SET prod_price_retail = :prod_price_retail, prod_price_barter = :prod_price_barter, "
                   "prod_price_wholesale = :prod_price_wholesale WHERE prod_id=:prod_id;");
    query->bindValue(":prod_price_retail", ui->doubleSpinBox->value());
    query->bindValue(":prod_price_barter", ui->doubleSpinBox_2->value());
    query->bindValue(":prod_price_wholesale", ui->doubleSpinBox_3->value());
    query->bindValue(":prod_id", index_prod);
    query->exec();
    emit buttonclicked();
    close();

}

// функция получения данных
void prod_edit::recieveData(int i)
{
    index_prod = i;

    query = new QSqlQuery();
    query->exec("SELECT prod_price_retail, prod_price_barter, prod_price_wholesale, prod_name FROM products WHERE prod_id  = '"+QString::number(index_prod) +"';");
    while (query->next())
    {

        ui->doubleSpinBox->setValue(query->value(0).toDouble());
        ui->doubleSpinBox_2->setValue(query->value(1).toDouble());
        ui->doubleSpinBox_3->setValue(query->value(2).toDouble());
        setWindowTitle(query->value(3).toString());
    }

}
