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
   term = new termeszetiKepek();
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

    connect(ui->buttonKep1_2, SIGNAL(Mouse_PressedOnBuyingPic()), this, SLOT(Mouse_PressedOnBuyingPic()));
    connect(ui->buttonKep2_2, SIGNAL(Mouse_PressedOnBuyingPic()), this, SLOT(Mouse_PressedOnBuyingPic()));
    connect(ui->buttonKep3_2, SIGNAL(Mouse_PressedOnBuyingPic()), this, SLOT(Mouse_PressedOnBuyingPic()));
    connect(ui->buttonKep4_2, SIGNAL(Mouse_PressedOnBuyingPic()), this, SLOT(Mouse_PressedOnBuyingPic()));
    //connect(ui->buttonKep5_2, SIGNAL(Mouse_PressedOnBuyingPic()), this, SLOT(Mouse_PressedOnBuyingPic()));
    connect(ui->buttonKep6_2, SIGNAL(Mouse_PressedOnBuyingPic()), this, SLOT(Mouse_PressedOnBuyingPic()));
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
//    ui->stackedWidget->setCurrentIndex(5); // üres stacked Widget hogy ne csússzon el a layout
//    ui->pontPush->show();
//    ui->KartyaPush->show();
//    ui->kartya_vasarlas->show();
    ui->stackedWidget->setCurrentIndex(0);
    ui->pontPush->hide();
    ui->KartyaPush->hide();
    ui->kartya_vasarlas->hide();
    getPoints();
    ui->stackedWidget->show();
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

void jatekFelulet::on_pushButton_clicked() //természeti kártya pusbutton
{
    ui->stackedWidget->setCurrentIndex(3);
    ui->pontPush->hide();
    ui->KartyaPush->hide();
    ui->kartya_vasarlas->hide();
    ui->stackedWidget->show();
    getPoints();
    ui->pontszam->setText(QString::number(osszPontszam));
}

void jatekFelulet::Mouse_Pressed()
{
    qDebug() << "Klikk!";
//    term = new Ui::termeszetiKepek();
    term->show();
}

void jatekFelulet::Mouse_PressedOnLittlePic()
{
    qDebug()<<"Klikkelés kisképre!";
    if(ui->t3_8->hasFocus())
    {
      qDebug()<< "Beugrik 8-ba";
      term->setKisKepLista("image_part_008.jpg");
//      kisKepekLista.push_back("t3_8");
      qDebug()<<"Klikkelés 8.  kisképre!";
    }
    else if(ui->t3_5->hasFocus())
    {
      qDebug()<< "Beugrik 5-ba";
      term->setKisKepLista("image_part_005.jpg");
      qDebug()<<"Klikkelés 5. kisképre!";
    }
    else if(ui->t3_2->hasFocus())
    {
      qDebug()<< "Beugrik 2-ba";
      term->setKisKepLista("image_part_002.jpg");;
      qDebug()<<"Klikkelés 2. kisképre!";
    }
    else if(ui->t3_7->hasFocus())
    {
      qDebug()<< "Beugrik 7-ba";
      term->setKisKepLista("image_part_007.jpg");
      qDebug()<<"Klikkelés 7. kisképre!";
    }
    else if(ui->t3_1->hasFocus())
    {
      qDebug()<< "Beugrik 3-ba";
      term->setKisKepLista("image_part_003.jpg");
      qDebug()<<"Klikkelés 1. kisképre!";
    }
    else if(ui->t3_9->hasFocus())
    {
      qDebug()<< "Beugrik 9-ba";
      term->setKisKepLista("image_part_009.jpg");
      qDebug()<<"Klikkelés 9. kisképre!";
    }
    else if(ui->t3_4->hasFocus())
    {
      qDebug()<< "Beugrik 4-ba";
      term->setKisKepLista("image_part_004.jpg");
      qDebug()<<"Klikkelés 4. kisképre!";
    }
    else if(ui->t3_3->hasFocus())
    {
      qDebug()<< "Beugrik 3-ba";
      term->setKisKepLista("image_part_003");
      qDebug()<<"Klikkelés 3. kisképre!";
    }
}

void jatekFelulet::Mouse_PressedOnBuyingPic() // hogy ne minden buttonra kelljen külön függvény
{
    int answer;
    getPoints(); // hogy a pontokat beállítsuk
    if(kartyaTema == 1) // épp a történelmi kártyáknál van
    {
        if(tortenelemPont > 400)
        {
            answer = getAnswerForBuying();
            if(answer == 1)
            {
                if(ui->buttonKep1_2->hasFocus())
                {
                    QPixmap pix1(":resource/img/TortenelmiKartya/h1.jpg");
                    ui->term1->setPixmap(pix1);
                    updatePoints();
                }
                else if(ui->buttonKep2_2->hasFocus())
                {
                    QPixmap pix1(":resource/img/TortenelmiKartya/h2.jpg");
                    ui->term1->setPixmap(pix1);
                    updatePoints();
                }
                else if(ui->buttonKep3_2->hasFocus()) // nem látja ???
                {
                    QPixmap pix1(":resource/img/TortenelmiKartya/h4.jpg");
                    ui->term1->setPixmap(pix1);
                    updatePoints();
                }
                else if(ui->buttonKep4_2->hasFocus())
                {
                    QPixmap pix1(":resource/img/TortenelmiKartya/h7.jpg");
                    ui->term1->setPixmap(pix1);
                    updatePoints();
                }
                //else if(ui->buttonKep5_2->hasFocus())
                {
                    QPixmap pix1(":resource/img/TortenelmiKartya/h5.jpg");
                    ui->term1->setPixmap(pix1);
                    updatePoints();
                }
                //else if(ui->buttonKep6_2->hasFocus())
                {
                    QPixmap pix1(":resource/img/TortenelmiKartya/h3.jpg");
                    ui->term1->setPixmap(pix1);
                    updatePoints();
                }
                tortenelemPont -= 400;
                ui->jelenlegi_pont_2->setText(QString::number(tortenelemPont));
            }
        }
        else
        {
            QMessageBox::information(this,"Nincs egyenleg","Nincs elegendő pontod a vásárlás teljesítéséhez.");

        }
    }
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
            tortenelemPont = tortenelem.toInt();
            irodalomPont = irodalom.toInt();
            sportPont = sport.toInt();
            egyetemPont = egyetem.toInt();
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

int jatekFelulet::getAnswerForBuying()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this,"Vásárlás","Biztos meg akarod venni?",QMessageBox::Yes|QMessageBox::No);
    if(reply == QMessageBox::Yes)
    {
        QMessageBox::information(this,"Vásárlás megtörtént","Vásárlás megtörtént, tiéd a kép.");
        return 1;
    }
    else{
       return 0;
    }
}

void jatekFelulet::updatePoints()
{
    if(kartyaTema == 1) // történelmi kártyát vett --> pontok frissítése db-ben
    {
        QSqlQuery query;
        query.prepare("UPDATE Points SET points = :points WHERE category_id = 1");
        query.bindValue(":ponints", tortenelemPont);
        if(!query.exec())
        {
            QMessageBox::information(this,"Sikertelen", "Sikertelen beszúrás adatbázisba");
        }
    }
}

void jatekFelulet::on_buttonKep1_clicked()
{
    if(osszPontszam - 400 >= 0)
    {
        int answer = getAnswerForBuying();
        if(answer == 1)
        {
            QPixmap pix1(":resource/img/Termeszeti/Kicsiben/szurkeben/t3.jpg");
            ui->term1->setPixmap(pix1);
            updatePoints();
        }
    }
    else
    {
        QMessageBox::information(this,"Nincs egyenleg","Nincs elegendő pontod a vásárlás teljesítéséhez.");
    }
}

void jatekFelulet::on_buttonKep2_clicked()
{
    if(osszPontszam - 400 >= 0)
    {
        int answer = getAnswerForBuying();
        if(answer == 1)
        {
            QPixmap pix1(":resource/img/Termeszeti/Kicsiben/szurkeben/háttér4.jpg");
            ui->term1->setPixmap(pix1);
        }
    }
    else
    {
        QMessageBox::information(this,"Nincs egyenleg","Nincs elegendő pontod a vásárlás teljesítéséhez.");
    }
}

void jatekFelulet::on_buttonKep3_clicked()
{
    if(osszPontszam - 400 >= 0)
    {
        int answer = getAnswerForBuying();
        if(answer == 1)
        {
            QPixmap pix1(":resource/img/Termeszeti/Kicsiben/szurkeben/háttér3.jpg");
            ui->term1->setPixmap(pix1);
        }
    }
    else
    {
        QMessageBox::information(this,"Nincs egyenleg","Nincs elegendő pontod a vásárlás teljesítéséhez.");
    }
}

void jatekFelulet::on_buttonKep4_clicked()
{
    if(osszPontszam - 400 >= 0)
    {
        int answer = getAnswerForBuying();
        if(answer == 1)
        {
            QPixmap pix1(":resource/img/Termeszeti/Kicsiben/szurkeben/t1.jpg");
            ui->term1->setPixmap(pix1);
        }
    }
    else
    {
        QMessageBox::information(this,"Nincs egyenleg","Nincs elegendő pontod a vásárlás teljesítéséhez.");
    }
}

void jatekFelulet::on_buttonKep5_clicked()
{
    if(osszPontszam - 400 >= 0)
    {
        int answer = getAnswerForBuying();
        if(answer == 1)
        {
            QPixmap pix1(":resource/img/Termeszeti/Kicsiben/szurkeben/t2.jpg");
            ui->term1->setPixmap(pix1);
        }
    }
    else
    {
        QMessageBox::information(this,"Nincs egyenleg","Nincs elegendő pontod a vásárlás teljesítéséhez.");
    }
}

void jatekFelulet::on_buttonKep6_clicked()
{
    if(osszPontszam - 400 >= 0)
    {
        int answer = getAnswerForBuying();
        if(answer == 1)
        {
            QPixmap pix1(":resource/img/Termeszeti/Kicsiben/szurkeben/háttér2.jpg");
            ui->term1->setPixmap(pix1);
        }
    }
    else{
        QMessageBox::information(this,"Nincs egyenleg","Nincs elegendő pontod a vásárlás teljesítéséhez.");
    }
}

void jatekFelulet::on_buttonKep7_clicked()
{
    if(osszPontszam - 400 >= 0)
    {
        int answer = getAnswerForBuying();
        if(answer == 1)
        {
            QPixmap pix1(":resource/img/Termeszeti/Kicsiben/szurkeben/t5.jpg");
            ui->term1->setPixmap(pix1);
        }
    }
    else
    {
        QMessageBox::information(this,"Nincs egyenleg","Nincs elegendő pontod a vásárlás teljesítéséhez.");
    }
}

void jatekFelulet::on_kartyavasarlas_pushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    ui->pontPush->hide();
    ui->KartyaPush->hide();
    ui->kartya_vasarlas->hide();
    ui->stackedWidget->show();
}

void jatekFelulet::on_tortnelmiKartyaTema_clicked()
{
    kartyaTema = 1; // tortenelmi
    ui->stackedWidget->setCurrentIndex(8);
    ui->pontPush->hide();
    ui->KartyaPush->hide();
    ui->kartya_vasarlas->hide();
    ui->stackedWidget->show();
    getPoints();
    ui->jelenlegi_pont_2->setText(QString::number(tortenelemPont));
}
