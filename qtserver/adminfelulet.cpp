#include "adminfelulet.h"
#include "ui_adminfelulet.h"

adminFelulet::adminFelulet(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::adminFelulet)
{
    ui->setupUi(this);
}

adminFelulet::~adminFelulet()
{
    delete ui;
}
