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

    setVoltakKepek();
    // Természeti képek buttonjainak kattintása
    connect(ui->buttonKep1, SIGNAL(Mouse_PressedOnBuyingPic()), this, SLOT(Mouse_PressedOnBuyingPic()));
    connect(ui->buttonKep2, SIGNAL(Mouse_PressedOnBuyingPic()), this, SLOT(Mouse_PressedOnBuyingPic()));
    connect(ui->buttonKep7, SIGNAL(Mouse_PressedOnBuyingPic()), this, SLOT(Mouse_PressedOnBuyingPic()));
    connect(ui->buttonKep4, SIGNAL(Mouse_PressedOnBuyingPic()), this, SLOT(Mouse_PressedOnBuyingPic()));
    connect(ui->buttonKep5, SIGNAL(Mouse_PressedOnBuyingPic()), this, SLOT(Mouse_PressedOnBuyingPic()));
    connect(ui->buttonKep6, SIGNAL(Mouse_PressedOnBuyingPic()), this, SLOT(Mouse_PressedOnBuyingPic()));

    // Történelmi képek buttonjainak kattintása
    connect(ui->buttonKep1_2, SIGNAL(Mouse_PressedOnBuyingPic()), this, SLOT(Mouse_PressedOnBuyingPic()));
    connect(ui->buttonKep2_2, SIGNAL(Mouse_PressedOnBuyingPic()), this, SLOT(Mouse_PressedOnBuyingPic()));
    connect(ui->buttonKep3_2, SIGNAL(Mouse_PressedOnBuyingPic()), this, SLOT(Mouse_PressedOnBuyingPic()));
    connect(ui->buttonKep4_2, SIGNAL(Mouse_PressedOnBuyingPic()), this, SLOT(Mouse_PressedOnBuyingPic()));
    connect(ui->buttonKep5_2, SIGNAL(Mouse_PressedOnBuyingPic()), this, SLOT(Mouse_PressedOnBuyingPic()));
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
                }
            else
            {
                QMessageBox::information(this, "Not found player", "Player data not found.");
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

void jatekFelulet::Mouse_PressedOnBuyingPic() // hogy ne minden buttonra kelljen külön függvény //
{
    int answer;
    qDebug()<< "itt van mouse pressben";
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
                    qDebug()<< "itt van mouse pressben az első képnél";
                    QPixmap pix1(":resource/img/TortenelmiKartya/h1.jpg");
                    ui->tort1->setPixmap(pix1);
                    ui->buttonKep1_2->hide();
                    addImageToDb("h1");
                     ui->buttonKep1_2->hide();
                }
                else if(ui->buttonKep2_2->hasFocus())
                {
                    QPixmap pix1(":resource/img/TortenelmiKartya/h2.jpg");
                    ui->tort2->setPixmap(pix1);
                    addImageToDb("h2");
                    ui->buttonKep2_2->hide();
                }
                else if(ui->buttonKep3_2->hasFocus())
                {
                    QPixmap pix1(":resource/img/TortenelmiKartya/h4.jpg");
                    ui->tort3->setPixmap(pix1);
                    addImageToDb("h4");
                    ui->buttonKep3_2->hide();
                }
                else if(ui->buttonKep4_2->hasFocus())
                {
                    QPixmap pix1(":resource/img/TortenelmiKartya/h7.jpg");
                    ui->tort4->setPixmap(pix1);
                    addImageToDb("h7");
                    ui->buttonKep4_2->hide();
                }
                else if(ui->buttonKep5_2->hasFocus())
                {
                    QPixmap pix1(":resource/img/TortenelmiKartya/h5.jpg");
                    ui->term1->setPixmap(pix1);
                    addImageToDb("h5");
                    ui->buttonKep5_2->hide();
                }
                else if(ui->buttonKep6_2->hasFocus())
                {
                    QPixmap pix1(":resource/img/TortenelmiKartya/h3.jpg");
                    ui->tort6->setPixmap(pix1);
                    addImageToDb("h3");
                    ui->buttonKep6_2->hide();
                }
                tortenelemPont -= 400;
                ui->jelenlegi_pont_2->setText(QString::number(tortenelemPont));
                updatePoints();
            }
        }
        else
        {
            QMessageBox::information(this,"Nincs egyenleg","Nincs elegendő pontod a vásárlás teljesítéséhez.");

        }
    }

    if(kartyaTema == 2) // épp a természeti kártyáknál van
    {
        if(sportPont > 400)
        {
            answer = getAnswerForBuying();
            if(answer == 1)
            {
                if(ui->buttonKep1->hasFocus())
                {
                    qDebug()<< "itt van mouse pressben az első képnél";
                    QPixmap pix1(":resource/img/Termeszeti/Kicsiben/t3.jpg");
                    ui->term1->setPixmap(pix1);
                    addImageToDb("t3");
                     ui->buttonKep1->hide();
                }
                else if(ui->buttonKep2->hasFocus())
                {
                    QPixmap pix1(":resource/img/Termeszeti/Kicsiben/háttér4.jpg");
                    ui->term2->setPixmap(pix1);
                    addImageToDb("háttér4");
                    ui->buttonKep2->hide();
                }
                else if(ui->buttonKep7->hasFocus())
                {
                    QPixmap pix1(":resource/img/Termeszeti/Kicsiben/t5.jpg");
                    ui->term7->setPixmap(pix1);
                    addImageToDb("t5");
                    ui->buttonKep7->hide();
                }
                else if(ui->buttonKep4->hasFocus())
                {
                    QPixmap pix1(":resource/img/Termeszeti/Kicsiben/t1.jpg");
                    ui->term4->setPixmap(pix1);
                    addImageToDb("t1");
                    ui->buttonKep4->hide();
                }
                else if(ui->buttonKep5->hasFocus())
                {
                    QPixmap pix1(":resource/img/Termeszeti/Kicsiben/t2.jpg");
                    ui->term5->setPixmap(pix1);
                    addImageToDb("t2");
                    ui->buttonKep5->hide();
                }
                else if(ui->buttonKep6->hasFocus())
                {
                    QPixmap pix1(":resource/img/Termeszeti/Kicsiben/háttér2.jpg");
                    ui->term6->setPixmap(pix1);
                    addImageToDb("háttér2");
                    ui->buttonKep6->hide();
                }
                sportPont -= 400;
                ui->pontszam->setText(QString::number(sportPont));
                updatePoints();
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

void jatekFelulet::on_tortenelemTema_clicked() // START
{
    kerdesId = 1;
    QuizFelulet *kvizfelulet=new QuizFelulet(this,db, kerdesId, playerName);
    kvizfelulet->show();
    this->close();
}

void jatekFelulet::on_irodalomTema_clicked() // START
{
    kerdesId = 2;
    QuizFelulet *kvizfelulet=new QuizFelulet(this,db, kerdesId, playerName);
    kvizfelulet->show();
    this->close();
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
    qDebug()<< "itt van getAnswerForBuying";
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
    qDebug()<< "itt van updatePointsban";
    if(kartyaTema == 1) // történelmi kártyát vett --> pontok frissítése db-ben
    {
        QSqlQuery query;
        query.prepare("UPDATE Points SET points = :points WHERE category_id = 1 AND username = :playerName");
        query.bindValue(":points", tortenelemPont);
        query.bindValue(":playerName", playerName);
        if(!query.exec())
        {
            QMessageBox::information(this,"Sikertelen", "Sikertelen beszúrás adatbázisba");
        }
    }
}

void jatekFelulet::setVoltakKepek()
{
    QSqlQuery query(QSqlDatabase::database());
    query.prepare(QString("SELECT voltKepek FROM Users WHERE username=:name"));
    query.bindValue(":name",playerName);
    if(!query.exec())
    {
        throw QString("SELECT voltKepek FROM Users WHERE username=:name failed to execute");
    }
    else
    {
        query.next();
        QString voltakMar=query.value(0).toString();
        voltakKepek=voltakMar.split(",");
        for (auto i:voltakKepek)
            qDebug()<< "kepek amik voltak: " << i;
    }
    for(auto i : voltakKepek)
    {
        if(i == "h1")
        {
            QPixmap pix1(":resource/img/TortenelmiKartya/h1.jpg");
            ui->tort1->setPixmap(pix1);
            ui->buttonKep1_2->hide();
        }
        if(i == "h2")
        {
            QPixmap pix1(":resource/img/TortenelmiKartya/h2.jpg");
            ui->tort2->setPixmap(pix1);
            ui->buttonKep2_2->hide();
        }
        if(i == "h3")
        {
            QPixmap pix1(":resource/img/TortenelmiKartya/h3.jpg");
            ui->tort6->setPixmap(pix1);
            ui->buttonKep6_2->hide();
        }
        if(i == "h4")
        {
            QPixmap pix1(":resource/img/TortenelmiKartya/h4.jpg");
            ui->tort3->setPixmap(pix1);
            ui->buttonKep3_2->hide();
        }
        if(i == "h5")
        {
            QPixmap pix1(":resource/img/TortenelmiKartya/h5.jpg");
            ui->term1->setPixmap(pix1);
            ui->buttonKep5_2->hide();
        }
        if(i == "h7")
        {
            QPixmap pix1(":resource/img/TortenelmiKartya/h7.jpg");
            ui->tort4->setPixmap(pix1);
            ui->buttonKep4_2->hide();
        }
        //Természeti képek:
        if(i == "t3")
        {
            QPixmap pix1(":resource/img/Termeszeti/Kicsiben/t3.jpg");
            ui->term1->setPixmap(pix1);
            ui->buttonKep1->hide();
        }
        if(i == "háttér4")
        {
            QPixmap pix1(":resource/img/Termeszeti/Kicsiben/háttér4.jpg");
            ui->term2->setPixmap(pix1);
            ui->buttonKep2->hide();
        }
        if(i == "háttér2")
        {
            QPixmap pix1(":resource/img/TortenelmiKartya/háttér2.jpg");
            ui->term6->setPixmap(pix1);
            ui->buttonKep6->hide();
        }
        if(i == "t1")
        {
            QPixmap pix1(":resource/img/TortenelmiKartya/t1.jpg");
            ui->term4->setPixmap(pix1);
            ui->buttonKep4->hide();
        }
        if(i == "t5")
        {
            QPixmap pix1(":resource/img/TortenelmiKartya/t5.jpg");
            ui->term7->setPixmap(pix1);
            ui->buttonKep7->hide();
        }
        if(i == "t2")
        {
            QPixmap pix1(":resource/img/TortenelmiKartya/t2.jpg");
            ui->term5->setPixmap(pix1);
            ui->buttonKep5->hide();
        }
    }

}

void jatekFelulet::addImageToDb(QString kep)
{
//    try
//    {
//        qDebug() << "itt addImageToDb ben";
//        for (auto i:voltakKepek)
//            qDebug()<< "kepek amik voltak: " << i;

//        QSqlQuery query(QSqlDatabase::database());
//        query.prepare("UPDATE Users SET voltKepek=:kepSzoveg WHERE username=:usnm");
//        query.bindValue(":kepSzoveg",voltakKepek);
//        qDebug()<<"ElozoUjPlusz:";
//        qDebug()<<voltakKepek;
//        query.bindValue(":usnm",playerName);
//        if (!query.exec())
//        {
//            throw QString("ERROR UPDATE Users SET voltKepek=:kerdesekID WHERE username=:usnm");
//        }
//    }catch(QString e)
//    {
//        QMessageBox::information(this, "Failed Quizfelület catch QString", e);
//    }


    QSqlQuery queryVolt(QSqlDatabase::database()); // voltKépek lekérés
    QSqlQuery query(QSqlDatabase::database()); // Updatelés
    queryVolt.prepare(QString("SELECT voltKepek FROM Users WHERE username=:name"));
    queryVolt.bindValue(":name",playerName);
    if (!queryVolt.exec())
    {
        throw QString("Error SELECT voltKerdesek FROM Users WHERE username=:name");
    }
    else
    {
        queryVolt.next();
        if (queryVolt.value(0).toString()==NULL)
        {
            qDebug()<<"null a kepek listaja";
            query.prepare("UPDATE Users SET voltKepek=:voltKepek WHERE username=:usnm");
            query.bindValue(":voltKepek",kep);
            qDebug()<<"Username:";
            qDebug()<<playerName;
            query.bindValue(":usnm",playerName);
            if (!query.exec())
            {
                throw QString("ERROR UPDATE Users SET voltKerdesek=:kerdesekID WHERE username=:usnm");
            }
        }
        else
        {
                qDebug()<<"HELLOOO";
                QString elozoPluszUj=queryVolt.value(0).toString();
                elozoPluszUj+=QString(",");
                elozoPluszUj+=QString(kep);
                query.prepare("UPDATE Users SET voltKepek=:voltKepek WHERE username=:usnm");
                query.bindValue(":voltKepek",elozoPluszUj);
                qDebug()<<"ElozoUjPlusz:";
                qDebug()<<elozoPluszUj;
                qDebug()<<"Username:";
                qDebug()<<playerName;
                query.bindValue(":usnm",playerName);
                if (!query.exec())
                {
                    throw QString("ERROR UPDATE Users SET voltKerdesek=:kerdesekID WHERE username=:usnm");
                }
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

void jatekFelulet::on_termKartyaTema_clicked()
{
    kartyaTema = 2; // termeszeti
    ui->stackedWidget->setCurrentIndex(3);
    ui->pontPush->hide();
    ui->KartyaPush->hide();
    ui->kartya_vasarlas->hide();
    ui->stackedWidget->show();
    getPoints();
    ui->pontszam->setText(QString::number(sportPont));
}
