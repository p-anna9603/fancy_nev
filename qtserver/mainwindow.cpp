#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    qDebug()<< "Mainwindow konstruktor\n";
    ui->setupUi(this);
    //ezt kell minden új windowban a konstruktorba belerakni, meg a headerben lévőt:
    database= new DatabaseConnection();

    // hogy működjön a belépés enterrel is:     Klaudia liked your comment (szivekécsszeműsmiley)
    connect(ui->usernameLogin, SIGNAL(returnPressed()),ui->pushButton_2,SIGNAL(clicked()));
    connect(ui->passwordLogin, SIGNAL(returnPressed()),ui->pushButton_2,SIGNAL(clicked()));
}

MainWindow::~MainWindow()
{
    qDebug()<< "Destruktor\n";
    delete ui;
    QSqlDatabase::removeDatabase("QMYSQL");
    database->getDb().close();
}

void MainWindow::on_pushButton_2_clicked()  //Login Button
{
    ui->usernameLogin->setText("player");
    ui->passwordLogin->setText("player");
    QString username = ui->usernameLogin->text();
    QString password = ui->passwordLogin->text();

    // Messagebox ha vagy a felhasználónév vagy a jelszó mezőt üresen hagyta.
    if((username == "" || password == ""))
    {
         QMessageBox::information(this, "Please enter username and password", "Please enter username and password");
    }
    else
    {
        if(database->getDb().isOpen())
        {
            qDebug() << "pushbutton if ág";

            // QSqlQuery query(QSqlDatabase::database());
            QSqlQuery query(database->getDb());
            query.prepare(QString("SELECT * FROM Users WHERE username = :username AND password = :password"));
            query.bindValue(":username", username);
            query.bindValue(":password", password);
            if(!query.exec())
            {
                QMessageBox::information(this, "Failed", "Query Failed to execute");

            }
            else
            {
                if(query.size() == 0)
                {
                     QMessageBox::information(this, "Failed","Login Failed");
                }
                while(query.next())
                {
//                   QString usernameFromDB = query.value(0).toString();
//                   QString passwordFromDB = query.value(1).toString();

//                    if(usernameFromDB == username && passwordFromDB == password)
//                   {
                        //idegbajt kapok mégegyszer előugrik ez a szar
                        //QMessageBox::information(this, "Success", "Login Success");

                        if ((username=="adminKlaudia" || username=="adminVera" || username=="adminAnna") && password=="admin")   //admin---->AdminFelület
                        {
                            adminFelulet *testAdmin=new adminFelulet(this,username.replace("admin",""), database);

                            testAdmin->show();
                            //this->hide();
                            this->close();
                            ui->usernameLogin->setText("");
                            ui->passwordLogin->setText("");
                        }
                        else    //Sima User-->játékAblak
                        {
                            jatekFelulet *jatek = new jatekFelulet(this,username, database);
                            jatek->show();
                            this->close();
//                            Dialog dialog;
//                            dialog.setModal(true);
//                            dialog.exec();
                        }
//                   }
                }
            }
        }
        else
        {
            QMessageBox::information(this, "Not Connected", "Database not connected");
        }
    }
}

void MainWindow::on_regisztralasButton_clicked()
{
    QString firstName = ui->vnevReg->text();
    QString lastName = ui->knevReg->text();
    QString email = ui->emailReg->text();
    QString userName = ui->userNameReg->text();
    QString pass1 = ui->passwordReg->text();
    QString pass2 = ui->passwordReg2->text();

    if(email == "" || userName == "" || pass1 == "" || pass2 == "")
    {
        QMessageBox::information(this, "Missing data", "Please fill every field!");
    }
    else
    {
        if(database->getDb().isOpen())
        {
            qDebug() << "pushbutton if ág";

            QSqlQuery query(database->getDb());
            query.prepare(QString("SELECT * FROM Users WHERE username = :username"));
            query.bindValue(":username", userName);
            if(!query.exec())
            {
                QMessageBox::information(this, "Failed", "Query Failed to execute");

            }
            else
            {
                if(query.size() != 0)
                {
                     QMessageBox::information(this, "Már létező felhasználónév!", "Válassz másik felhasználó nevet!");
                }
                else
                {
                    if(pass1 != pass2)
                    {
                        QMessageBox::information(this,"Nem egyező jelszó", "Adj meg egyező jelszavakat!");
                    }
                    else
                    {
                        QSqlQuery queryInsert("INSERT INTO Users VALUES(:username,:password,:email,:firstname,:lastname)");
                    }
                }
            }
        }
        else
        {
            QMessageBox::information(this, "Not Connected", "Database not connected");
        }
    }
}
