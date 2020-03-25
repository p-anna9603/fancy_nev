#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //ezt kell minden új windowban a konstruktorba belerakni, meg a headerben lévőt:
    database= new DatabaseConnection();

    // hogy működjön a belépés enterrel is:
    connect(ui->usernameLogin, SIGNAL(returnPressed()),ui->pushButton_2,SIGNAL(clicked()));
    connect(ui->passwordLogin, SIGNAL(returnPressed()),ui->pushButton_2,SIGNAL(clicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete database;
}

void MainWindow::on_pushButton_clicked()    //db_Connection Button
{
    if(database->getDb().open())
    {
        QMessageBox::information(this,"Connection", "Database connected successfully");
    }
    else
    {
        QMessageBox::information(this, "Not Connected", "Database not connected");
    }

}

void MainWindow::on_pushButton_2_clicked()  //Login Button
{
    QString username = ui->usernameLogin->text();
    QString password = ui->passwordLogin->text();

    //majd megoldom valahogy hogy csekkolja ezeket is, ez most nem jó (forever loop)
//    while(username == "" || password =="")
//    {
//      QMessageBox::information(this, "Please enter username and password", "Please enter username and password");
//    }

    if(database->getDb().open())
    {
        QSqlQuery query(QSqlDatabase::database("MyConnect"));
        query.prepare(QString("SELECT * FROM Users WHERE username = :username AND password = :password"));
        query.bindValue(":username", username);
        query.bindValue(":password", password);
        if(!query.exec())
        {
            QMessageBox::information(this, "Failed", "Query Failed to execute");

        }
        else
        {
            while(query.next())
            {
                QString usernameFromDB = query.value(0).toString();
                QString passwordFromDB = query.value(1).toString();

                if(usernameFromDB == username && passwordFromDB == password)
                {
                    //idegbajt kapok mégegyszer előugrik ez a szar
                    //QMessageBox::information(this, "Success", "Login Success");
                    if ((username=="adminKlaudia" || username=="adminVera" || username=="adminAnna") && password=="admin")   //admin---->AdminFelület
                    {
                        adminFelulet *testAdmin=new adminFelulet(this,username);
                        testAdmin->show();
                        this->hide();
                        //ui->usernameLogin->setText("");
                        //ui->passwordLogin->setText("");
                    }
                    else    //Sima User-->játékAblak
                    {
                        Dialog dialog;
                        dialog.setModal(true);
                        dialog.exec();
                    }
                }
                else
                {
                    QMessageBox::information(this, "Failed","Login Failed");
                }
            }
        }
    }
    else
    {
        QMessageBox::information(this, "Not Connected", "Database not connected");
    }
}
