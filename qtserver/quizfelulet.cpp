#include "quizfelulet.h"
#include "ui_quizfelulet.h"

QuizFelulet::QuizFelulet(QWidget *parent, DatabaseConnection *db) :
    QMainWindow(parent),
    ui(new Ui::QuizFelulet),
    db(db)
{
    ui->setupUi(this);
    kerdesLekeres();
}

QuizFelulet::~QuizFelulet()
{
    delete ui;
}

void QuizFelulet::kerdesLekeres()
{
    int elso=0, utolso=0;
    if(db->getDb().isOpen())
    {
        try
        {
            QSqlQuery query(QSqlDatabase::database());
            //Lekérdezem az első id-t
            query.prepare(QString("SELECT id FROM Question ORDER BY id ASC LIMIT 1"));
            if(!query.exec())
            {
                throw QString("SELECT id FROM Question ORDER BY id ASC LIMIT 1 failed to execute");
            }
            else
            {
                if(query.size() == 0)
                {
                     QMessageBox::information(this, "Error","No question found");
                }
                query.next();
                elso=query.value(0).toString().toDouble();
            }

            //Lekérdezem az utolsó id-t
            query.prepare(QString("SELECT id FROM Question ORDER BY id DESC LIMIT 1"));
            if(!query.exec())
            {
                throw QString("SELECT id FROM Question ORDER BY id DESC LIMIT 1Failed to execute");
            }
            else
            {
                if(query.size() == 0)
                {
                     QMessageBox::information(this, "Error","No question found");
                }
                query.next();
                utolso=query.value(0).toString().toDouble();
            }
            qDebug()<<"elso";
            qDebug()<<elso;
            qDebug()<<"utolso";
            qDebug()<<utolso;
            //Az első és utolsó ID-jú kérdések között randomoltatok egy számot

            try
            {
                QSqlQuery queryQuestion(QSqlDatabase::database());
               /* std::random_device rd;
                std::mt19937 mt(rd());
                std::uniform_real_distribution<> dist(elso, utolso);  //zárt intervalum*/
                do
                {
                    qDebug()<<"Eleje";
                    int randomSzam=(elso + ( std::rand() % ( utolso - elso + 1 ) ));
                    //randomSzam=1; így nyilván jó
                    qDebug()<<"randomSzam:";
                    qDebug()<<randomSzam;
                    queryQuestion.prepare(QString("SELECT question FROM Question WHERE id=:szam"));
                    qDebug()<<"1";
                    queryQuestion.bindValue(":szam",randomSzam);
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
                    ui->kerdesTextEdit->setText(queryQuestion.value(0).toString());
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
