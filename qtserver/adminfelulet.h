#ifndef ADMINFELULET_H
#define ADMINFELULET_H

#include <QMainWindow>
#include <QDebug>
#include "mainwindow.h"
#include "databaseconnection.h"

namespace Ui {
class adminFelulet;
}

class adminFelulet : public QMainWindow
{
    Q_OBJECT

public:
    explicit adminFelulet( QMainWindow *main,const QString& adminName="Unknown",QWidget *parent = nullptr);
    ~adminFelulet();

private slots:

    void on_buttonVissza_clicked();

    void on_buttonKerdesHozzaad_clicked();

private:
    Ui::adminFelulet *ui;
    QMainWindow *vissza;
};

#endif // ADMINFELULET_H
