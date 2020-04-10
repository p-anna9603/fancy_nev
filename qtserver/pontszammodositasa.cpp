#include "pontszammodositasa.h"
#include "ui_pontszammodositasa.h"

pontszamModositasa::pontszamModositasa(QWidget *parent, DatabaseConnection *db) :
    QMainWindow(parent),
    ui(new Ui::pontszamModositasa),
    db(db)
{
    ui->setupUi(this);
}

pontszamModositasa::~pontszamModositasa()
{
    delete ui;
    delete db;
}

void pontszamModositasa::on_mehetGomb_clicked()
{
    QString username = ui->felhasznaloNevLineEdit->text();
    QString category_name=ui->temakorLineEdit->text();
    int points=(ui->modositottPontszamLineEdit->text()).toInt();
    if(db->getDb().open())
    {
        QSqlQuery query(QSqlDatabase::database("MyConnect"));
        query.prepare(QString("SELECT id FROM Category WHERE category_name=:category_name"));
        query.bindValue(":category_name",category_name);
        int category_id=0;
        if (query.exec())
        {
            query.next();
            category_id=(query.value(0).toString().toInt());
        }
        else
            QMessageBox::information(this,"Failed Pontszammodositas","SELECT id FROM Category WHERE category_name=:category_name failed to execute");

        query.prepare(QString("UPDATE Points SET points=:ertek WHERE username=:nev AND category_id=:id"));
        query.bindValue(":ertek", points);
        query.bindValue(":nev", username);
        query.bindValue(":id", category_id);
        if(!query.exec())
            QMessageBox::information(this,"Failed Pontszammodositas","UPDATE Points SET points=:ertek WHERE username=:nev AND category_id=:id Failed to execute");
        else
        {
            if (query.numRowsAffected()!=1)
                QMessageBox::information(this,"Failed Pontszammodositas","No rows affected");
            else
                QMessageBox::information(this,"Success","OK");
        }
    }
    else
        QMessageBox::information(this,"Failed Pontszammodositas","Database is not open");
}
