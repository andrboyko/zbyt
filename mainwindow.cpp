#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //регулярное выражение для LineEdit поиска по номеру накладной
    QRegExp exp("[0-9]{0,6}");
    ui->lineEdit->setValidator(new QRegExpValidator(exp, this));

    // показать ТТН за текущий месяц
    ui->comboBox->setCurrentIndex((QDate::currentDate().month())-1);
    ui->spinBox->setValue(QDate::currentDate().year());
    RefreshTabl_ttn();
    ui->pushButton_10->setChecked(true);
    index_table = 0;
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_spinBox_valueChanged(int arg1)
{
    if(ui->pushButton_6->isChecked()){
        RefreshTabl_coming();
    }else if (ui->pushButton_10->isChecked()){
        RefreshTabl_ttn();
    }
}

void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    if(ui->pushButton_6->isChecked()){
        RefreshTabl_coming();
    }else if (ui->pushButton_10->isChecked()){
        RefreshTabl_ttn();
    }
}

void MainWindow::on_tableView_clicked(const QModelIndex &index)
{
    index_table = ui->tableView->model()->data(ui->tableView->model()->index(index.row(),0)).toInt();
}

// Кнопка плюсик
void MainWindow::on_pushButton_clicked()
{
    // если выбрано отгрузка
    if (ui->pushButton_10->isChecked()){

            t_t_n = new ttn();
            t_t_n->setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::WindowCloseButtonHint);
            connect(t_t_n, SIGNAL(PushB4()), this, SLOT(RefreshTabl_ttn()));
            connect(this, SIGNAL(sendData(int, bool)), t_t_n, SLOT(receiveData(int, bool)));
            emit sendData(index_table, false);
            t_t_n->show();

    // если выбрано Продукция
    }else if(ui->pushButton_8->isChecked()){

        prod = new products;
        prod->setWindowFlags(Qt::Tool);
        connect(prod, SIGNAL(buttonclicked()), this, SLOT(RefreshTabl_prod()));
        connect(this, SIGNAL(sendData(int, bool)), prod, SLOT(receiveData(int, bool)));
        emit sendData(index_table, false);
        prod->show();
        prod->activateWindow();

    // если выбрано заказчики
    }else if(ui->pushButton_7->isChecked()){
        cust = new custumers();
        cust->setWindowFlags(Qt::Tool);
        connect(cust, SIGNAL(buttonclicked()), this, SLOT(RefreshTabl_cust()));
        connect(this, SIGNAL(sendData(int, bool)), cust, SLOT(receiveData(int, bool)));
        emit sendData(index_table, false);
        cust->show();
        cust->activateWindow();

    // если выбрано приход
    }else if (ui->pushButton_6->isChecked()){
        prodcoming = new prod_coming;
        prodcoming->setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::WindowCloseButtonHint);
        connect(prodcoming, SIGNAL(PushB4()), this, SLOT(RefreshTabl_coming()));
        prodcoming->show();
    }
}

// Кнопка редактировать
void MainWindow::on_pushButton_5_clicked()
{
if(index_table!=0){
    // если выбрано Продукция
    if(ui->pushButton_8->isChecked()){

        prod = new products;
        prod->setWindowFlags(Qt::Tool);
        connect(prod, SIGNAL(buttonclicked()), this, SLOT(RefreshTabl_prod()));
        connect(this, SIGNAL(sendData(int, bool)), prod, SLOT(receiveData(int, bool)));
        emit sendData(index_table, true);
        prod->show();
        prod->activateWindow();

    // если выбрано заказчики
    }else if(ui->pushButton_7->isChecked()){
        cust = new custumers();
        cust->setWindowFlags(Qt::Tool);
        connect(cust, SIGNAL(buttonclicked()), this, SLOT(RefreshTabl_cust()));
        connect(this, SIGNAL(sendData(int, bool)), cust, SLOT(receiveData(int, bool)));
        emit sendData(index_table, true);
        cust->show();
        cust->activateWindow();

    // если выбрано отгрузка
    }else if (ui->pushButton_10->isChecked()){

        t_t_n = new ttn();
        t_t_n->setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::WindowCloseButtonHint);
        connect(this, SIGNAL(sendData(int, bool)), t_t_n, SLOT(receiveData(int, bool)));
        connect(t_t_n, SIGNAL(PushB4()), this, SLOT(RefreshTabl_ttn()));
        emit sendData(index_table, true);
        t_t_n->show();
        t_t_n->activateWindow();
    }
}else{

    QMessageBox::information(this, "Увага", "Виберіть запис для редагування");
}
}

// Кнопка Удалить
void MainWindow::on_pushButton_2_clicked()
{
if (index_table!=0){
    if (ui->pushButton_6->isChecked()|| ui->pushButton_10->isChecked()){
        QMessageBox msgBox;
        msgBox.setWindowTitle("Увага");
        msgBox.setText("Видалити запис");

        msgBox.setStandardButtons(QMessageBox::Yes);
        msgBox.addButton(QMessageBox::No);
        msgBox.setDefaultButton(QMessageBox::No);
        msgBox.setButtonText(QMessageBox::Yes, "Так");
        msgBox.setButtonText(QMessageBox::No, "Ні");
        if(msgBox.exec() == QMessageBox::Yes){
            query = new QSqlQuery();
            query->prepare("DELETE FROM ttn WHERE ttn_id = :ttn_id");
            query->bindValue(":ttn_id", index_table);
            query->exec();
            query->prepare("DELETE FROM ttn_items WHERE ttn_id = :ttn_id");
            query->bindValue(":ttn_id", index_table);
            query->exec();

            if (ui->pushButton_6->isChecked()){
            RefreshTabl_coming();
            }else{
                RefreshTabl_ttn();
            }


        }else {
            // do something else
        }
   }else{
         QMessageBox::information(this, "Увага", "Ви не можете видалити цей запис ");
    }
}else{
         QMessageBox::information(this, "Увага", "Виберіть запис для видалення ");
}
}

// Кнопка Приход
void MainWindow::on_pushButton_6_clicked()
{
    ui->comboBox->setVisible(true);
    ui->spinBox->setVisible(true);
    ui->label->setVisible(true);
    ui->lineEdit->setVisible(true);
    ui->pushButton_8->setChecked(false);
    ui->pushButton_7->setChecked(false);
    ui->pushButton_10->setChecked(false);
    ui->pushButton_6->setChecked(true);
    RefreshTabl_coming();
    index_table = 0;

}

// Кнопка продукты
void MainWindow::on_pushButton_8_clicked()
{
    ui->comboBox->setVisible(false);
    ui->spinBox->setVisible(false);
    ui->label->setVisible(false);
    ui->lineEdit->setVisible(false);
    ui->pushButton_7->setChecked(false);
    ui->pushButton_6->setChecked(false);
    ui->pushButton_10->setChecked(false);
    ui->pushButton_8->setChecked(true);
    RefreshTabl_prod();
    index_table = 0;

}

// Кнопка заказчики
void MainWindow::on_pushButton_7_clicked()
{
    ui->label->setVisible(false);
    ui->lineEdit->setVisible(false);
    ui->comboBox->setVisible(false);
    ui->spinBox->setVisible(false);
    ui->pushButton_8->setChecked(false);
    ui->pushButton_6->setChecked(false);
    ui->pushButton_10->setChecked(false);
    ui->pushButton_7->setChecked(true);
    RefreshTabl_cust();
    index_table = 0;

}

// Кнопка Збут
void MainWindow::on_pushButton_10_clicked()
{
    ui->label->setVisible(true);
    ui->lineEdit->setVisible(true);
    ui->comboBox->setVisible(true);
    ui->spinBox->setVisible(true);
    ui->pushButton_8->setChecked(false);
    ui->pushButton_6->setChecked(false);\
    ui->pushButton_7->setChecked(false);
    ui->pushButton_10->setChecked(true);
    RefreshTabl_ttn();
    index_table = 0;

}

// Поиск по номеру
void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{
    if (ui->lineEdit->text()== NULL && ui->pushButton_6->isChecked()){
    RefreshTabl_coming();
    }else if(ui->lineEdit->text()== NULL && ui->pushButton_10->isChecked()){
    RefreshTabl_ttn();
    }else{

    QString ttn_id;
    ttn_id = "'" + arg1 + "%" +"'";
    model = new QSqlQueryModel;
    model->setQuery("select ttn_id, operation_name,(SELECT sum(ttn_item_quantity*ttn_item_price)FROM ttn_items where ttn.ttn_id = ttn_items.ttn_id), cust_name, ttn_date FROM ttn, operations, custumers where ttn.operation_id = operations.operation_id and ttn.cust_id = custumers.cust_id and ttn_id LIKE "+ ttn_id +";");
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
}

void MainWindow::on_action_triggered()
{
    ui->pushButton_8->clicked();
}

void MainWindow::on_action_2_triggered()
{
    ui->pushButton_7->clicked();
}

// обновить таблицу с накладными збут
void MainWindow::RefreshTabl_ttn()
{
    int month;
     int year;
     month=ui->comboBox->currentIndex();
     year=ui->spinBox->value();

     model = new QSqlQueryModel;
     model->setQuery("select ttn_id, operation_name, cust_name, sum, ttn_date FROM ttn, operations, custumers where ttn.operation_id = operations.operation_id and ttn.cust_id = custumers.cust_id and NOT (ttn.operation_id = 1) and year(ttn_date) =" + QString::number(year) + " and month(ttn_date)=" +QString::number(month+1)+";");
     proxyModel = new QSortFilterProxyModel(this);
     proxyModel->setSourceModel(model);
     proxyModel->sort(0, Qt::DescendingOrder);
     ui->tableView->setModel(proxyModel);
     model->setHeaderData(0,Qt::Horizontal, "№ ТТН");
     model->setHeaderData(1,Qt::Horizontal, "Вид");
     model->setHeaderData(2,Qt::Horizontal, "Замовник");
     model->setHeaderData(3,Qt::Horizontal, "Сума, грн.");
     model->setHeaderData(4,Qt::Horizontal, "Дата");
     ui->tableView->setColumnHidden(0,0);
     ui->tableView->setColumnWidth(0,60);
     ui->tableView->setColumnWidth(1,185);
     ui->tableView->setColumnWidth(2,300);
     ui->tableView->setColumnWidth(3,70);
     ui->tableView->setColumnWidth(4,70);
}

// обновить таблицу с накладными приход
void MainWindow::RefreshTabl_coming()
{
    int month;
     int year;
     month=ui->comboBox->currentIndex();
     year=ui->spinBox->value();

     model = new QSqlQueryModel;
     model->setQuery("select ttn_id, operation_name, cust_name, sum, ttn_date FROM ttn, operations, custumers where ttn.operation_id = operations.operation_id and ttn.cust_id = custumers.cust_id and ttn.operation_id = 1 and year(ttn_date) =" + QString::number(year) + " and month(ttn_date)=" +QString::number(month+1)+";");
     proxyModel = new QSortFilterProxyModel(this);
     proxyModel->setSourceModel(model);
     proxyModel->sort(0, Qt::DescendingOrder);
     ui->tableView->setModel(proxyModel);
     model->setHeaderData(0,Qt::Horizontal, "№ ТТН");
     model->setHeaderData(1,Qt::Horizontal, "Вид");
     model->setHeaderData(2,Qt::Horizontal, "Постачальник");
     model->setHeaderData(3,Qt::Horizontal, "Сума, грн.");
     model->setHeaderData(4,Qt::Horizontal, "Дата");
     ui->tableView->setColumnHidden(0,0);
     ui->tableView->setColumnWidth(0,60);
     ui->tableView->setColumnWidth(1,185);
     ui->tableView->setColumnWidth(2,300);
     ui->tableView->setColumnWidth(3,70);
     ui->tableView->setColumnWidth(4,70);
}

// Обновить таблицу продуктов
void MainWindow::RefreshTabl_prod()
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

// Обновить таблицу заказчиков
void MainWindow::RefreshTabl_cust()
{
    model = new QSqlQueryModel;
    model->setQuery("SELECT * FROM zbyt.custumers WHERE NOT (cust_id =0);");
    ui->tableView->setModel(model);
    model->setHeaderData(1,Qt::Horizontal, "Имя");
    model->setHeaderData(2,Qt::Horizontal, "Адрес");
    model->setHeaderData(3,Qt::Horizontal, "Телефон");
    model->setHeaderData(4,Qt::Horizontal, "Код П/П");
    model->setHeaderData(5,Qt::Horizontal, "№ Реєстртації");
    ui->tableView->setColumnHidden(0,1);
    ui->tableView->setColumnWidth(1,260);
    ui->tableView->setColumnWidth(2,300);
    ui->tableView->setColumnWidth(3,95);
    ui->tableView->setColumnWidth(4,80);
    ui->tableView->setColumnWidth(5,100);
}

