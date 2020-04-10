#include "kategoriahozzaadasa.h"
#include "ui_kategoriahozzaadasa.h"

kategoriaHozzaadasa::kategoriaHozzaadasa(QWidget *parent,DatabaseConnection *db) :
    QMainWindow(parent),
    ui(new Ui::kategoriaHozzaadasa),
    db(db)
{
    ui->setupUi(this);
}

kategoriaHozzaadasa::~kategoriaHozzaadasa()
{
    delete ui;
}

void kategoriaHozzaadasa::on_pushButton_clicked()
{
    QString kategoria=ui->kategoriaNeveLineEdit->text();
    if (db->getDb().open())
    {
        QSqlQuery query(QSqlDatabase::database("MyConnect"));
        query.prepare(QString("INSERT INTO Category(category_name) VALUES (:category_name)"));
        query.bindValue(":category_name",kategoria);
        if (!query.exec())
             QMessageBox::information(this,"Error KategoriaHozzadasa","INSERT INTO Category(category_name) VALUES (:category_name) execution failed");
        else
             QMessageBox::information(this,"Success","Category added successfully");
    }
    else
        QMessageBox::information(this,"Error KategoriaHozzadasa","Database not open");
}
