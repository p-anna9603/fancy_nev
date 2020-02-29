#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //ezt kell minden új windowban a konstruktorba belerakni, meg a headerben lévőt:
    database= DatabaseConnection();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    if(database.getDb().open())
    {
        QMessageBox::information(this,"Connection", "Database connected successfully");
    }
    else
    {
        QMessageBox::information(this, "Not Connected", "Database not connected");
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    QString username = ui->usernameLogin->text();
    QString password = ui->passwordLogin->text();

    if(database.getDb().open())
    {
//        QMessageBox::information(this,"Connection", "Database connected successfully");

        QSqlQuery query(QSqlDatabase::database("MyConnect"));
        query.prepare(QString("SELECT * FROM users WHERE username = :username AND password = :password"));

           query.bindValue(":username", username);
           query.bindValue(":password", password);

        if(!query.exec())
        {
            QMessageBox::information(this, "Failed", "Query Failed to execute");

        }else{
            while(query.next())
            {
                QString usernameFromDB = query.value(0).toString();
                QString passwordFromDB = query.value(1).toString();

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
