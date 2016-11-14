#include "custumers_add.h"
#include "ui_custumers_add.h"

custumers_add::custumers_add(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::custumers_add)
{
    ui->setupUi(this);

    //Горячая клавиша Отмена=Esc
    keyCancel = new QShortcut(this);
    keyCancel->setKey(Qt::Key_Escape);
    connect(keyCancel, SIGNAL(activated()), this, SLOT(close()));
}

custumers_add::~custumers_add()
{
    delete ui;
}

void custumers_add::on_pushButton_clicked()
{

    if(ui->lineEdit->text().count() > 2){
        query = new QSqlQuery();
        query->prepare("INSERT INTO custumers (cust_name, address, tel, kod_pp, n_reg_svid) VALUES (:cust_name, :address, :tel, :kod_pp, :n_reg_svid);");
        query->bindValue(":cust_name", ui->lineEdit->text());
        query->bindValue(":address", ui->lineEdit_2->text());
        query->bindValue(":tel", ui->lineEdit_3->text());
        query->bindValue(":kod_pp", ui->lineEdit_4->text());
        query->bindValue(":n_reg_svid", ui->lineEdit_5->text());
        query->exec();
        emit buttonclicked();
        close();
    }else{

        QMessageBox::information(this, "Увага", "Відсутнє імя замовника");

    }



}
