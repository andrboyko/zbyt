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

    // показать ТТН за текущий год
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
        ui->comboBox->setCurrentIndex(0);
        t_t_n = new ttn();
        t_t_n->setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::WindowCloseButtonHint);
        connect(t_t_n, SIGNAL(update_table()), this, SLOT(RefreshTabl_ttn()));
        connect(this, SIGNAL(sendData(int, bool)), t_t_n, SLOT(receiveData(int, bool)));
        emit sendData(index_table, false);
        t_t_n->show();
        t_t_n->activateWindow();

        // если выбрано приход
    }else if (ui->pushButton_6->isChecked()){
        ui->comboBox->setCurrentIndex(0);
        prodcoming = new prod_coming;
        prodcoming->setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::WindowCloseButtonHint);
        connect(prodcoming, SIGNAL(update_table()), this, SLOT(RefreshTabl_coming()));
        connect(this, SIGNAL(sendData(int, bool)), prodcoming, SLOT(receiveData(int, bool)));
        emit sendData(index_table, false);
        prodcoming->show();
        prodcoming->activateWindow();

        // если выбрано Продукция
    }else if(ui->pushButton_8->isChecked()){
        prod = new products;
        prod->setWindowFlags(Qt::Tool);
        connect(prod, SIGNAL(update_table()), this, SLOT(RefreshTabl_prod()));
        connect(this, SIGNAL(sendData(int, bool)), prod, SLOT(receiveData(int, bool)));
        emit sendData(index_table, false);
        prod->show();
        prod->activateWindow();

        // если выбрано заказчики
    }else if(ui->pushButton_7->isChecked()){
        cust = new custumers();
        cust->setWindowFlags(Qt::Tool);
        connect(cust, SIGNAL(update_table()), this, SLOT(RefreshTabl_cust()));
        connect(this, SIGNAL(sendData(int, bool)), cust, SLOT(receiveData(int, bool)));
        emit sendData(index_table, false);
        cust->show();
        cust->activateWindow();
    }
}

// Кнопка редактировать
void MainWindow::on_pushButton_5_clicked()
{
    if(index_table!=0){
        // если выбрано отгрузка
        if (ui->pushButton_10->isChecked()){
            t_t_n = new ttn();
            t_t_n->setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint);
            connect(this, SIGNAL(sendData(int, bool)), t_t_n, SLOT(receiveData(int, bool)));
            connect(t_t_n, SIGNAL(update_table()), this, SLOT(RefreshTabl_ttn()));
            emit sendData(index_table, true);
            t_t_n->show();
            t_t_n->activateWindow();

            // если выбрано приход
        }else if (ui->pushButton_6->isChecked()){
            prodcoming = new prod_coming();
            prodcoming->setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint);
            connect(this, SIGNAL(sendData(int, bool)),prodcoming, SLOT(receiveData(int, bool)));
            connect(prodcoming, SIGNAL(update_table()), this, SLOT(RefreshTabl_coming()));
            emit sendData(index_table, true);
            prodcoming->show();
            prodcoming->activateWindow();

            // если выбрано Продукция
        }else if(ui->pushButton_8->isChecked()){

            prod = new products;
            prod->setWindowFlags(Qt::Tool);
            connect(prod, SIGNAL(update_table()), this, SLOT(RefreshTabl_prod()));
            connect(this, SIGNAL(sendData(int, bool)), prod, SLOT(receiveData(int, bool)));
            emit sendData(index_table, true);
            prod->show();
            prod->activateWindow();

            // если выбрано заказчики
        }else if(ui->pushButton_7->isChecked()){
            cust = new custumers();
            cust->setWindowFlags(Qt::Tool);
            connect(cust, SIGNAL(update_table()), this, SLOT(RefreshTabl_cust()));
            connect(this, SIGNAL(sendData(int, bool)), cust, SLOT(receiveData(int, bool)));
            emit sendData(index_table, true);
            cust->show();
            cust->activateWindow();
        }
    }
}

// Кнопка Удалить
void MainWindow::on_pushButton_2_clicked()
{
    if (index_table!=0){

        QMessageBox msgBox;
        msgBox.setWindowTitle("Увага");
        msgBox.setText("Видалити запис");
        msgBox.setStandardButtons(QMessageBox::Yes);
        msgBox.addButton(QMessageBox::No);
        msgBox.setDefaultButton(QMessageBox::No);
        msgBox.setButtonText(QMessageBox::Yes, "Так");
        msgBox.setButtonText(QMessageBox::No, "Ні");
        if(msgBox.exec() == QMessageBox::Yes)
        {
            query = new QSqlQuery();
            query2 = new QSqlQuery();
            queryUpdate = new QSqlQuery();

            if (ui->pushButton_10->isChecked()){
                query->prepare("SELECT ttn_item_quantity, prod_id from ttn_items WHERE ttn_id=:ttn_id");
                query->bindValue(":ttn_id", index_table);
                query->exec();
                while (query->next())
                {
                    query2->exec("SELECT prod_quantity FROM products WHERE prod_id=" +query->value(1).toString()+ ";");
                    query2->next();
                    int x;
                    x=(query2->value(0).toInt())+(query->value(0).toInt());
                    queryUpdate->prepare("UPDATE products SET prod_quantity=:prod_quantity  WHERE prod_id = :prod_id;");
                    queryUpdate->bindValue(":prod_quantity", QString::number(x) );
                    queryUpdate->bindValue(":prod_id", query->value(1).toString() );
                    queryUpdate->exec();
                }

                query->exec("DELETE FROM ttn_items WHERE ttn_id = " +QString::number(index_table)+ ";");
                query->exec("DELETE FROM ttn WHERE ttn_id = " +QString::number(index_table)+ ";");
                RefreshTabl_ttn();

            }else if(ui->pushButton_6->isChecked()){
                //подсчет количества продукции
                query->prepare("SELECT ttn_item_quantity, prod_id from ttn_items WHERE ttn_id=:ttn_id");
                query->bindValue(":ttn_id", index_table);
                query->exec();
                while (query->next())
                {
                    query2->exec("SELECT prod_quantity FROM products WHERE prod_id=" +query->value(1).toString()+ ";");
                    query2->next();
                    int x;
                    x=(query2->value(0).toInt())-(query->value(0).toInt());
                    queryUpdate->prepare("UPDATE products SET prod_quantity=:prod_quantity  WHERE prod_id = :prod_id;");
                    queryUpdate->bindValue(":prod_quantity", QString::number(x) );
                    queryUpdate->bindValue(":prod_id", query->value(1).toString() );
                    queryUpdate->exec();
                }
                query->exec("DELETE FROM ttn_items WHERE ttn_id = " +QString::number(index_table)+ ";");
                query->exec("DELETE FROM ttn WHERE ttn_id = " +QString::number(index_table)+ ";");
                RefreshTabl_coming();
            }else{
                QMessageBox::information(this, "Увага", "Ви не можете видалити цей запис ");
            }
        }else{
            // do something else
        }
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
    ui->comboBox->setCurrentIndex(0);

}

// Кнопка Збут
void MainWindow::on_pushButton_10_clicked()
{
    ui->label->setVisible(true);
    ui->lineEdit->setVisible(true);
    ui->comboBox->setVisible(true);
    ui->spinBox->setVisible(true);
    ui->pushButton_8->setChecked(false);
    ui->pushButton_6->setChecked(false);
    ui->pushButton_7->setChecked(false);
    ui->pushButton_10->setChecked(true);
    RefreshTabl_ttn();
    index_table = 0;
    ui->comboBox->setCurrentIndex(0);

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
// Нашие Реквизиты
void MainWindow::on_action_4_triggered()
{
widget_our_requisites = new QWidget;
verticalLayout = new QVBoxLayout;
our_requisites = new QTableView;
tableModel = new QSqlTableModel;

tableModel->setTable("our_requisites");
tableModel->select();
tableModel->setEditStrategy(QSqlTableModel::OnFieldChange);
tableModel->setHeaderData(0,Qt::Horizontal, "id");
tableModel->setHeaderData(1,Qt::Horizontal, "Імя");
tableModel->setHeaderData(2,Qt::Horizontal, "Адрес");
tableModel->setHeaderData(3,Qt::Horizontal, "Телефон");
tableModel->setHeaderData(4,Qt::Horizontal, "Індивідуальний под. номер");
tableModel->setHeaderData(5,Qt::Horizontal, "Номер свідоцтва");
our_requisites->setModel(tableModel);
our_requisites->setColumnHidden(0,1);
our_requisites->resizeColumnsToContents();
verticalLayout->addWidget(our_requisites);
widget_our_requisites->setWindowFlags(Qt::Tool);
widget_our_requisites->setWindowTitle("Наші реквізити");
widget_our_requisites->setWindowModality(Qt::ApplicationModal);
widget_our_requisites->setFixedSize(800,100);
widget_our_requisites->setLayout(verticalLayout);
widget_our_requisites->show();
widget_our_requisites->activateWindow();
}

// обновить таблицу с накладными збут
void MainWindow::RefreshTabl_ttn()
{
    model = new QSqlQueryModel;
    proxyModel = new QSortFilterProxyModel(this);

    if(ui->comboBox->currentIndex()!=0){
        model->setQuery("select ttn_id, operation_name, cust_name, sum, ttn_date FROM ttn, operations, custumers where ttn.operation_id = operations.operation_id and ttn.cust_id = custumers.cust_id and NOT (ttn.operation_id = 1) and year(ttn_date) =" + QString::number(ui->spinBox->value()) + " and month(ttn_date)=" +QString::number(ui->comboBox->currentIndex())+";");
    }else{
        model->setQuery("select ttn_id, operation_name, cust_name, sum, ttn_date FROM ttn, operations, custumers where ttn.operation_id = operations.operation_id and ttn.cust_id = custumers.cust_id and NOT (ttn.operation_id = 1) and year(ttn_date) =" + QString::number(ui->spinBox->value()) + ";");
    }
    model->setHeaderData(0,Qt::Horizontal, "№ ТТН");
    model->setHeaderData(1,Qt::Horizontal, "Вид");
    model->setHeaderData(2,Qt::Horizontal, "Замовник");
    model->setHeaderData(3,Qt::Horizontal, "Сума, грн.");
    model->setHeaderData(4,Qt::Horizontal, "Дата");
    proxyModel->setSourceModel(model);
    proxyModel->sort(0, Qt::DescendingOrder);
    ui->tableView->setModel(proxyModel);
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
    model = new QSqlQueryModel;
    proxyModel = new QSortFilterProxyModel(this);


    if(ui->comboBox->currentIndex()!=0){
        model->setQuery("select ttn_id, operation_name, cust_name, sum, ttn_date FROM ttn, operations, custumers where ttn.operation_id = operations.operation_id and ttn.cust_id = custumers.cust_id and ttn.operation_id = 1 and year(ttn_date) =" + QString::number(ui->spinBox->value()) + " and month(ttn_date)=" +QString::number(ui->comboBox->currentIndex())+";");
    }else{
        model->setQuery("select ttn_id, operation_name, cust_name, sum, ttn_date FROM ttn, operations, custumers where ttn.operation_id = operations.operation_id and ttn.cust_id = custumers.cust_id and ttn.operation_id = 1  and year(ttn_date) =" + QString::number(ui->spinBox->value()) + ";");
    }
    model->setHeaderData(0,Qt::Horizontal, "№ ТТН");
    model->setHeaderData(1,Qt::Horizontal, "Вид");
    model->setHeaderData(2,Qt::Horizontal, "Постачальник");
    model->setHeaderData(3,Qt::Horizontal, "Сума, грн.");
    model->setHeaderData(4,Qt::Horizontal, "Дата");
    proxyModel->setSourceModel(model);
    proxyModel->sort(0, Qt::DescendingOrder);
    ui->tableView->setModel(proxyModel);
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
    model->setQuery("SELECT prod_id, cipher, prod_name, prod_quantity, prod_price_retail, prod_price_barter, prod_price_wholesale FROM zbyt.products;");
    ui->tableView->setModel(model);
    model->setHeaderData(1,Qt::Horizontal, "Шифр");
    model->setHeaderData(2,Qt::Horizontal, "Назва виробу");
    model->setHeaderData(3,Qt::Horizontal, "Кількість");
    model->setHeaderData(4,Qt::Horizontal, "Ціна,роздр., грн.");
    model->setHeaderData(5,Qt::Horizontal, "Ціна,бартер");
    model->setHeaderData(6,Qt::Horizontal, "Ціна,опт");
    ui->tableView->setColumnHidden(0,1);
    ui->tableView->setColumnWidth(1,100);
    ui->tableView->setColumnWidth(2,470);
    ui->tableView->setColumnWidth(3,80);
    ui->tableView->setColumnWidth(4,110);
    ui->tableView->setColumnWidth(5,80);
    ui->tableView->setColumnWidth(6,80);

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


void MainWindow::on_tableView_doubleClicked()
{
    // если выбрано отгрузка
    if (ui->pushButton_10->isChecked()){

        // если выбрано приход
    }else if (ui->pushButton_6->isChecked()){

        // если выбрано Продукция
    }else if(ui->pushButton_8->isChecked()){
        ui->pushButton_5->clicked();

        // если выбрано заказчики
    }else if(ui->pushButton_7->isChecked()){
        ui->pushButton_5->clicked();
    }
}

void MainWindow::on_pushButton_3_clicked()
{

    query = new QSqlQuery();

    if (ui->pushButton_10->isChecked()){
        file=new QFile;
        file->setFileName("C:/Temp/test.html");
        file->open(QIODevice::WriteOnly);



        QTextStream in(file);
        in.setCodec("UTF-8");
        in <<QString("<!DOCTYPE HTML>");
        in <<QString("<HTML>");
        in <<QString("<HEAD>");
        in <<QString("    <TITLE>Податкова накладна</TITLE>");
        in <<QString("    <meta charset='UTF-8'>");
        in <<QString("    <link href=\"css\\podatkova.css\" rel=\"stylesheet\" type=\"text/css\"> </HEAD>");

        in <<QString("<BODY>");
        in <<QString("    <div id=\"page_align\">");
        in <<QString("        <div id=\"header\">");
        in <<QString("            <div id=\"header_right\">");
        in <<QString("                <p> ЗАТВЕРДЖЕНО");
        in <<QString("                    <p>Наказ Державної податкової");
        in <<QString("                        <p>адміністрації України");
        in <<QString("                            <p>21.12.2010 №969 </div>");
        in <<QString("            <div id=\"header_left\">");
        in <<QString("                <table style=\" border-collapse: collapse;   text-align: center; height:120px; width:225px;\" border=1px;>");
        in <<QString("                    <tr>");
        in <<QString("                        <td rowspan=\"4\">Оригінал</td>");
        in <<QString("                        <td>Видається покупцю</td>");
        in <<QString("                        <td colspan=\"2\" ; width=\"26px\"></td>");
        in <<QString("                    </tr>");
        in <<QString("                    <tr>");
        in <<QString("                        <td>Включено до ЕРПН</td>");
        in <<QString("                        <td colspan=\"2\" ; width=\"26px\"></td>");
        in <<QString("                    </tr>");
        in <<QString("                    <tr>");
        in <<QString("                        <td rowspan=\"2\">Залишається у продавця");
        in <<QString("                            <p>(тип причини)</td>");
        in <<QString("                        <td colspan=\"2\" ; width=\"26px\"></td>");
        in <<QString("                    </tr>");
        in <<QString("                    <tr>");
        in <<QString("                        <td></td>");
        in <<QString("                        <td></td>");
        in <<QString("                    </tr>");
        in <<QString("                    <tr>");
        in <<QString("                        <td colspan=\"2\">Копія (залишається у продавця)</td>");
        in <<QString("                        <td colspan=\"2\" ; width=\"26px\"></td>");
        in <<QString("                    </tr>");
        in <<QString("                </table>");
        in <<QString("                <p>(Потрібне виділити 'X') </div>");
        in <<QString("        </div>");
        in <<QString("        <h2 align=center>Податкова накладна</h2>");
        in <<QString("        <div id=\"date_nomer\">");
        in <<QString("            <div id=\"date\">");
        in <<QString("                <div id=\"left\"> Дата виписки податкової накладної</div>");
        in <<QString("                <div id=\"right\">");
        in <<QString("                    <table id=\"table_property\" border=\"1\">");
        in <<QString("                        <tr>");

        query->exec("SELECT DATE_FORMAT((SELECT ttn_date FROM zbyt.ttn WHERE ttn_id="+QString::number(index_table)+") , '%m%d%Y');");
        query->next();

        foreach(QChar c, query->value(0).toString()){
            in <<QString("                            <td>" + QString(c) + "</td>");
        }
        in <<QString("                        </tr>");
        in <<QString("                    </table>");
        in <<QString("                </div>");
        in <<QString("            </div>");
        in <<QString("            <div id=\"nomer\">");
        in <<QString("                <div id=\"left\"> Порядковий номер</div>");
        in <<QString("                <div id=\"right\">");
        in <<QString("                    <div id=\"nomer_left\">");
        in <<QString("                        <table id=\"table_property\" border=\"1\">");
        in <<QString("                            <tr>");
        in <<QString("                                <td>&nbsp&nbsp</td>");
        in <<QString("                                <td>&nbsp&nbsp</td>");
        in <<QString("                                <td>&nbsp&nbsp</td>");
        in <<QString("                                <td>&nbsp&nbsp</td>");
        in <<QString("                                <td>&nbsp&nbsp</td>");
        in <<QString("                                <td>&nbsp&nbsp</td>");
        in <<QString("                                <td>&nbsp&nbsp</td>");
        in <<QString("                        </table>");
        in <<QString("                    </div> <span style=\"font-size:16px\">\\</span>");
        in <<QString("                    <div id=\"nomer_right\">");
        in <<QString("                        <table border=\"1\" width=\"60px\" height=\"20px\" style=\"border-collapse: collapse; text-align: center;\">");
        in <<QString("                            <tr>");
        in <<QString("                                <td>1</td>");
        in <<QString("                                <td>&nbsp&nbsp</td>");
        in <<QString("                                <td>&nbsp&nbsp</td>");
        in <<QString("                        </table>");
        in <<QString("                    </div>");
        in <<QString("                </div>");
        in <<QString("            </div>");
        in <<QString("        </div>");
        in <<QString("        <div id=\"property\">");
        in <<QString("            <div id=\"property_saller\">");
        in <<QString("                <p align=center><i>ПРОДАВЕЦЬ</i></p>");
        in <<QString("                <div id=\"seller_left\">");
        in <<QString("                    <p>");
        in <<QString("                        <p>Особа (платник податку)-продавець</p>");
        in <<QString("                        <p>Індивідуальний податковий номер</p>");
        in <<QString("                        <p>");
        in <<QString("                            <p>Місцезнаходження (податкова адреса) продавця</p>");
        in <<QString("                            <p>");
        in <<QString("                                <p>Номер телефону</p>");
        in <<QString("                                <p>");
        in <<QString("                                    <p>Номер свідоцтва про реєстрацію платника податку на додану вартість (продавця) </p>");
        in <<QString("                </div>");
        in <<QString("                <div id=\"seller_right\">");
        in <<QString("                    <p>");
        in <<QString("                        <p id=\"text_border\">ВМЗ ПАТ \"Мотор Січ\"</p>");
        in <<QString("                        <p><p><p>");
        in <<QString("                            <table id=\"table_property\" border=\"1\">");
        in <<QString("                                <tr>");
        in <<QString("                                    <td>1</td>");
        in <<QString("                                    <td>4</td>");
        in <<QString("                                    <td>3</td>");
        in <<QString("                                    <td>0</td>");
        in <<QString("                                    <td>7</td>");
        in <<QString("                                    <td>7</td>");
        in <<QString("                                    <td>9</td>");
        in <<QString("                                    <td>0</td>");
        in <<QString("                                    <td>8</td>");
        in <<QString("                                    <td>2</td>");
        in <<QString("                                    <td>4</td>");
        in <<QString("                                    <td>6</td>");
        in <<QString("                                </tr>");
        in <<QString("                            </table>");
        in <<QString("                            <p id=\"text_border\">пр.Моторобудівників 15 м.Запоріжжя 69068</p>");
        in <<QString("                            <p><p><p>");
        in <<QString("                                <table id=\"table_property\" border=\"1\">");
        in <<QString("                                    <tr>");
        in <<QString("                                        <td>0</td>");
        in <<QString("                                        <td>3</td>");
        in <<QString("                                        <td>8</td>");
        in <<QString("                                        <td>4</td>");
        in <<QString("                                        <td>5</td>");
        in <<QString("                                        <td>3</td>");
        in <<QString("                                        <td>6</td>");
        in <<QString("                                        <td>5</td>");
        in <<QString("                                        <td>8</td>");
        in <<QString("                                        <td>9</td>");
        in <<QString("                                    </tr>");
        in <<QString("                                </table>");
        in <<QString("                                <p>");
        in <<QString("                                    <p>");
        in <<QString("                                        <table id=\"table_property\" border=\"1\">");
        in <<QString("                                            <tr>");
        in <<QString("                                                <td>&nbsp&nbsp</td>");
        in <<QString("                                                <td>1</td>");
        in <<QString("                                                <td>0</td>");
        in <<QString("                                                <td>0</td>");
        in <<QString("                                                <td>2</td>");
        in <<QString("                                                <td>2</td>");
        in <<QString("                                                <td>5</td>");
        in <<QString("                                                <td>4</td>");
        in <<QString("                                                <td>2</td>");
        in <<QString("                                                <td>0</td>");
        in <<QString("                                            </tr>");
        in <<QString("                                        </table>");
        in <<QString("                </div>");
        in <<QString("            </div>");
        in <<QString("            <div id=\"property_custumers\">");
        in <<QString("                <p align=center><i>ПОКУПЕЦЬ</i></p>");
        in <<QString("                <div id=\"seller_left\">");
        in <<QString("                    <p><p>");
        in <<QString("                        <p>Особа (платник податку)-покупець</p>");
        in <<QString("                        <p>Індивідуальний податковий номер</p>");
        in <<QString("                        <p>");
        in <<QString("                            <p>");
        in <<QString("                                <p>Місцезнаходження (податкова адреса) покупця</p>");
        in <<QString("                                <p>");
        in <<QString("                                    <p>");
        in <<QString("                                        <p>Номер телефону</p>");
        in <<QString("                                        <p>Номер свідоцтва про реєстрацію платника податку на додану вартість (покупця) </p>");
        in <<QString("                </div>");
        in <<QString("                <div id=\"seller_right\">");
        in <<QString("                    <p id=\"text_border\">Відгрузка за готівку зі складу збут </p>");
        in <<QString("                    <p>");
        in <<QString("                        <table id=\"table_property\" border=\"1\">");
        in <<QString("                            <tr>");
        in <<QString("                                <td>1</td>");
        in <<QString("                                <td>4</td>");
        in <<QString("                                <td>3</td>");
        in <<QString("                                <td>0</td>");
        in <<QString("                                <td>7</td>");
        in <<QString("                                <td>7</td>");
        in <<QString("                                <td>9</td>");
        in <<QString("                                <td>0</td>");
        in <<QString("                                <td>8</td>");
        in <<QString("                                <td>2</td>");
        in <<QString("                                <td>4</td>");
        in <<QString("                                <td>6</td>");
        in <<QString("                            </tr>");
        in <<QString("                        </table>");
        in <<QString("                        <p id=\"text_border\">пр.Моторобудівників 15 м.Запоріжжя 69068</p>");
        in <<QString("                        <p>");
        in <<QString("                            <p>");
        in <<QString("                                <p><p>");
        in <<QString("                                    <table id=\"table_property\" border=\"1\">");
        in <<QString("                                        <tr>");
        in <<QString("                                            <td>0</td>");
        in <<QString("                                            <td>3</td>");
        in <<QString("                                            <td>8</td>");
        in <<QString("                                            <td>4</td>");
        in <<QString("                                            <td>5</td>");
        in <<QString("                                            <td>3</td>");
        in <<QString("                                            <td>6</td>");
        in <<QString("                                            <td>5</td>");
        in <<QString("                                            <td>8</td>");
        in <<QString("                                            <td>9</td>");
        in <<QString("                                        </tr>");
        in <<QString("                                    </table>");
        in <<QString("                                    <p>");
        in <<QString("                                        <p>");
        in <<QString("                                            <table id=\"table_property\" border=\"1\">");
        in <<QString("                                                <tr>");
        in <<QString("                                                    <td>&nbsp&nbsp</td>");
        in <<QString("                                                    <td>1</td>");
        in <<QString("                                                    <td>0</td>");
        in <<QString("                                                    <td>0</td>");
        in <<QString("                                                    <td>2</td>");
        in <<QString("                                                    <td>2</td>");
        in <<QString("                                                    <td>5</td>");
        in <<QString("                                                    <td>4</td>");
        in <<QString("                                                    <td>2</td>");
        in <<QString("                                                    <td>0</td>");
        in <<QString("                                                </tr>");
        in <<QString("                                            </table>");
        in <<QString("                </div>");
        in <<QString("            </div>");
        in <<QString("        </div>");
        in <<QString("        <div id=\"dogovir\">");
        in <<QString("            <div id=\"dogovir_left\">Вид цивільного проавового договору&nbsp&nbsp <span id=\"text_border10\">11111111</span>&nbsp&nbsp&nbsp&nbsp від </div>");
        in <<QString("            <div id=\"dogovir_right\">");
        in <<QString("                <div id=\"dogovir_right_left\">");
        in <<QString("                    <table border=\"1\" id=\"table_property\">");
        in <<QString("                        <tr>");
        in <<QString("                            <td>0</td>");
        in <<QString("                            <td>4</td>");
        in <<QString("                            <td>0</td>");
        in <<QString("                            <td>1</td>");
        in <<QString("                            <td>2</td>");
        in <<QString("                            <td>0</td>");
        in <<QString("                            <td>1</td>");
        in <<QString("                            <td>1</td>");
        in <<QString("                        </tr>");
        in <<QString("                    </table>");
        in <<QString("                </div> <span style=\"font-size:14px\">№</span>");
        in <<QString("                <div id=\"dogovir_right_right\">");
        in <<QString("                    <table border=\"1\" id=\"table_property\">");
        in <<QString("                        <tr>");
        in <<QString("                            <td>&nbsp&nbsp</td>");
        in <<QString("                            <td>&nbsp&nbsp</td>");
        in <<QString("                            <td>&nbsp&nbsp</td>");
        in <<QString("                            <td>&nbsp&nbsp</td>");
        in <<QString("                            <td>&nbsp&nbsp</td>");
        in <<QString("                            <td>&nbsp&nbsp</td>");
        in <<QString("                            <td>&nbsp&nbsp</td>");
        in <<QString("                    </table>");
        in <<QString("                </div>");
        in <<QString("            </div>");
        in <<QString("        </div>");
        in <<QString("        <p> Форма проведених розрахунків <span id=\"text_border10\">Готівковий розрахунок</span>");
        in <<QString("            <p>");
        in <<QString("                <div id=\"table\">");
        in <<QString("                    <table style=\"font-size:12px; border-collapse:collapse; text-align:center;\" ; border=1px;>");
        in <<QString("                        <tr>");
        in <<QString("                            <td rowspan=\"2\">Розділ</td>");
        in <<QString("                            <td rowspan=\"2\" width=\"20\">Дата відвантаження виконання, постачання</td>");
        in <<QString("                            <td rowspan=\"2\">Номенклатура постачання товарів/послуг продавця</td>");
        in <<QString("                            <td rowspan=\"2\">Одиниця виміру товару</td>");
        in <<QString("                            <td rowspan=\"2\">Кількість</td>");
        in <<QString("                            <td rowspan=\"2\" width=\"1\">Ціна постачання одиниці товару/послуги без урахування ПДВ</td>");
        in <<QString("                            <td colspan=\"4\">Обсяги постачання(база оподаткування) без урахування ПДВ що підлягають оподаткуванню за ставками</td>");
        in <<QString("                            <td rowspan=\"2\">Загальна сума коштів що підлягають оплаті</td>");
        in <<QString("                        </tr>");
        in <<QString("                        <tr>");
        in <<QString("                            <td>20%</td>");
        in <<QString("                            <td>0% (постач. на митній території України)</td>");
        in <<QString("                            <td>0% (експорт)</td>");
        in <<QString("                            <td>Звільнення від ПДВ **</td>");
        in <<QString("                        </tr>");
        in <<QString("                        <tr>");
        in <<QString("                            <td>1</td>");
        in <<QString("                            <td>2</td>");
        in <<QString("                            <td>3</td>");
        in <<QString("                            <td>4</td>");
        in <<QString("                            <td>5</td>");
        in <<QString("                            <td>6</td>");
        in <<QString("                            <td>7</td>");
        in <<QString("                            <td>8</td>");
        in <<QString("                            <td>9</td>");
        in <<QString("                            <td>10</td>");
        in <<QString("                            <td>11</td>");
        in <<QString("                        </tr>");
        in <<QString("                        <tr>");
        in <<QString("                            <td rowspan=\"3\">I</td>");
        in <<QString("                            <td rowspan=\"3\">01.01.11</td>");
        in <<QString("                            <td>Плуг к Мотоблоку ПН-1</td>");
        in <<QString("                            <td>штук</td>");
        in <<QString("                            <td>1.00</td>");
        in <<QString("                            <td>634.00</td>");
        in <<QString("                            <td>634.00</td>");
        in <<QString("                            <td></td>");
        in <<QString("                            <td></td>");
        in <<QString("                            <td></td>");
        in <<QString("                            <td></td>");
        in <<QString("                        </tr>");
        in <<QString("                        <tr>");
        in <<QString("                            <td>Мотоблок Мотор Січ 4.05</td>");
        in <<QString("                            <td>штук</td>");
        in <<QString("                            <td>1.00</td>");
        in <<QString("                            <td>9350.00</td>");
        in <<QString("                            <td>9350.00</td>");
        in <<QString("                            <td></td>");
        in <<QString("                            <td></td>");
        in <<QString("                            <td></td>");
        in <<QString("                            <td></td>");
        in <<QString("                        </tr>");
        in <<QString("                        <tr>");
        in <<QString("                            <td> Механізм поворотний до Мотоблока Мотор Січ 4.05</td>");
        in <<QString("                            <td>штук</td>");
        in <<QString("                            <td>1.00</td>");
        in <<QString("                            <td>418.00</td>");
        in <<QString("                            <td>418.00</td>");
        in <<QString("                            <td></td>");
        in <<QString("                            <td></td>");
        in <<QString("                            <td></td>");
        in <<QString("                            <td></td>");
        in <<QString("                        </tr>");
        in <<QString("                        <tr>");
        in <<QString("                            <tr>");
        in <<QString("                                <td></td>");
        in <<QString("                                <td colspan=\"2\">Усього по розділу I</td>");
        in <<QString("                                <td>X</td>");
        in <<QString("                                <td>X</td>");
        in <<QString("                                <td>X</td>");
        in <<QString("                                <td>10402.17</td>");
        in <<QString("                                <td></td>");
        in <<QString("                                <td></td>");
        in <<QString("                                <td></td>");
        in <<QString("                                <td>10402.17</td>");
        in <<QString("                            </tr>");
        in <<QString("                            <tr>");
        in <<QString("                                <td>II</td>");
        in <<QString("                                <td colspan=\"2\">Зворотня (заставна) тара</td>");
        in <<QString("                                <td>X</td>");
        in <<QString("                                <td>X</td>");
        in <<QString("                                <td>X</td>");
        in <<QString("                                <td>X</td>");
        in <<QString("                                <td>X</td>");
        in <<QString("                                <td>X</td>");
        in <<QString("                                <td>X</td>");
        in <<QString("                                <td></td>");
        in <<QString("                            </tr>");
        in <<QString("                            <tr>");
        in <<QString("                                <td>III</td>");
        in <<QString("                                <td colspan=\"2\">Податок на додану вартість</td>");
        in <<QString("                                <td>X</td>");
        in <<QString("                                <td>X</td>");
        in <<QString("                                <td>X</td>");
        in <<QString("                                <td>2080.43</td>");
        in <<QString("                                <td></td>");
        in <<QString("                                <td></td>");
        in <<QString("                                <td></td>");
        in <<QString("                                <td>2080.43</td>");
        in <<QString("                            </tr>");
        in <<QString("                            <tr>");
        in <<QString("                                <td>IV</td>");
        in <<QString("                                <td colspan=\"2\">Загальна сума з ПДВ</td>");
        in <<QString("                                <td>X</td>");
        in <<QString("                                <td>X</td>");
        in <<QString("                                <td>X</td>");
        in <<QString("                                <td>12482.60</td>");
        in <<QString("                                <td>X</td>");
        in <<QString("                                <td></td>");
        in <<QString("                                <td></td>");
        in <<QString("                                <td>12482.60</td>");
        in <<QString("                            </tr>");
        in <<QString("                    </table>");
        in <<QString("                </div>");
        in <<QString("                <p>Суми ПДВ нараховані(сплачені у звязку з постачанням товарів/послуг), зазначених у цій накладній, визначені правильно, відповідають сумі податкових зобовя`заннь продавця і включені до реєстру виданих та отриманих податкових накладних</p>");
        in <<QString("                <p>");
        in <<QString("                    <div id=\"podpis\">");
        in <<QString("                        <div id=\"podpis_left\" align=right><b>М.П</b></div>");
        in <<QString("                        <div id=\"podpis_right\"><span id=\"text_border\">&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbspА.М.Пастир</span></div>");
        in <<QString("                    </div> (*)Дата оплати ставиться у разі попередньої оплати постачання, на яку виписується податкова накладна, для операцій з постачання товарів/послуг відповідно до пункту 187.10 статті 187 розділу V Податкового кодексу України. </p>");
        in <<QString("                <p> (**)_____________________________________________________________________________________________________________________________________________</p>");
        in <<QString("                <p>(відповідні пункти (підпункти), статті, підрозділи, розділи Податкового кодексу України, якими передбачено звільнення від оподаткування)</p>");
        in <<QString("    </div>");
        in <<QString("</BODY>");
        in <<QString("</HTML>");

        QProcess::execute("cmd /c start firefox.exe \"file:///C:/Temp/test.html\"");




    }else if(ui->pushButton_6->isChecked()){


    }else{
        QMessageBox::information(this, "Увага", "");
    }
}






void MainWindow::on_pushButton_4_clicked()
{

}


