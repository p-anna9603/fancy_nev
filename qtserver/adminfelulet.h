#ifndef ADMINFELULET_H
#define ADMINFELULET_H

#include <QMainWindow>
#include <QDebug>
//#include "mainwindow.h"
#include "databaseconnection.h"
#include "kerdeshozzaadasa.h"
#include <QWidget>
namespace Ui {
class adminFelulet;
}

class adminFelulet : public QMainWindow
{
    Q_OBJECT

public:
    explicit adminFelulet( QMainWindow *main,const QString& adminName="Unknown",DatabaseConnection *db = nullptr, QWidget *parent = nullptr);
    ~adminFelulet();
    QWidget *centralwidget = nullptr;

private slots:

    void on_buttonVissza_clicked();

    void on_buttonKerdesHozzaad_clicked();

private:
    Ui::adminFelulet *ui;
    QMainWindow *vissza;
    DatabaseConnection *db;

    kerdesHozzaadasa *kerdesWidget;

    //lehet így is - csak akkor szépen megkell szerkeszteni
    //kerdesHozzaadasa *kerdesWidget = new kerdesHozzaadasa(this,db);

};

#endif // ADMINFELULET_H
