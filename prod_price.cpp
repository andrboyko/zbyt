#include "prod_price.h"
#include "ui_prod_price.h"

prod_price::prod_price(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::prod_price)
{
    ui->setupUi(this);
    RefreshTabl_prod();


}

prod_price::~prod_price()
{
    delete ui;
}

void prod_price::RefreshTabl_prod()
{
    model = new QSqlQueryModel;
    model->setQuery("SELECT prod_id, prod_name, prod_price_retail, prod_price_barter, prod_price_wholesale FROM zbyt.products;");
    ui->tableView->setModel(model);
    model->setHeaderData(0,Qt::Horizontal, "Шифр");
    model->setHeaderData(1,Qt::Horizontal, "Назва");
    model->setHeaderData(2,Qt::Horizontal, "Ціна,роздр.");
    model->setHeaderData(3,Qt::Horizontal, "Ціна,бартер");
    model->setHeaderData(4,Qt::Horizontal, "Ціна,опт");
    ui->tableView->setColumnWidth(0,100);
    ui->tableView->setColumnWidth(1,175);
    ui->tableView->setColumnWidth(2,80);
    ui->tableView->setColumnWidth(3,80);
    ui->tableView->setColumnWidth(4,80);
}


void prod_price::on_pushButton_clicked()
{
    QWidget *prod_add = new QWidget;
    query = new QSqlQuery;
    prod_add->setWindowFlags(Qt::Tool);
    prod_add->setWindowTitle("Добавить товар");
    prod_add->setFont(QFont("Times New Roman", 12));
    prod_add->setFixedWidth(335);
    prod_add->setWindowModality(Qt::WindowModality::ApplicationModal);

    QLabel* label_1 = new QLabel ("Шифр");
    QLineEdit* lineEdit_1 = new QLineEdit;

    QLabel* label_2 = new QLabel ("Назва товару");
    QLineEdit* lineEdit_2 = new QLineEdit;

    QLabel* label_3 = new QLabel ("Ціна роздріб");
    QDoubleSpinBox* doubleSpinBox_1 = new QDoubleSpinBox;
    doubleSpinBox_1->setMaximum(999999.99);

    QLabel* label_4 = new QLabel ("Ціна бартер");
    QDoubleSpinBox* doubleSpinBox_2 = new QDoubleSpinBox;
    doubleSpinBox_2->setMaximum(999999.99);

    QLabel* label_5 = new QLabel ("Ціна опт");
    QDoubleSpinBox* doubleSpinBox_3 = new QDoubleSpinBox;
    doubleSpinBox_3->setMaximum(999999.99);

    QPushButton *pushButton_1 = new QPushButton ("Добавить");

    QGridLayout *GridProd_1 = new QGridLayout;
    GridProd_1->addWidget(label_1, 0, 0);
    GridProd_1->addWidget(lineEdit_1, 0, 1);
    GridProd_1->addWidget(label_2, 1, 0);
    GridProd_1->addWidget(lineEdit_2, 1, 1);
    GridProd_1->addWidget(label_3, 2, 0);
    GridProd_1->addWidget(doubleSpinBox_1, 2, 1);
    GridProd_1->addWidget(label_4, 3, 0);
    GridProd_1->addWidget(doubleSpinBox_2, 3, 1);
    GridProd_1->addWidget(label_5, 4, 0);
    GridProd_1->addWidget(doubleSpinBox_3, 4, 1);
    GridProd_1->addWidget(pushButton_1, 5, 1);
    prod_add->setLayout(GridProd_1);

    connect(pushButton_1, SIGNAL (clicked()), this, SLOT(prod_add( )));


    prod_add->show();
}

void prod_price::prod_add()
{

}
