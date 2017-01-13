#ifndef PRINT_TTN_H
#define PRINT_TTN_H

#include <QWidget>
#include <QDebug>
#include <QProcess>
#include <QTextStream>
#include <QFile>
#include <QSqlQuery>

namespace Ui {
class print_ttn;
}

class print_ttn : public QWidget
{
    Q_OBJECT

public:
    explicit print_ttn(QWidget *parent = 0);
    ~print_ttn();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void receiveData(int i, bool e);

private:
    Ui::print_ttn *ui;
    QFile *file;
    QSqlQuery *query;
    int index_table;
};

#endif // PRINT_TTN_H
