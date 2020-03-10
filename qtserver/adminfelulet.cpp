#include "adminfelulet.h"
#include "ui_adminfelulet.h"
#include "kerdeshozzaadasa.h"

adminFelulet::adminFelulet(QMainWindow *qMain, const QString &adminName, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::adminFelulet),
    vissza(qMain)
{
    ui->setupUi(this);
    ui->adminUsername->setText(adminName);
    ui->kerdesWidget->hide();
}

adminFelulet::~adminFelulet()
{
    delete ui;
}


void adminFelulet::on_buttonVissza_clicked()
{
    this->hide();
    vissza->show();
}

void adminFelulet::on_buttonKerdesHozzaad_clicked()
{
    //ui->kerdesWidget->setStyleSheet("background-color:white;");
    ui->kerdesWidget->show();
}
