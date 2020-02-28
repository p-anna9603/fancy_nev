#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("remotemysql.com");
    db.setUserName("GaZL22lGP6");
    db.setPassword("X5QBXJILeg");
    db.setDatabaseName("GaZL22lGP6");
    if(db.open())
    {
        QMessageBox::information(this,"Connection", "Database connected successfully");
    }
    else {
        QMessageBox::information(this, "Not Connected", "Database not connected");
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL", "MyConnect");
    db.setHostName("remotemysql.com");
    db.setUserName("GaZL22lGP6");
    db.setPassword("X5QBXJILeg");
    db.setDatabaseName("GaZL22lGP6");

    QString username = ui->usernameLogin->text();
    QString password = ui->passwordLogin->text();

    if(db.open())
    {
//        QMessageBox::information(this,"Connection", "Database connected successfully");

        QSqlQuery query(QSqlDatabase::database("MyConnect"));
        query.prepare(QString("SELECT * FROM Users WHERE Felhasználónév = :username AND Jelszó = :password"));

           query.bindValue(":username", username);
           query.bindValue(":password", password);

        if(!query.exec())
        {
            QMessageBox::information(this, "Failed", "Query Failed to execute");

        }else{
            while(query.next())
            {
                QString usernameFromDB = query.value(2).toString();
                QString passwordFromDB = query.value(3).toString();

                if(usernameFromDB == username && passwordFromDB == password)
                {
                    QMessageBox::information(this, "Success", "Login Success");

                    Dialog dialog;
                    dialog.setModal(true);
                    dialog.exec();
                }
                else
                {
                    QMessageBox::information(this, "Failed","Login Failed");
                }
            }
        }
    }
    else {
        QMessageBox::information(this, "Not Connected", "Database not connected");
    }
}
