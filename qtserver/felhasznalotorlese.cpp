#include "felhasznalotorlese.h"
#include "ui_felhasznalotorlese.h"

felhasznaloTorlese::felhasznaloTorlese(QWidget *parent,DatabaseConnection *db) :
    QMainWindow(parent),
    ui(new Ui::felhasznaloTorlese),
    db(db)
{
    ui->setupUi(this);
}

felhasznaloTorlese::~felhasznaloTorlese()
{
    delete ui;
}

void felhasznaloTorlese::on_pushButton_clicked()
{
    QString fnev = ui->lineEdit->text();
        if (db->getDb().open())
        {
            QSqlQuery query(db->getDb());
            query.prepare(QString("SELECT * FROM Users WHERE username = :fnev"));
            query.bindValue(":fnev", fnev);
            if(!query.exec())
            {
                QMessageBox::information(this, "Failed", "Query Failed to execute");
            }
            else
            {
                if(query.size() == 0)
                {
                     QMessageBox::information(this,"Error felhasznaloTorlese","Nincs ilyen felhasználó!");
                }
                else
                {
                    QSqlQuery query(db->getDb());
                    query.prepare(QString("DELETE FROM Users WHERE username=:fnev"));
                    query.bindValue(":fnev",fnev);
                    if (!query.exec())
                    {
                        QMessageBox::information(this,"Error felhasznaloTorlese","DELETE FROM Users WHERE username=fnev execution failed");
                    }
                    else
                    {
                        QMessageBox::information(this,"Success","Felhasználó törölve!");
                        qDebug()<<fnev;
                    }
                }
            }
        }
        else
        {
            QMessageBox::information(this,"Error FelhasznaloTorlese","Database not open");
        }
}
