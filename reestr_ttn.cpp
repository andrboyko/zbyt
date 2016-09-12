#include "reestr_ttn.h"
#include "ui_reestr_ttn.h"

reestr_ttn::reestr_ttn(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::reestr_ttn)
{
    ui->setupUi(this);



//показать ТТН за текущий месяц
//ui->comboBox->setCurrentIndex(QDate::currentDate().month());
//ui->spinBox->setValue(QDate::currentDate().year());
    ui->comboBox->setCurrentIndex(0);
    ui->spinBox->setValue(2012);
findByDate();


viewttn = new View_ttn(this);
viewttn->setWindowFlags(Qt::Dialog);
connect(this, SIGNAL(sendData(int)), viewttn, SLOT(recieveData(int)));



}

reestr_ttn::~reestr_ttn()
{
    delete ui;
}




//функция выбоки ТТН по Дате
void reestr_ttn::findByDate(){

    QString sql;
    int month;
    int year;
    month=ui->comboBox->currentIndex();
    year=ui->spinBox->value();
    sql = "select ttn_id, operation_name,(SELECT sum(ttn_item_quantity*ttn_item_price)FROM ttn_items where ttn.ttn_id = ttn_items.ttn_id), cust_name, ttn_date FROM ttn, operations, custumers where ttn.operation_id = operations.operation_id and ttn.cust_id = custumers.cust_id and year(ttn_date) =" + QString::number(year) + " and month(ttn_date)=" +QString::number(month+1)+";""";
    model = new QSqlQueryModel;
    model->setQuery(sql);
    ui->tableView->setModel(model);
    model->setHeaderData(0,Qt::Horizontal, "№ ТТН");
    model->setHeaderData(1,Qt::Horizontal, "Вид");
    model->setHeaderData(2,Qt::Horizontal, "Сума, грн.");
    model->setHeaderData(3,Qt::Horizontal, "Замовник");
    model->setHeaderData(4,Qt::Horizontal, "Дата");
    ui->tableView->setColumnWidth(0,60);
    ui->tableView->setColumnWidth(1,185);
    ui->tableView->setColumnWidth(2,70);
    ui->tableView->setColumnWidth(3,300);
    ui->tableView->setColumnWidth(4,70);



}

void reestr_ttn::on_spinBox_valueChanged(int arg1)
{
    findByDate();
}
void reestr_ttn::on_comboBox_currentIndexChanged(int index)
{
    findByDate();
}

// функция выборки по номеру ТТН
void reestr_ttn::on_lineEdit_editingFinished()
{
    QString sql;
    sql = "select ttn_id, operation_name,(SELECT sum(ttn_item_quantity*ttn_item_price)FROM ttn_items where ttn.ttn_id = ttn_items.ttn_id), cust_name, ttn_date FROM ttn, operations, custumers where ttn.operation_id = operations.operation_id and ttn.cust_id = custumers.cust_id and ttn_id ="+ ui->lineEdit->text() +";";
    model = new QSqlQueryModel;
    model->setQuery(sql);
    ui->tableView->setModel(model);
    model->setHeaderData(0,Qt::Horizontal, "№ ТТН");
    model->setHeaderData(1,Qt::Horizontal, "Вид");
    model->setHeaderData(2,Qt::Horizontal, "Сума, грн.");
    model->setHeaderData(3,Qt::Horizontal, "Замовник");
    model->setHeaderData(4,Qt::Horizontal, "Дата");
    ui->tableView->setColumnWidth(0,60);
    ui->tableView->setColumnWidth(1,185);
    ui->tableView->setColumnWidth(2,70);
    ui->tableView->setColumnWidth(3,300);
    ui->tableView->setColumnWidth(4,70);

}

void reestr_ttn::on_tableView_clicked(const QModelIndex &index)
{
    int temp_nom;
    temp_nom = ui->tableView->model()->data(ui->tableView->model()->index(index.row(),0)).toInt();
    qDebug() << temp_nom;
    emit sendData(temp_nom);


}

void reestr_ttn::on_pushButton_clicked()
{
    viewttn->show();
}


void reestr_ttn::on_tableView_doubleClicked(const QModelIndex &index)
{
    viewttn->show();
}
