#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlError>
#include <QSqlRecord>
#include <QMessageBox>
#include <QSettings>
#include <QShortcut>
#include <mainwindow.h>

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

    };

#endif // LOGIN_H
