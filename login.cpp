#include "login.h"
#include "ui_login.h"



login::login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
    settings = new QSettings(this);
    //Загрузить имя последнего пользователя

    ui->lineEdit_2->setText(settings->value("user", "root").toString());

    //Горячая клавиша Отмена=Esc
    keyCancel = new QShortcut(this);
    keyCancel->setKey(Qt::Key_Escape);
    connect(keyCancel, SIGNAL(activated()), this, SLOT(slotShortcutCancel()));


}

login::~login()
{
     delete ui;
}

//Функция Горячая клавиша Esc
void login::slotShortcutCancel()
{
    on_buttonBox_rejected();
}

//Выход из програмы по нажатию кнопки "Cancel"
void login::on_buttonBox_rejected()
{
    close();
    emit login_cancel();
}

//Подключение к базе по нажатию кнопки "ОК"
void login::on_buttonBox_accepted()
{
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("10.10.10.10");
    db.setDatabaseName("zbyt");

    db.setUserName(ui->lineEdit_2->text());
    db.setPassword("3482sql");
    if (!db.open()){
        ui->lineEdit->clear();
        db.close();
        qDebug() << db.lastError().text();
        errorloginMessage = new QMessageBox(this);
        errorloginMessage->setText(db.lastError().text());
        errorloginMessage->setWindowTitle("ERROR");
        errorloginMessage->setIcon(QMessageBox::Warning);
        errorloginMessage->exec();
    }
    else {
        qDebug() << "Подключение к базе данных открыто";

        //Сохранить имя пользователя
        settings->setValue("user", ui->lineEdit_2->text());
        close();
        // Создать и показать окно mainwindow
        ttn = new reestr_ttn;
        ttn->show();
    }

}

void login::on_lineEdit_returnPressed()
{
    on_buttonBox_accepted();
}
