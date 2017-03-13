#include "login.h"
#include "ui_login.h"



login::login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);

    logFile = new QFile;
    logFile->setFileName("./log.txt");
    logFile->open(QIODevice::WriteOnly | QIODevice::Append);
    log.setCodec("UTF-8");
    log.setDevice(logFile);


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
    db.setHostName("46.200.74.194");
    db.setDatabaseName("zbyt");

    db.setUserName(ui->lineEdit_2->text());

    db.setPassword("3482sql");
    if (!db.open()){
        ui->lineEdit->clear();
        db.close();

        log << QDateTime::currentDateTime().toString("dd/mm/yy hh:mm:ss  ")<< QString(db.lastError().text())<<endl;
        qDebug() << db.lastError().text();

        errorloginMessage = new QMessageBox(this);
        errorloginMessage->setText(db.lastError().text());
        errorloginMessage->setWindowTitle("ERROR");
        errorloginMessage->setIcon(QMessageBox::Warning);
        errorloginMessage->exec();
    }
    else {
        // Кодировка в Windows-1251
        query = new QSqlQuery;
        query->exec("SET NAMES cp1251");
        query->exec("SET CHARACTER SET 'cp1251'");

        log << QDateTime::currentDateTime().toString("dd/mm/yy hh:mm:ss  ") << QString("Подключение к базе данных открыто") << endl;
        qDebug() << "Подключение к базе данных открыто";

        //Сохранить имя пользователя
        settings->setValue("user", ui->lineEdit_2->text());
        close();
        // Создать и показать окно mainwindow
        mainwindow = new MainWindow;
        mainwindow->show();
      //  mainwindow->showMaximized();
    }

}

void login::on_lineEdit_returnPressed()
{
    on_buttonBox_accepted();
}
