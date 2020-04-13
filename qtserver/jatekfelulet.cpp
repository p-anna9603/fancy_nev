#include "jatekfelulet.h"
#include "ui_jatekfelulet.h"

jatekFelulet::jatekFelulet(QMainWindow *qMain, const QString &playerName, DatabaseConnection *db,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::jatekFelulet),
    db(db),
    playerName(playerName),
    vissza(qMain)
{
    ui->setupUi(this);
    ui->playerUsername->setText(playerName);
    ui->stackedWidget->hide();
//    ui->widget->hide();
//    ui->widget_2->hide();
//    ui->pontszamWidget->hide();
    ui->pontPush->hide();
    ui->KartyaPush->hide();
}

jatekFelulet::~jatekFelulet()
{
    delete ui;
}

void jatekFelulet::on_fiokomButton_clicked()
{
//    ui->pontszamWidget->hide();
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

                ui->stackedWidget->setCurrentIndex(1);
                ui->username->setText(playerName);
                ui->fullName->setText(userFullName);
                ui->email->setText(userEmail);
                ui->stackedWidget->show();

       /* #szarakodás
       //         adatok = new jatekosAdatok(this, playerName, userFullName, userEmail);
       //         ui->widget->show();
       //         this->layout()->addWidget(adatok);
        //                ui->widget_2->show();
        //                ui->widget->show();
        //                ui->username->setText(playerName);
        //                ui->fullname->setText(userFullName);
        //                ui->email->setText(userEmail);
        //                ui->widget->show();
        //                layout()->setAlignment(adatok, Qt::AlignCenter);
        */
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

void jatekFelulet::on_visszaButton_clicked()
{
    this->close();
    vissza->show();
}

void jatekFelulet::on_EredmenyButton_clicked()
{
    ui->stackedWidget->hide();
    ui->pontPush->show();
    ui->KartyaPush->show();
}

void jatekFelulet::on_pontPush_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);

    ui->pontPush->hide();
    ui->KartyaPush->hide();
    QString irodalom = "0", egyetem = "0", sport = "0", tortenelem = "0";
    QString info;
    int osszPontszam = 0;

    QSqlQuery query;
    query.prepare("SELECT category_id, points FROM Points WHERE username = :username");
    query.bindValue(":username", playerName);
    if(db->getDb().isOpen())
    {
        if(query.exec())
        {
            if(query.size() == 0)
            {
                info = "Még nincs pontod, irány játszani!";
                ui->osszpontszam->setText(info);
            }
            else
            {
                while(query.next())
                {
                    int id_fromDb = query.value(0).toInt();
                    int point_fromDb_INT = query.value(1).toInt();
                    QString point_fromDb_String = query.value(1).toString();
                    if(id_fromDb == 1)
                    {
                        tortenelem = point_fromDb_String;
                    }
                    else if(id_fromDb == 2)
                    {
                        irodalom = point_fromDb_String;
                    }
                    else if(id_fromDb == 3)
                    {
                        egyetem = point_fromDb_String;
                    }
                    else if(id_fromDb == 4)
                    {
                        sport = point_fromDb_String;
                    }
                    osszPontszam += point_fromDb_INT;
                    ui->osszpontszam->setText(QString::number(osszPontszam));
                }
            }
            ui->tortenelem->setText(tortenelem);
            ui->Idodalom->setText(irodalom);
            ui->sport->setText(sport);
            ui->egyetem->setText(egyetem);
        }
        else
        {
            QMessageBox::information(this, "Failed", "Query Failed to execute");
        }
    }
    else
    {
        QMessageBox::information(this, "Not Connected", "Database not connected");
    }
    ui->stackedWidget->show();
}

