#include "quizfelulet.h"
#include "ui_quizfelulet.h"

QuizFelulet::QuizFelulet(QWidget *parent, DatabaseConnection *db, int temaId, QString playerName) :
    QMainWindow(parent),
    ui(new Ui::QuizFelulet),
    vissza(parent),
    db(db),
    kerdesTemaId(temaId),
    playerName(playerName)
{
    ui->setupUi(this);
    setBackground();
    kerdesLekeres();
    valaszLekeres();
    ui->nextQuestion->setEnabled(false);
}

QuizFelulet::~QuizFelulet()
{
    delete ui;
}

void QuizFelulet::kerdesLekeres()
{
    QString question;
    vector <int> kerdesIdkLista;
    vector <int> szurtkerdesek;
    ui->nextQuestion->setEnabled(false);
    if(db->getDb().isOpen())
    {
        try
        {
            {
                    QSqlQuery query(QSqlDatabase::database());
                    query.prepare(QString("SELECT voltKerdesek FROM Users WHERE username=:name"));
                    query.bindValue(":name",playerName);
                    if(!query.exec())
                    {
                        throw QString("SELECT voltKerdesek FROM Users WHERE username=:name failed to execute");
                    }
                    else
                    {
                        query.next();
                        QString voltakMar=query.value(0).toString();
                        voltakKerdesek=voltakMar.split(",");
                        for (auto i:voltakKerdesek)
                            qDebug()<<i;
                    }
            }
                QSqlQuery query(QSqlDatabase::database());
                //Lekérdezem az összes category_id-hoz tartozó kérdés id-t és listába rakom
                query.prepare(QString("SELECT id FROM Question WHERE category_id = :categoryID ORDER BY category_id ASC, id ASC"));
                query.bindValue(":categoryID", kerdesTemaId);

                if(!query.exec())
                {
                    throw QString("SELECT id FROM Question ORDER BY id ASC failed to execute");
                }
                else
                {
                    if(query.size() == 0)
                    {
                         QMessageBox::information(this, "Error","No question found");
                    }
                    else
                    {
                        while(query.next())
                        {
                            questionId = query.value(0).toInt();
                            kerdesIdkLista.push_back(questionId);
//                            qDebug()<< "Kerdes ID db-bol";
//                            qDebug()<<questionId;
                        }
                    }
                }
                marKerdezettId.clear(); // ez fontos hiszen minden körben sokszorozódnának a bele pakolt dolgok
                szurtkerdesek.clear();
                for(int i = 0; i < voltakKerdesek.size(); i++) // voltakKerdes-ből az intet bele rakni a marKerdettId - vektorba
                {
                     marKerdezettId.push_back(voltakKerdesek[i].toInt());
                }
                sort(marKerdezettId.begin(),marKerdezettId.end()); // marKerdettId vektort rendezni kell a set_difference - hez
                // két vektor különbsége a szurtkerdesek vektorába kerül bele
                std::set_difference(kerdesIdkLista.begin(),kerdesIdkLista.end(),marKerdezettId.begin(),marKerdezettId.end(),
                                    std::inserter(szurtkerdesek,szurtkerdesek.begin()));
                srand((unsigned int)time(NULL));
                int RandomValue = rand() % ((szurtkerdesek.size()-1) - 0);
                questionId = szurtkerdesek[RandomValue];
                qDebug()<< "random question ID " << questionId;

           /*     bool notOK=true;
                int hanyszor=0;
                if (kerdesIdkLista.size()==voltakKerdesek.size())
                    throw QString("Out of Questions for this subject");
               do
                {
                    srand((unsigned int)time(NULL));
                    int RandomValue = rand() % ((kerdesIdkLista.size()-1) - 0);
//                    qDebug()<< "Random szám";
//                    qDebug()<< RandomValue;
                    questionId = kerdesIdkLista[RandomValue];
                    qDebug()<< "Random ID:";
                    qDebug()<< questionId;
//                    qDebug()<< "Voltak Size:";
//                    qDebug()<< voltakKerdesek.size();
                    int i=0;
                    hanyszor++;
                    qDebug()<<QString(QString("Hanyszor:")+QString(QString::number(hanyszor)));
                    while(i<voltakKerdesek.size() && voltakKerdesek[i].toInt()!=questionId)
                    {
                        i++;
                    }
//                    questionId = voltakKerdesek[i].toInt();
                    if (i==voltakKerdesek.size())
                        notOK=false;
                }while(notOK);
                */

                {
                    QSqlQuery queryVolt(QSqlDatabase::database());
                    queryVolt.prepare(QString("SELECT voltKerdesek FROM Users WHERE username=:name"));
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
                            query.prepare("UPDATE Users SET voltKerdesek=:kerdesekID WHERE username=:usnm");
                            query.bindValue(":kerdesekID",questionId);
                            qDebug()<<"KerdesID:";
                            qDebug()<<questionId;
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
                                elozoPluszUj+=QString(QString::number(questionId));
                                query.prepare("UPDATE Users SET voltKerdesek=:kerdesekID WHERE username=:usnm");
                                query.bindValue(":kerdesekID",elozoPluszUj);
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

                qDebug()<< "Random ID";
                qDebug()<< questionId;


           // marKerdezettId.push_back(questionId); // fontos, hogy az előbbi ciklus után adjuk hozzá a már kérdezettek vektorához
            eddigiKerdesCounter++;
            ui->osszCounter->setText(QString::number(eddigiKerdesCounter));

     /*       srand((unsigned int)time(NULL));
            int RandomValue = rand() % ((kerdesIdkLista.size()-1) - 0);
            qDebug()<< "Random szám";
            qDebug()<< RandomValue;
            randomTemaId = kerdesIdkLista[RandomValue];
            qDebug()<< "Random ID";
            qDebug()<< randomTemaId;

           it = std::find(kerdesIdkLista.begin(), kerdesIdkLista.end(), randomTemaId);
           kerdesIdkLista.erase(it);*/

            try
            {
                QSqlQuery queryQuestion(QSqlDatabase::database());
               /* std::random_device rd;
                std::mt19937 mt(rd());
                std::uniform_real_distribution<> dist(elso, utolso);  //zárt intervalum*/
//                do
//                {
//                    qDebug()<<"Eleje";
//                    int randomSzam=(elso + ( std::rand() % ( utolso - elso + 1 ) ));
                    //randomSzam=1; így nyilván jó
                    qDebug()<<"randomSzam:";
                    qDebug()<<questionId;
                    queryQuestion.prepare(QString("SELECT question,id FROM Question WHERE id=:szam"));
//                    qDebug()<<"1";
                    queryQuestion.bindValue(":szam",questionId);
//                    qDebug()<<"2";
                    if(!queryQuestion.exec())
                    {
                        throw QString("Failed to execute SELECT question FROM Question WHERE id=:szam");
                        qDebug()<<"Failed to execute SELECT question FROM Question WHERE id=:szam";
                    }
                    qDebug()<<"3\nQuery size:";
                    qDebug()<<queryQuestion.size();
/*                }while(queryQuestion.size()==0);  */   //itt megfagy a program fuckknowswhy
                qDebug()<<"while out";
                if (queryQuestion.size() == 1)
                {
                    queryQuestion.next();
                    question = queryQuestion.value(0).toString();
//                    question.insert(0,'\n'); - nem lesz középen ettől
                    ui->kerdesTextEdit->setText(question);
                    ui->kerdesTextEdit->setAlignment(Qt::AlignCenter);
                    ui->kerdesTextEdit->setAlignment(Qt::AlignHCenter);
//                    ui->kerdesTextEdit->setAlignment(Qt::AlignVCenter);
//                    ui->kerdesTextEdit->setStyleSheet("padding-top:50px;");
//                    questionId = queryQuestion.value(1).toInt();          questionId==randomTemaId!!
//                    qDebug()<<"questionId:";
//                    qDebug()<< questionId;
                }
                else
                {
                    throw QString("queryQuestion.size() != 1");
                }
            }
            catch(QString e)
            {
                QMessageBox::information(this, "Failed Quizfelület catch QString", e);
            }
            /*catch(...)
            {
                QMessageBox::information(this, "Failed Quizfelület catch ...", "Unexpected error");
            }   nem kell, mert elvileg a külső ugyan ilyen elkapja*/
        }
        catch(QString e)
        {
            QMessageBox::information(this, "Failed Quizfelület catch QString", e);
        }
        catch(...)
        {
            QMessageBox::information(this, "Failed Quizfelület catch ...", "Unexpected error");
        }
    }
}

void QuizFelulet::valaszLekeres()
{
    vector <QString> valaszIDLista;
    QString valaszDbbol;
    int j = 0;
    int correct;
    if(db->getDb().isOpen())
    {
        try
        {
            QSqlQuery query(QSqlDatabase::database());
            //Lekérdezem az összes question_id-hoz tartozó válasz id-t és listába rakom
            query.prepare(QString("SELECT answer, id, correct FROM Answers WHERE question_id = :questionID ORDER BY question_id ASC, id ASC"));
            query.bindValue(":questionID", questionId);
            if(!query.exec())
            {
                throw QString("SELECT answer, id, correct FROM Answers WHERE question_id = :questionID ORDER BY question_id ASC, id ASC failed to execute");
            }
            else
            {
                if(query.size() == 0)
                {
                     QMessageBox::information(this, "Error","No answer found");
                }
                else
                {
                    while(query.next())
                    {
                        valaszDbbol = query.value(1).toString();
                        qDebug()<< "Valasz: ";
                        qDebug()<< valaszDbbol;
                        correct = query.value(2).toInt(); //  1/0

                        if(j == 0) // első válasz
                        {
                            qDeleteAll(ui->valasz1Button->children());
                            ui->valasz1Button->setStyleSheet("hover:background-color: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #f2d9e6, stop: 0.1 #cc6699,  stop: 0.49 #d98cb3;");
                            valasz1 = checkStringLength(query.value(0).toString());
                            ui->valasz1Button->setText("");
                            ui->valasz1Button->setLayout(valasz1);
                            if(correct == 1) // ha helyes elmentjük hogy az 1 a helyes (buttonokhoz)
                            {
                                helyesValasz = 1;
                            }
                        }
                        else if(j == 1) // második válasz
                        {
                            qDeleteAll(ui->valasz2Button->children());
                            ui->valasz2Button->setStyleSheet("hover:background-color: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #f2d9e6, stop: 0.1 #cc6699,  stop: 0.49 #d98cb3;");
                            valasz2 = checkStringLength(query.value(0).toString());
                            ui->valasz2Button->setText("");
                            ui->valasz2Button->setLayout(valasz2);
                            if(correct == 1)
                            {
                                helyesValasz = 2;
                            }
                        }
                        else if(j == 2) // haramdik válasz
                        {
                            qDeleteAll(ui->valasz3Button->children());
                            ui->valasz3Button->setStyleSheet("hover:background-color: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #f2d9e6, stop: 0.1 #cc6699,  stop: 0.49 #d98cb3;");
                            valasz3 = checkStringLength(query.value(0).toString());
                            ui->valasz3Button->setText("");
                            ui->valasz3Button->setLayout(valasz3);
                            if(correct == 1)
                            {
                                helyesValasz = 3;
                            }
                        }
                        else if(j == 3) // negyedik válasz
                        {
                            qDeleteAll(ui->valasz4Button->children());
                            ui->valasz4Button->setStyleSheet("hover:background-color: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #f2d9e6, stop: 0.1 #cc6699,  stop: 0.49 #d98cb3;");
                            valasz4 = checkStringLength(query.value(0).toString());
                            ui->valasz4Button->setText("");
                            ui->valasz4Button->setLayout(valasz4);
                            if(correct == 1)
                            {
                                helyesValasz = 4;
                            }
                        }
                        j++;
                    }
                }
            }
        }
        catch(QString e)
        {
            QMessageBox::information(this, "Failed Quizfelület catch QString", e);
        }
        catch(...)
        {
            QMessageBox::information(this, "Failed Quizfelület catch ...", "Unexpected error");
        }
    }
}

QHBoxLayout *QuizFelulet::checkStringLength(QString str)
{
        QHBoxLayout *pLayout = new QHBoxLayout();
        QLabel *pTextLabel = new QLabel();
        pTextLabel->setText(str);
        pTextLabel->setAlignment(Qt::AlignCenter);
        pTextLabel->setWordWrap(true);
        pTextLabel->setTextInteractionFlags(Qt::NoTextInteraction);
        pTextLabel->setMouseTracking(false);
        pTextLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        if(str.length() > 37)
        {
          pTextLabel->setStyleSheet("color: white;font: bold 10pt ""MS Shell Dlg 2"";");
        }
        else
        {
            pTextLabel->setStyleSheet("color: white;font: bold 12pt ""MS Shell Dlg 2"";");
        }
        pLayout->addWidget(pTextLabel);
        pLayout->setSpacing(0);
        pLayout->setMargin(0);
        pLayout->setContentsMargins(5, 5, 5, 5);
        return pLayout;
}

void QuizFelulet::on_valasz1Button_clicked()
{
    if(helyesValasz == 1)
    {
        ui->valasz1Button->setStyleSheet("background-color: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #b3ff99, stop: 0.1 #66ff33,  stop: 0.49 #33cc00 );");
        joValaszCounter++;
    }
    else
    {
        ui->valasz1Button->setStyleSheet("background-color: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #ff6666, stop: 0.1 #ff1a1a,  stop: 0.49 #cc0000 );");
        QEventLoop loop;
        QTimer::singleShot(500, &loop, SLOT(quit())); // kicsit várjon amíg megjeleníti az eredményt
        loop.exec();
        if(helyesValasz == 4)
        {
            ui->valasz4Button->setStyleSheet("background-color: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #b3ff99, stop: 0.1 #66ff33,  stop: 0.49 #33cc00 );");

        }
        if(helyesValasz == 2)
        {
            ui->valasz2Button->setStyleSheet("background-color: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #b3ff99, stop: 0.1 #66ff33,  stop: 0.49 #33cc00 );");

        }
        if(helyesValasz == 3)
        {
            ui->valasz3Button->setStyleSheet("background-color: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #b3ff99, stop: 0.1 #66ff33,  stop: 0.49 #33cc00 );");
        }
    }
    ui->valasz2Button->setEnabled(false);
    ui->valasz3Button->setEnabled(false);
    ui->valasz4Button->setEnabled(false);
    ui->counter->setText(QString::number(joValaszCounter));
    ui->nextQuestion->setEnabled(true);
    if(eddigiKerdesCounter == kerdesekSzama)
    {
        ui->nextQuestion->setEnabled(false);
        QEventLoop loop;
        QTimer::singleShot(2000, &loop, SLOT(quit())); // kicsit várjon amíg megjeleníti az eredményt
        loop.exec();
        totalPoints = joValaszCounter * 50;
        QString status = QString("Gratulálok! Nyertél %1 pontot.").arg(totalPoints);
        QMessageBox::information(this,"Végeztél", status);
        assignPointsToPlayer();
        this->close();
        vissza->show();
    }
}

void QuizFelulet::on_valasz2Button_clicked()
{
    if(helyesValasz == 2)
    {
        ui->valasz2Button->setStyleSheet("background-color: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #b3ff99, stop: 0.1 #66ff33,  stop: 0.49 #33cc00 );");
        joValaszCounter++;
    }
    else
    {
        ui->valasz2Button->setStyleSheet("background-color: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #ff6666, stop: 0.1 #ff1a1a,  stop: 0.49 #cc0000 );");
        QEventLoop loop;
        QTimer::singleShot(500, &loop, SLOT(quit())); // kicsit várjon amíg megjeleníti az eredményt
        loop.exec();
        if(helyesValasz == 1)
        {
            ui->valasz1Button->setStyleSheet("background-color: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #b3ff99, stop: 0.1 #66ff33,  stop: 0.49 #33cc00 );");

        }
        if(helyesValasz == 4)
        {
            ui->valasz4Button->setStyleSheet("background-color: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #b3ff99, stop: 0.1 #66ff33,  stop: 0.49 #33cc00 );");

        }
        if(helyesValasz == 3)
        {
            ui->valasz3Button->setStyleSheet("background-color: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #b3ff99, stop: 0.1 #66ff33,  stop: 0.49 #33cc00 );");
        }
    }
    ui->valasz1Button->setEnabled(false);
    ui->valasz3Button->setEnabled(false);
    ui->valasz4Button->setEnabled(false);
    ui->counter->setText(QString::number(joValaszCounter));
    ui->nextQuestion->setEnabled(true);
    if(eddigiKerdesCounter == kerdesekSzama)
    {
        ui->nextQuestion->setEnabled(false);
        QEventLoop loop;
        QTimer::singleShot(2000, &loop, SLOT(quit())); // kicsit várjon amíg megjeleníti az eredményt
        loop.exec();
        totalPoints = joValaszCounter * 50;
        QString status = QString("Gratulálok! Nyertél %1 pontot.").arg(totalPoints);
        QMessageBox::information(this,"Végeztél", status);
        assignPointsToPlayer();
        this->close();
        vissza->show();
    }
}

void QuizFelulet::on_valasz3Button_clicked()
{
    if(helyesValasz == 3)
    {
        ui->valasz3Button->setStyleSheet("background-color: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #b3ff99, stop: 0.1 #66ff33,  stop: 0.49 #33cc00 );");
        joValaszCounter++;
    }
    else
    {
        ui->valasz3Button->setStyleSheet("background-color: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #ff6666, stop: 0.1 #ff1a1a,  stop: 0.49 #cc0000 );");
        QEventLoop loop;
        QTimer::singleShot(500, &loop, SLOT(quit())); // kicsit várjon amíg megjeleníti az eredményt
        loop.exec();
        if(helyesValasz == 1)
        {
            ui->valasz1Button->setStyleSheet("background-color: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #b3ff99, stop: 0.1 #66ff33,  stop: 0.49 #33cc00 );");

        }
        if(helyesValasz == 2)
        {
            ui->valasz2Button->setStyleSheet("background-color: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #b3ff99, stop: 0.1 #66ff33,  stop: 0.49 #33cc00 );");

        }
        if(helyesValasz == 4)
        {
            ui->valasz4Button->setStyleSheet("background-color: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #b3ff99, stop: 0.1 #66ff33,  stop: 0.49 #33cc00 );");
        }
    }
    ui->valasz2Button->setEnabled(false);
    ui->valasz1Button->setEnabled(false);
    ui->valasz4Button->setEnabled(false);
    ui->counter->setText(QString::number(joValaszCounter));
    ui->nextQuestion->setEnabled(true);
    if(eddigiKerdesCounter == kerdesekSzama)
    {
        ui->nextQuestion->setEnabled(false);
        QEventLoop loop;
        QTimer::singleShot(2000, &loop, SLOT(quit())); // kicsit várjon amíg megjeleníti az eredményt
        loop.exec();
        totalPoints = joValaszCounter * 50;
        QString status = QString("Gratulálok! Nyertél %1 pontot.").arg(totalPoints);
        QMessageBox::information(this,"Végeztél", status);
        assignPointsToPlayer();
        this->close();
        vissza->show();
    }
}

void QuizFelulet::on_valasz4Button_clicked()
{
    if(helyesValasz == 4)
    {
        ui->valasz4Button->setStyleSheet("background-color: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #b3ff99, stop: 0.1 #66ff33,  stop: 0.49 #33cc00 );");
        joValaszCounter++;
    }
    else
    {
        ui->valasz4Button->setStyleSheet("background-color: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #ff6666, stop: 0.1 #ff1a1a,  stop: 0.49 #cc0000 );");
        QEventLoop loop;
        QTimer::singleShot(500, &loop, SLOT(quit())); // kicsit várjon amíg megjeleníti az eredményt
        loop.exec();
        if(helyesValasz == 1)
        {
            ui->valasz1Button->setStyleSheet("background-color: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #b3ff99, stop: 0.1 #66ff33,  stop: 0.49 #33cc00 );");
        }
        if(helyesValasz == 2)
        {
            ui->valasz2Button->setStyleSheet("background-color: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #b3ff99, stop: 0.1 #66ff33,  stop: 0.49 #33cc00 );");

        }
        if(helyesValasz == 3)
        {
            ui->valasz3Button->setStyleSheet("background-color: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #b3ff99, stop: 0.1 #66ff33,  stop: 0.49 #33cc00 );");
        }
    }
    ui->valasz2Button->setEnabled(false);
    ui->valasz3Button->setEnabled(false);
    ui->valasz1Button->setEnabled(false);
    ui->counter->setText(QString::number(joValaszCounter));
    ui->nextQuestion->setEnabled(true);
    if(eddigiKerdesCounter == kerdesekSzama)
    {
        ui->nextQuestion->setEnabled(false);
        QEventLoop loop;
        QTimer::singleShot(2000, &loop, SLOT(quit())); // kicsit várjon amíg megjeleníti az eredményt
        loop.exec();
        totalPoints = joValaszCounter * 50;
        QString status = QString("Gratulálok! Nyertél %1 pontot.").arg(totalPoints);
        QMessageBox::information(this,"Végeztél", status);
        assignPointsToPlayer();
        this->close();
        vissza->show();
    }
}

void QuizFelulet::on_nextQuestion_clicked()
{

    //visszaállítani a gombokat kattinthatóra, és a szinüket eredeti állapotba
    ui->valasz1Button->setEnabled(true);
    ui->valasz2Button->setEnabled(true);
    ui->valasz3Button->setEnabled(true);
    ui->valasz4Button->setEnabled(true);
    ui->valasz1Button->setStyleSheet("background-color: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #df9fbf, stop: 0.1 #c6538c,  stop: 0.49 #73264d );");
    ui->valasz2Button->setStyleSheet("background-color: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #df9fbf, stop: 0.1 #c6538c,  stop: 0.49 #73264d );");
    ui->valasz3Button->setStyleSheet("background-color: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #df9fbf, stop: 0.1 #c6538c,  stop: 0.49 #73264d );");
    ui->valasz4Button->setStyleSheet("background-color: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #df9fbf, stop: 0.1 #c6538c,  stop: 0.49 #73264d );");
    kerdesLekeres();
    valaszLekeres();
}


void QuizFelulet::setBackground()
{
    if(kerdesTemaId == 1) // történelmi
    {
        // legfelsővel nem megy
        // ui->centralwidget->setStyleSheet("border-image: url(:/resource/img/tortenelmiHatter/tortenelmi_1.jpg);background-repeat: no-repeat;bacground-position: center;");

        QPixmap bkgnd(":/resource/img/tortenelmiHatter/tortenelmi_1.jpg");
          bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
          QPalette palette;
          palette.setBrush(QPalette::Background, bkgnd);
          this->setPalette(palette);
    }
    else if(kerdesTemaId == 2) // irodalmi
    {
        QPixmap bkgnd(":/resource/img/irodalmiHatter/irodalmi_4.jpg");
          bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
          QPalette palette;
          palette.setBrush(QPalette::Background, bkgnd);
          this->setPalette(palette);
    }
}

void QuizFelulet::assignPointsToPlayer()
{
    int pointFromDb;
    QSqlQuery query(QSqlDatabase::database());
    query.prepare("SELECT username,points FROM Points WHERE username = :username AND category_id = :categoryID");
    query.bindValue(":username", playerName);
    query.bindValue(":categoryID", kerdesTemaId);
    if(db->getDb().isOpen())
    {
        try
        {
            if(!query.exec())
            {
                throw QString("SELECT username WHERE username = :username AND category_id = :categoryID");
            }
            else
            {
                if(totalPoints != 0)
                {
                    if(query.size() == 0) // ha még nincsen pontja ebben a kategóriában -- bekell szúrni névvel együtt
                    {
                        QSqlQuery queryInsert(QSqlDatabase::database());
                        queryInsert.prepare("INSERT INTO Points(username,category_id,points) VALUES(:uname,:categoryId,:points)");
                        queryInsert.bindValue(":uname", playerName);
                        queryInsert.bindValue(":categoryId", kerdesTemaId);
                        queryInsert.bindValue(":points", totalPoints);
                        if(!queryInsert.exec())
                        {
                            qDebug() << "Sikertelen beszúrás";
                            throw QString("INSERT INTO Points(username,category_id,points) VALUES(:uname,:categoryId,:points)");
                        }
                        qDebug()<<"Beszúrva az adatbázishoz a pont." << totalPoints;
                    }
                    else // ha már van, lekell kérni és hozzá kell adni
                    {
                        query.next();
                        pointFromDb = query.value(1).toInt();
                        totalPoints+=pointFromDb;
                        QSqlQuery queryUpdate(QSqlDatabase::database());
                        queryUpdate.prepare("UPDATE Points SET points = :points WHERE username = :uname AND category_id = :categoryID");
                        queryUpdate.bindValue(":uname", playerName);
                        queryUpdate.bindValue(":categoryID", kerdesTemaId);
                        queryUpdate.bindValue(":points", totalPoints);
                        if(!queryUpdate.exec())
                        {
                            qDebug() << "Sikertelen update";
                            throw QString("UPDATE Points SET points = :points WHERE username = :uname AND category_id = :categoryID");
                        }
                        qDebug()<<"Hozzáadva az adatbázishoz a pont." << totalPoints;
                    }
                }
            }
        }
        catch(QString e)
        {
                QMessageBox::information(this, "Failed Quizfelület catch QString", e);
        }
        catch(...)
        {
                QMessageBox::information(this, "Failed Quizfelület catch ...", "Unexpected error");
        }
    }
}

void QuizFelulet::on_nextQuestion_2_clicked()
{
    assignPointsToPlayer();
    this->close();
    vissza->show();
}
