#include "custumers.h"
#include "ui_custumers.h"

custumers::custumers(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::custumers)
{
    ui->setupUi(this);

    //Горячая клавиша Отмена=Esc
    keyCancel = new QShortcut(this);
    keyCancel->setKey(Qt::Key_Escape);
    connect(keyCancel, SIGNAL(activated()), this, SLOT(close()));
}

custumers::~custumers()
{
    delete ui;
}

void custumers::on_pushButton_clicked()
{
    if (edit==false){
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
    }else{
        if(ui->lineEdit->text().count() > 2){
            query = new QSqlQuery();
            query->prepare("UPDATE custumers SET cust_name = :cust_name, address = :address, tel = :tel, kod_pp = :kod_pp, n_reg_svid = :n_reg_svid WHERE cust_id = :cust_id;");
            query->bindValue(":cust_name", ui->lineEdit->text());
            query->bindValue(":address", ui->lineEdit_2->text());
            query->bindValue(":tel", ui->lineEdit_3->text());
            query->bindValue(":kod_pp", ui->lineEdit_4->text());
            query->bindValue(":n_reg_svid", ui->lineEdit_5->text());
            query->bindValue(":cust_id", index_table);
            query->exec();
            emit buttonclicked();
            close();
        }else{

            QMessageBox::information(this, "Увага", "Відсутнє імя замовника");
        }

    }

}

void custumers::receiveData(int i, bool e)
{
    index_table = i;
    edit=e;

    if(edit==true){
        ui->pushButton->setText("Редагувати");
        ui->lineEdit->setEnabled(false);
        setWindowTitle("Редагувати");
    }else{
        ui->pushButton->setText("Додати");
        ui->lineEdit->setEnabled(true);
        setWindowTitle("Додати");
    }

    if(edit==true){
        query = new QSqlQuery();
        query->exec("SELECT cust_name, address, tel, kod_pp, n_reg_svid FROM zbyt.custumers WHERE cust_id="+QString::number(index_table)+";");
        while (query->next())
        {
            ui->lineEdit->setText(query->value(0).toString());
            ui->lineEdit_2->setText(query->value(1).toString());
            ui->lineEdit_3->setText(query->value(2).toString());
            ui->lineEdit_4->setText(query->value(3).toString());
            ui->lineEdit_5->setText(query->value(4).toString());
        }
    }
}

