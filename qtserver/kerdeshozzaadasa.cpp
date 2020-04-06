#include "kerdeshozzaadasa.h"
#include "ui_kerdeshozzaadasa.h"

//kerdesHozzaadasa::kerdesHozzaadasa(QWidget *parent) :
//    QWidget(parent),
//    ui(new Ui::kerdesHozzaadasa)
//{
//    ui->setupUi(this);
//    db= new DatabaseConnection();
//}
kerdesHozzaadasa::kerdesHozzaadasa(QWidget *parent, DatabaseConnection *db) :
    QWidget(parent),
    ui(new Ui::kerdesHozzaadasa),
    db(db)
{
    ui->setupUi(this);
    QMessageBox::information(this, "WARNING", "Ne adj hozzá kérdést kategória nélkül!!!");
}
kerdesHozzaadasa::~kerdesHozzaadasa()
{
    delete ui;
}

void kerdesHozzaadasa::on_hozzaadButton_clicked()
{
    QString kerdes = ui->kerdesMezo->toPlainText();
    QString valasz1 = ui->valasz1Mezo->text();
    QString valasz2 = ui->valasz1Mezo->text();
    QString valasz3 = ui->valasz1Mezo->text();
    QString valasz4 = ui->valasz1Mezo->text();
    int helyesNum;
    if (ui->radioButton->isChecked())
        helyesNum=1;
    if (ui->radioButton_2->isChecked())
        helyesNum=2;
    if (ui->radioButton_3->isChecked())
        helyesNum=3;
    if (ui->radioButton_4->isChecked())
        helyesNum=4;

    if(db->getDb().open())
    {
        QSqlQuery query(QSqlDatabase::database("MyConnect"));
        query.prepare(QString("INSERT INTO Question(question) VALUES(:kerdes)"));
        query.bindValue(":kerdes", kerdes);
        if(!query.exec())
        {
            QMessageBox::information(this, "Failed", "Query Failed to execute");

        }
        else
        {
            query.prepare(QString("SELECT id FROM Question WHERE question=:kerdes"));
            query.bindValue(":kerdes", kerdes);
            if(!query.exec())
            {
                QMessageBox::information(this, "Failed", "Query Failed to execute");

            }
            while (query.next())
            {
                int questionID = query.value(0).toInt();
                QSqlQuery queryAns(QSqlDatabase::database("MyConnect"));
                queryAns.prepare(QString("INSERT INTO Answers(answer,question_id,correct) VALUES(:valasz1,:questionID,:correctNum)"));
                queryAns.bindValue(":valasz1", valasz1);
                queryAns.bindValue(":questionID", questionID);
                if (helyesNum==1)
                    queryAns.bindValue(":correctNum", 1);
                else
                    queryAns.bindValue(":correctNum", 0);
                if(!queryAns.exec())
                {
                    QMessageBox::information(this, "Failed", "Query Failed to execute");

                }

                queryAns.prepare(QString("INSERT INTO Answers(answer,question_id,correct) VALUES(:valasz2,:questionID,:correctNum)"));
                queryAns.bindValue(":valasz2", valasz2);
                queryAns.bindValue(":questionID", questionID);
                if (helyesNum==2)
                    queryAns.bindValue(":correctNum", 1);
                else
                    queryAns.bindValue(":correctNum", 0);
                if(!queryAns.exec())
                {
                    QMessageBox::information(this, "Failed", "Query Failed to execute");

                }

                queryAns.prepare(QString("INSERT INTO Answers(answer,question_id,correct) VALUES(:valasz3,:questionID,:correctNum)"));
                queryAns.bindValue(":valasz3", valasz3);
                queryAns.bindValue(":questionID", questionID);
                if (helyesNum==3)
                    queryAns.bindValue(":correctNum", 1);
                else
                    queryAns.bindValue(":correctNum", 0);
                if(!queryAns.exec())
                {
                    QMessageBox::information(this, "Failed", "Query Failed to execute");

                }

                queryAns.prepare(QString("INSERT INTO Answers(answer,question_id,correct) VALUES(:valasz4,:questionID,:correctNum)"));
                queryAns.bindValue(":valasz4", valasz4);
                queryAns.bindValue(":questionID", questionID);
                if (helyesNum==4)
                    queryAns.bindValue(":correctNum", 1);
                else
                    queryAns.bindValue(":correctNum", 0);
                if(!queryAns.exec())
                {
                    QMessageBox::information(this, "Failed", "Query Failed to execute");

                }

                QMessageBox::information(this, "DONE", "Kész" );
                ui->valasz1Mezo->setText("");
                ui->valasz2Mezo->setText("");
                ui->valasz3Mezo->setText("");
                ui->valasz4Mezo->setText("");
                ui->kerdesMezo->setText("");

        }
    }
 }

}
