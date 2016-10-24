#include "customers.h"
#include "ui_customers.h"

customers::customers(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::customers)
{
    ui->setupUi(this);
    RefreshTabl_customers();
}

customers::~customers()
{
    delete ui;
}

//Обновление таблицы заказчиков
void customers::RefreshTabl_customers()
{
    model = new QSqlQueryModel;
    model->setQuery("SELECT * FROM zbyt.custumers;");
    ui->tableView->setModel(model);
    model->setHeaderData(0,Qt::Horizontal, "№");
    model->setHeaderData(1,Qt::Horizontal, "Имя");
    model->setHeaderData(2,Qt::Horizontal, "Адрес");
    model->setHeaderData(3,Qt::Horizontal, "Телефон");
    model->setHeaderData(4,Qt::Horizontal, "Код П/П");
    model->setHeaderData(5,Qt::Horizontal, "№ Реєстртації");
    ui->tableView->setColumnWidth(0,20);
    ui->tableView->setColumnWidth(1,260);
    ui->tableView->setColumnWidth(2,320);
    ui->tableView->setColumnWidth(3,80);
    ui->tableView->setColumnWidth(4,80);
    ui->tableView->setColumnWidth(5,100);
}

// кнопка добавить
void customers::on_pushButton_clicked()
{
    cust_add = new custumers_add();
    cust_add->setWindowFlags(Qt::Tool);
    connect(cust_add, SIGNAL(buttonclicked()), this, SLOT(RefreshTabl_customers()));
    cust_add->show();
    cust_add->activateWindow();

}
