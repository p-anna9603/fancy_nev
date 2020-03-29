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
    //ui->kerdesWidget->setStyleSheet("background-color:white;");
    //ui->kerdesWidget->show();
    //ez a centralwidget-el megoldva, új ablakban
    // kerdesHozzaadasa *kerdesWidget = new kerdesHozzaadasa(centralwidget,db);

    //nullptr-el (szülő nélkül) új ablakban
    kerdesHozzaadasa *kerdesWidget = new kerdesHozzaadasa(nullptr,db);

    //lehet így is - csak akkor szépen megkell szerkeszteni (így nem új ablakban jelenik meg, hanem statikusan beépítve)
    //kerdesHozzaadasa *kerdesWidget = new kerdesHozzaadasa(this,db);

    kerdesWidget->show();



}
