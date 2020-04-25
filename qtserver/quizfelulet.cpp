#include "quizfelulet.h"
#include "ui_quizfelulet.h"

QuizFelulet::QuizFelulet(QWidget *parent, DatabaseConnection *db, int temaId) :
    QMainWindow(parent),
    ui(new Ui::QuizFelulet),
    db(db),
    kerdesTemaId(temaId)
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
    int kerdesIdDbbol;
    int randomTemaId;
    QString question;
    vector <int> kerdesIdkLista;
    ui->nextQuestion->setEnabled(false);
    if(db->getDb().isOpen())
    {
        try
        {
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
                        kerdesIdDbbol = query.value(0).toInt();
                        kerdesIdkLista.push_back(kerdesIdDbbol);
                        qDebug()<< "Kerdes ID";
                        qDebug()<<kerdesIdDbbol;
                    }
                }
            }
            if(eddigiKerdesCounter != 0)
            {
                for(auto it = begin(kerdesIdkLista); it != end(kerdesIdkLista); ++it)
                {
                    for(auto li = begin(marKerdezettId); li != end(marKerdezettId); ++li)
                    {
                        if(*it != *li)
                        {
                            szurtKerdesIdkLista.push_back(*it);
                        }
                    }
                }
                // random szám generálás
                srand((unsigned int)time(NULL));
                int RandomValue = rand() % ((szurtKerdesIdkLista.size()-1) - 0);
                qDebug()<< "Random szám";
                qDebug()<< RandomValue;
                randomTemaId = szurtKerdesIdkLista[RandomValue];
                qDebug()<< "Random ID";
                qDebug()<< randomTemaId;
            }
            else
            {
                srand((unsigned int)time(NULL));
                int RandomValue = rand() % ((kerdesIdkLista.size()-1) - 0);
                qDebug()<< "Random szám";
                qDebug()<< RandomValue;
                randomTemaId = kerdesIdkLista[RandomValue];
                qDebug()<< "Random ID";
                qDebug()<< randomTemaId;
            }
            marKerdezettId.push_back(kerdesIdDbbol); // fontos, hogy az előbbi ciklus után adjuk hozzá a már kérdezettek vektorához
            eddigiKerdesCounter++;
            ui->osszCounter->setText(QString::number(eddigiKerdesCounter));

            try
            {
                QSqlQuery queryQuestion(QSqlDatabase::database());
               /* std::random_device rd;
                std::mt19937 mt(rd());
                std::uniform_real_distribution<> dist(elso, utolso);  //zárt intervalum*/
                do
                {
                    qDebug()<<"Eleje";
//                    int randomSzam=(elso + ( std::rand() % ( utolso - elso + 1 ) ));
                    //randomSzam=1; így nyilván jó
                    qDebug()<<"randomSzam:";
                    qDebug()<<randomTemaId;
                    queryQuestion.prepare(QString("SELECT question,id FROM Question WHERE id=:szam"));
                    qDebug()<<"1";
                    queryQuestion.bindValue(":szam",randomTemaId);
                    qDebug()<<"2";
                    if(!queryQuestion.exec())
                    {
                        throw QString("Failed to execute SELECT question FROM Question WHERE id=:szam");
                        qDebug()<<"Failed to execute SELECT question FROM Question WHERE id=:szam";
                    }
                    qDebug()<<"3\nQuery size:";
                    qDebug()<<queryQuestion.size();
                }while(queryQuestion.size()==0);     //itt megfagy a program fuckknowswhy
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
                    questionId = queryQuestion.value(1).toInt();
                    qDebug()<<"questionId:";
                    qDebug()<< questionId;
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
                            valasz1 = checkStringLength(query.value(0).toString());
                            ui->valasz1Button->setText(valasz1);
                            if(correct == 1) // ha helyes elmentjük hogy az 1 a helyes (buttonokhoz)
                            {
                                helyesValasz = 1;
                            }
                        }
                        else if(j == 1) // második válasz
                        {
                            valasz2 = checkStringLength(query.value(0).toString());
                            ui->valasz2Button->setText(valasz2);
                            if(correct == 1)
                            {
                                helyesValasz = 2;
                            }
                        }
                        else if(j == 2) // haramdik válasz
                        {
                            valasz3 = checkStringLength(query.value(0).toString());
                            ui->valasz3Button->setText(valasz3);
                            if(correct == 1)
                            {
                                helyesValasz = 3;
                            }
                        }
                        else if(j == 3) // negyedik válasz
                        {
                            valasz4 = checkStringLength(query.value(0).toString());
                            ui->valasz4Button->setText(valasz4);
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

QString QuizFelulet::checkStringLength(QString str)
{
    int i = 0;
    if(str.length() > 37)
    {
        for(i = 28; i < str.length();)
        {
            if(str.data()[i] != ' ')
            {
                i++;
            }
            else
            {
                break;
            }
        }
        if(str.data()[i] == ' ' && str.data()[i+1] == ' ')
        { // ha pont 28 karakteres a string akkor felső sorba rakja - ez elkerülentő

        }
        else{
           str.insert(i,'\n');
        }
    }
    qDebug()<< "i értéke: " << i;
    return str;
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
    }
    ui->valasz2Button->setEnabled(false);
    ui->valasz3Button->setEnabled(false);
    ui->valasz4Button->setEnabled(false);
    ui->counter->setText(QString::number(joValaszCounter));
    ui->nextQuestion->setEnabled(true);
    if(eddigiKerdesCounter == 11)
    {
        ui->nextQuestion->setEnabled(false);
        QEventLoop loop;
        QTimer::singleShot(2000, &loop, SLOT(quit())); // kicsit várjon amíg megjeleníti az eredményt
        loop.exec();
        totalPoints = joValaszCounter * 50;
        QString status = QString("Gratulálok! Nyertél %1 pontot.").arg(totalPoints);
        QMessageBox::information(this,"Végeztél", status);
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
    }
    ui->valasz1Button->setEnabled(false);
    ui->valasz3Button->setEnabled(false);
    ui->valasz4Button->setEnabled(false);
    ui->counter->setText(QString::number(joValaszCounter));
    ui->nextQuestion->setEnabled(true);
    if(eddigiKerdesCounter == 5)
    {
        ui->nextQuestion->setEnabled(false);
        QEventLoop loop;
        QTimer::singleShot(2000, &loop, SLOT(quit())); // kicsit várjon amíg megjeleníti az eredményt
        loop.exec();
        totalPoints = joValaszCounter * 50;
        QString status = QString("Gratulálok! Nyertél %1 pontot.").arg(totalPoints);
        QMessageBox::information(this,"Végeztél", status);
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
    }
    ui->valasz2Button->setEnabled(false);
    ui->valasz1Button->setEnabled(false);
    ui->valasz4Button->setEnabled(false);
    ui->counter->setText(QString::number(joValaszCounter));
    ui->nextQuestion->setEnabled(true);
    if(eddigiKerdesCounter == 5)
    {
        ui->nextQuestion->setEnabled(false);
        QEventLoop loop;
        QTimer::singleShot(2000, &loop, SLOT(quit())); // kicsit várjon amíg megjeleníti az eredményt
        loop.exec();
        totalPoints = joValaszCounter * 50;
        QString status = QString("Gratulálok! Nyertél %1 pontot.").arg(totalPoints);
        QMessageBox::information(this,"Végeztél", status);
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
    }
    ui->valasz2Button->setEnabled(false);
    ui->valasz3Button->setEnabled(false);
    ui->valasz1Button->setEnabled(false);
    ui->counter->setText(QString::number(joValaszCounter));
    ui->nextQuestion->setEnabled(true);
    if(eddigiKerdesCounter == 5)
    {
        ui->nextQuestion->setEnabled(false);
        QEventLoop loop;
        QTimer::singleShot(2000, &loop, SLOT(quit())); // kicsit várjon amíg megjeleníti az eredményt
        loop.exec();
        totalPoints = joValaszCounter * 50;
        QString status = QString("Gratulálok! Nyertél %1 pontot.").arg(totalPoints);
        QMessageBox::information(this,"Végeztél", status);
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
