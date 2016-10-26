#include "custumers_edit.h"
#include "ui_custumers_edit.h"

custumers_edit::custumers_edit(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::custumers_edit)
{
    ui->setupUi(this);




}


custumers_edit::~custumers_edit()
{
    delete ui;
}

void custumers_edit::on_pushButton_clicked()
{

      query = new QSqlQuery();
      QString sql;
      sql ="UPDATE custumers "
           "SET cust_name = :cust_name, address = :address, tel = :tel, "
           "kod_pp = :kod_pp, n_reg_svid = :n_reg_svid WHERE cust_id=:cust_id;";
    query->prepare(sql);
    query->bindValue(":cust_name", ui->lineEdit->text());
    query->bindValue(":address", ui->lineEdit_2->text());
    query->bindValue(":tel", ui->lineEdit_3->text());
    query->bindValue(":kod_pp", ui->lineEdit_4->text());
    query->bindValue(":n_reg_svid", ui->lineEdit_5->text());
    query->bindValue(":cust_id", index_cust);
    query->exec();

    emit buttonclicked();

    close();
}

void custumers_edit::reciveData(int i)
{
    index_cust = i;

    query = new QSqlQuery();
    query->exec("SELECT cust_name, address, tel, kod_pp, n_reg_svid FROM custumers WHERE cust_id = "+ QString::number(index_cust) +";");

    while (query->next())
    {
        ui->lineEdit->setText(query->value(0).toString());
        ui->lineEdit_2->setText(query->value(1).toString());
        ui->lineEdit_3->setText(query->value(2).toString());
        ui->lineEdit_4->setText(query->value(3).toString());
        ui->lineEdit_5->setText(query->value(4).toString());
    }
}

