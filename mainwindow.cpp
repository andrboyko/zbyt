#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // показать ТТН за текущий месяц
    ui->comboBox->setCurrentIndex((QDate::currentDate().month())-1);
    ui->spinBox->setValue(QDate::currentDate().year());
    RefreshTabl_ttn();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::RefreshTabl_ttn()
{

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
    RefreshTabl_ttn();
}
void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    RefreshTabl_ttn();
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
    index_ttn = ui->tableView->model()->data(ui->tableView->model()->index(index.row(),0)).toInt();
}

// Создать форму для создания накладной
void MainWindow::on_pushButton_clicked()
{
    createttn = new create_ttn();
    createttn->setWindowFlags(Qt::Dialog);
    connect(createttn, SIGNAL(PushB4()), this, SLOT(RefreshTabl_ttn()));
    createttn->show();
}


//Удалить запись накладной
void MainWindow::on_pushButton_2_clicked()
{
    query = new QSqlQuery();
    query->prepare("DELETE FROM ttn WHERE ttn_id = :ttn_id");
    query->bindValue(":ttn_id", index_ttn);
    query->exec();

    query->prepare("DELETE FROM ttn_items WHERE ttn_id = :ttn_id");
    query->bindValue(":ttn_id", index_ttn);
    query->exec();

    RefreshTabl_ttn();
}

void MainWindow::on_pushButton_8_clicked()
{
    prodprice = new prod_price();
    prodprice->setWindowFlags(Qt::Dialog);
    prodprice->show();
}
