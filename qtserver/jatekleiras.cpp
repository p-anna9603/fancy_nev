#include "jatekleiras.h"
#include "ui_jatekleiras.h"

jatekLeiras::jatekLeiras(QWidget *parent, DatabaseConnection *db):
    QMainWindow(parent),
    ui(new Ui::jatekLeiras),
    db(db)
{
    ui->setupUi(this);
    ui->textEdit->setPlainText(beolvasas());
}

jatekLeiras::~jatekLeiras()
{
    delete ui;
    delete db;
}

QString jatekLeiras::beolvasas() const
{
    QString data;
    QString fileName(":/resource/txt/jatekLeiras.txt");

    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly)) {
        qDebug()<<"file not opened"<<endl;
    }
    else
    {
        qDebug()<<"file opened"<<endl;
        data = file.readAll();
    }

    file.close();
    return data;
}
