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
//    ui->stackedWidget->hide();
    ui->stackedWidget->setCurrentIndex(5); // üres stacked Widget hogy ne csússzon el a layout
//    ui->widget->hide();
//    ui->widget_2->hide();
//    ui->pontszamWidget->hide();
    ui->pontPush->hide();
    ui->KartyaPush->hide();
    ui->kartya_vasarlas->hide();

    // Adott képre (QLabel) lehessen kattintani. (lsd: clickableLabel)
    connect(ui->term1, SIGNAL(Mouse_Pressed()), this, SLOT(Mouse_Pressed()));
    connect(ui->t3_8, SIGNAL(Mouse_PressedOnLittlePic()), this, SLOT(Mouse_PressedOnLittlePic()));
    connect(ui->t3_1, SIGNAL(Mouse_PressedOnLittlePic()), this, SLOT(Mouse_PressedOnLittlePic()));
    connect(ui->t3_2, SIGNAL(Mouse_PressedOnLittlePic()), this, SLOT(Mouse_PressedOnLittlePic()));
    connect(ui->t3_3, SIGNAL(Mouse_PressedOnLittlePic()), this, SLOT(Mouse_PressedOnLittlePic()));
    connect(ui->t3_4, SIGNAL(Mouse_PressedOnLittlePic()), this, SLOT(Mouse_PressedOnLittlePic()));
    connect(ui->t3_5, SIGNAL(Mouse_PressedOnLittlePic()), this, SLOT(Mouse_PressedOnLittlePic()));
    connect(ui->t3_6, SIGNAL(Mouse_PressedOnLittlePic()), this, SLOT(Mouse_PressedOnLittlePic()));
    connect(ui->t3_7, SIGNAL(Mouse_PressedOnLittlePic()), this, SLOT(Mouse_PressedOnLittlePic()));
    connect(ui->t3_9, SIGNAL(Mouse_PressedOnLittlePic()), this, SLOT(Mouse_PressedOnLittlePic()));
}

jatekFelulet::~jatekFelulet()
{
    delete ui;
}

void jatekFelulet::on_fiokomButton_clicked()
{
    ui->pontPush->hide();
    ui->KartyaPush->hide();
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

                ui->stackedWidget->setCurrentIndex(2);
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
    ui->stackedWidget->setCurrentIndex(5); // üres stacked Widget hogy ne csússzon el a layout
    ui->pontPush->show();
    ui->KartyaPush->show();
    ui->kartya_vasarlas->show();
}

void jatekFelulet::on_pontPush_clicked() // Pontszámaim
{
    ui->stackedWidget->setCurrentIndex(0);
    ui->pontPush->hide();
    ui->KartyaPush->hide();
    ui->kartya_vasarlas->hide();
    getPoints();
    ui->stackedWidget->show();
}


void jatekFelulet::on_KartyaPush_clicked() // Eredményeim --> Kártyák
{
    ui->stackedWidget->setCurrentIndex(1);
    ui->pontPush->hide();
    ui->KartyaPush->hide();
    ui->kartya_vasarlas->hide();
    ui->stackedWidget->show();
}

void jatekFelulet::on_pushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
    ui->pontPush->hide();
    ui->KartyaPush->hide();
    ui->kartya_vasarlas->hide();
    ui->stackedWidget->show();
}

void jatekFelulet::Mouse_Pressed()
{
    qDebug() << "Klikk!";
    term = new termeszetiKepek();
    term->show();
}

void jatekFelulet::Mouse_PressedOnLittlePic()
{ // ez az egész szar fos nem működik mert nem adja át paraméterben a termeszetikepek osztálynak hiába van feltöltve a vektor
    qDebug()<<"Klikkelés kisképre!";
    if(ui->t3_8->hasFocus())
    {
      qDebug()<< "Beugrik 8-ba";
//      term->setKisKepLista("t8_3");
      kisKepekLista.push_back("t3_8");
      qDebug()<<"Klikkelés 8.  kisképre!";
    }
    else if(ui->t3_5->hasFocus())
    {
      qDebug()<< "Beugrik 5-ba";
      kisKepekLista.push_back("t3_5");
      qDebug()<<"Klikkelés 5. kisképre!";
    }
    else if(ui->t3_2->hasFocus())
    {
      qDebug()<< "Beugrik 2-ba";
      kisKepekLista.push_back("t3_2");
      qDebug()<<"Klikkelés 2. kisképre!";
    }
    else if(ui->t3_7->hasFocus())
    {
      qDebug()<< "Beugrik 7-ba";
      kisKepekLista.push_back("t3_7");
      qDebug()<<"Klikkelés 7. kisképre!";
    }
    else if(ui->t3_1->hasFocus())
    {
      qDebug()<< "Beugrik 1-ba";
      kisKepekLista.push_back("t3_1");
      qDebug()<<"Klikkelés 1. kisképre!";
    }
    else if(ui->t3_9->hasFocus())
    {
      qDebug()<< "Beugrik 9-ba";
      kisKepekLista.push_back("t3_9");
      qDebug()<<"Klikkelés 9. kisképre!";
    }
    else if(ui->t3_4->hasFocus())
    {
      qDebug()<< "Beugrik 4-ba";
      kisKepekLista.push_back("t3_4");
      qDebug()<<"Klikkelés 4. kisképre!";
    }
    else if(ui->t3_3->hasFocus())
    {
      qDebug()<< "Beugrik 3-ba";
      kisKepekLista.push_back("t3_3");
      qDebug()<<"Klikkelés 3. kisképre!";
    }
//    term->setKisKepLista("t3_3"); /6 ez nem jó mert a vector valamiért nem inicializálódik jól és nem adja hozzá...
//    term->setKisKepLista("t3_9");
//    term->setKisKepLista("t3_4");
//    term->setKisKepLista("t3_2");
//    term->setKisKepLista("t3_6");
//    term->setKisKepLista("t3_1");
//    term->setKisKepLista("t3_7");
}

void jatekFelulet::on_pushButton_4_clicked()    //START
{
    ui->stackedWidget->setCurrentIndex(4);
    ui->stackedWidget->show();
/*
    QuizFelulet *kvizfelulet=new QuizFelulet(nullptr,db);
    this->hide();
    kvizfelulet->show();*/
}

void jatekFelulet::on_tortenelemTema_clicked()
{
    kerdesId = 1;
    QuizFelulet *kvizfelulet=new QuizFelulet(this,db, kerdesId, playerName);
    this->hide();
    kvizfelulet->show();
}

void jatekFelulet::on_irodalomTema_clicked()
{
    kerdesId = 2;
    QuizFelulet *kvizfelulet=new QuizFelulet(this,db, kerdesId, playerName);
    this->hide();
    kvizfelulet->show();
}

void jatekFelulet::on_egyetemTema_clicked()
{
    kerdesId = 3;
    QuizFelulet *kvizfelulet=new QuizFelulet(this,db, kerdesId, playerName);
    this->hide();
    kvizfelulet->show();
}

void jatekFelulet::on_sportTema_clicked()
{
    kerdesId = 4;
    QuizFelulet *kvizfelulet=new QuizFelulet(this,db, kerdesId, playerName);
    this->hide();
    kvizfelulet->show();
}

void jatekFelulet::on_jatekrolButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(6);
    ui->stackedWidget->show();
}

void jatekFelulet::on_kartya_vasarlas_clicked()
{
    ui->stackedWidget->setCurrentIndex(7);
    ui->pontPush->hide();
    ui->KartyaPush->hide();
    ui->kartya_vasarlas->hide();
    ui->stackedWidget->show();
    getPoints();
    ui->jelenlegi_pont->setText(QString::number(osszPontszam));
}

void jatekFelulet::getPoints()
{
    QString irodalom = "0", egyetem = "0", sport = "0", tortenelem = "0";
    QString info;
    osszPontszam = 0;
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
}

vector<QString> jatekFelulet::getKisKepLista()
{
    return kisKepekLista;
}
