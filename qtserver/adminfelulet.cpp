#include "adminfelulet.h"
#include "ui_adminfelulet.h"

//adminFelulet::adminFelulet(QMainWindow *qMain, const QString &adminName, QWidget *parent) :
//    QMainWindow(parent),
//    ui(new Ui::adminFelulet),
//    vissza(qMain)
//{
//    ui->setupUi(this);
//    ui->adminUsername->setText(adminName);
//    ui->kerdesWidget->hide();
//}
adminFelulet::adminFelulet(QMainWindow *qMain, const QString &adminName, DatabaseConnection *db, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::adminFelulet),
    vissza(qMain),
    db(db)
{
         qDebug()<<"admin konstruktor \n";
    ui->setupUi(this);
    ui->adminUsername->setText(adminName);
}

adminFelulet::~adminFelulet()
{
    delete ui;
}


void adminFelulet::on_buttonVissza_clicked()
{
    //this->hide();
    this->close();
    vissza->show();
}

void adminFelulet::on_buttonKerdesHozzaad_clicked()
{
         qDebug()<<" kerdes hozzaad button \n";
    //ui->kerdesWidget->setStyleSheet("background-color:white;");
    //ui->kerdesWidget->show();
    kerdesHozzaadasa *kerdesWidget = new kerdesHozzaadasa(centralwidget,db);
    kerdesWidget->show();


}
