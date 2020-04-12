#include "jatekfelulet.h"
#include "ui_jatekfelulet.h"

jatekFelulet::jatekFelulet(const QString &playerName, DatabaseConnection *db,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::jatekFelulet),
    db(db),
    playerName(playerName)
{
    ui->setupUi(this);
    ui->playerUsername->setText(playerName);
}

jatekFelulet::~jatekFelulet()
{
    delete ui;
}

void jatekFelulet::on_pushButton_clicked()
{
    QString userFullName;
    QString userEmail;

    if(db->getDb().isOpen())
    {
        QSqlQuery query;
        query.prepare(QString("SELECT email, firstName, lastName FROM Users WHERE username = :username"));
        query.bindValue(":username", playerName);
        if(query.exec())
        {
            if(query.size() != 0)
            {
                while(query.next())
                {
                  userEmail = query.value(0).toString();
                  userFullName = query.value(1).toString() + " " + query.value(2).toString();
                  qDebug() << query.value(1).toString() + " " + query.value(2).toString();
                  qDebug() << query.value(0).toString();
                }
                qDebug() << query.value(1).toString() + " " + query.value(2).toString();
                qDebug() << query.value(0).toString();
                qDebug() << userFullName << " " << userEmail;
                jatekosAdatok *adatok = new jatekosAdatok(this, playerName, userFullName, userEmail);
                adatok->show();
                }
            else
            {
                QMessageBox::information(this, "Not foun player", "Player data not found.");
            }
         }
        else
        {
            QMessageBox::information(this, "Query fail", "Query failed to execute");
        }
    }
    else
    {
        QMessageBox::information(this, "Not Connected", "Database not connected");
    }
}
