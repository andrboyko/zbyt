#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    viewttn = new View_ttn();
    viewttn->setWindowFlags(Qt::Tool);
    connect(this, SIGNAL(sendData(int)), viewttn, SLOT(recieveData(int)));

    createttn = new create_ttn();
    createttn->setWindowFlags(Qt::Dialog);
    findByDate();
    ui->tableView->selectRow(0);

   // показать ТТН за текущий месяц
    ui->comboBox->setCurrentIndex((QDate::currentDate().month())-1);
    ui->spinBox->setValue(QDate::currentDate().year());



}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::findByDate(){

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
void MainWindow::on_spinBox_valueChanged(int arg1)
{
    findByDate();
}
void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    findByDate();
}

// функция выборки по номеру ТТН
void MainWindow::on_lineEdit_editingFinished()
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

void MainWindow::on_tableView_clicked(const QModelIndex &index)
{

    index_del = ui->tableView->model()->data(ui->tableView->model()->index(index.row(),0)).toInt();
    emit sendData(index_del);

}


void MainWindow::on_pushButton_6_clicked()
{

}

void MainWindow::on_pushButton_10_clicked()
{

}

void MainWindow::on_pushButton_clicked()
{
    createttn->show();
}

void MainWindow::on_pushButton_11_clicked()
{

        viewttn->show();

}

void MainWindow::on_tableView_doubleClicked(const QModelIndex &index)
{
        viewttn->show();
}




void MainWindow::on_pushButton_2_clicked()
{
    query = new QSqlQuery();
    query->prepare("DELETE FROM ttn WHERE ttn_id = :ttn_id");
    query->bindValue(":ttn_id", index_del);
    query->exec();
    findByDate();
}