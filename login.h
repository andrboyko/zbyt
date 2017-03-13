#ifndef LOGIN_H
#define LOGIN_H

/*Локальные, пользовательские классы*/
#include "mainwindow.h"

/*Стандартные классы Qt*/
#include <QWidget>
#include <QDebug>
#include <QMessageBox>
#include <QShortcut>
#include <QFile>
#include <QDateTime>

#include <QSettings>

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QTextStream>

namespace Ui {
class login;
}

class login : public QWidget
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = 0);
    ~login();

private slots:


void on_buttonBox_rejected();
void on_buttonBox_accepted();
void slotShortcutCancel();

void on_lineEdit_returnPressed();

signals:
void login_cancel();


private:
    Ui::login *ui;
    QSqlDatabase db;
    QMessageBox *errorloginMessage;
    QSettings *settings;
    QShortcut *keyCancel;
    MainWindow *mainwindow;
    QSqlQuery *query;
    QFile *logFile;
    QTextStream log;



    };

#endif // LOGIN_H
