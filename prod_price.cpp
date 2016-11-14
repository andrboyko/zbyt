#include "prod_price.h"
#include "ui_prod_price.h"

prod_price::prod_price(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::prod_price)
{
    ui->setupUi(this);

    RefreshTabl_prod();
    //Горячая клавиша Отмена=Esc
    keyCancel = new QShortcut(this);
    keyCancel->setKey(Qt::Key_Escape);
    connect(keyCancel, SIGNAL(activated()), this, SLOT(close()));

}

prod_price::~prod_price()
{
    delete ui;
}

// обновление таблицы с продукцией
void prod_price::RefreshTabl_prod()
{
    model = new QSqlQueryModel;
    model->setQuery("SELECT prod_id, cipher, prod_name, prod_price_retail, prod_price_barter, prod_price_wholesale FROM zbyt.products;");
    ui->tableView->setModel(model);
    model->setHeaderData(1,Qt::Horizontal, "Шифр");
    model->setHeaderData(2,Qt::Horizontal, "Назва виробу");
    model->setHeaderData(3,Qt::Horizontal, "Ціна,роздр., грн.");
    model->setHeaderData(4,Qt::Horizontal, "Ціна,бартер");
    model->setHeaderData(5,Qt::Horizontal, "Ціна,опт");
    ui->tableView->setColumnHidden(0,1);
    ui->tableView->setColumnWidth(1,100);
    ui->tableView->setColumnWidth(2,470);
    ui->tableView->setColumnWidth(3,110);
    ui->tableView->setColumnWidth(4,80);
    ui->tableView->setColumnWidth(5,80);
}

// вывести форму для добавления новой продукции в справочник
void prod_price::on_pushButton_clicked()
{
    prodadd = new prod_add;
    prodadd->setWindowFlags(Qt::Tool);
    connect(prodadd, SIGNAL(buttonclicked()), this, SLOT(RefreshTabl_prod()));
    prodadd->show();
    prodadd->activateWindow();


}

// вывести форму для изменения цены
void prod_price::on_pushButton_2_clicked()
{


    prodedit = new prod_edit;
    prodedit->setWindowFlags(Qt::Tool);
    connect(prodedit, SIGNAL(buttonclicked()), this, SLOT(RefreshTabl_prod()));
    connect(this, SIGNAL(sendData(int)), prodedit, SLOT(recieveData(int)));
    emit sendData(index_prod);
    prodedit->show();
    prodedit->activateWindow();




}

void prod_price::on_tableView_clicked(const QModelIndex &index)
{
    index_prod = ui->tableView->model()->data(ui->tableView->model()->index(index.row(),0)).toInt();
}
