#include "kerdeshozzaadasa.h"
#include "ui_kerdeshozzaadasa.h"
#define N 10
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
    menuLekerdezes();
    //QMessageBox::information(this, "WARNING", "Ne adj hozzá kérdést kategória nélkül!!!");

}
kerdesHozzaadasa::~kerdesHozzaadasa()
{
    delete ui;
}

void kerdesHozzaadasa::menuLekerdezes() const
{
    //qDebug()<<"\nKérdéshozzáadása konstruktor menuLekerdezes()\n";
    QString listaElemek[N];
    QSqlQuery query(QSqlDatabase::database("MyConnect"));
    if(db->getDb().open())
    {
        query.prepare(QString("SELECT category_name FROM Category"));
        int i=0;
        if(query.exec())
        {
            while(query.next())
            {
                listaElemek[i] = query.value(0).toString(); //query.value(oszlopszám), mivel nekem x rekordot ad vissza, de mindig csak ugyanaz az oszlop kell, azaz a nulladik, ezért ez MINDIG nulla lesz
                //qDebug()<<listaElemek[i];
                ++i;
            }
            int meret=i;
            //qDebug()<<meret;
            for (i=0;i<meret;i++)
            {
                ui->listaTargyaknak->addItem(listaElemek[i]);
                //qDebug()<<listaElemek[i];
            }
        }
        else
            qDebug()<<"Error kerdeshozzaadasa: Failed to execute query ";
    }
    else
        qDebug()<<"Error kerdeshozzadasa: Database is not open";
}

void kerdesHozzaadasa::on_hozzaadButton_clicked()
{
    QString kerdes = ui->kerdesMezo->toPlainText();
    QString valasz1 = ui->valasz1Mezo->text();
    QString valasz2 = ui->valasz2Mezo->text();
    QString valasz3 = ui->valasz3Mezo->text();
    QString valasz4 = ui->valasz4Mezo->text();
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
        int category_id;
        query.prepare(QString("SELECT id FROM Category WHERE category_name=:kategoria_neve"));
        QString kategoria_neve=ui->listaTargyaknak->currentText();
        query.bindValue(":kategoria_neve", kategoria_neve);
        qDebug()<<kategoria_neve;
        if (!query.exec())
        {
            QMessageBox::information(this, "Failed", "SELECT id FROM Category WHERE category_name=:kategoria_neve Failed to execute");
            QMessageBox::information(this, "Failed", "category_id has been set to 1 = 'Történelem'");
            category_id=1;
        }
        else
        {
            query.next();
            category_id=(query.value(0).toString().toInt());
        }
        qDebug()<<category_id;
        query.prepare(QString("INSERT INTO Question(question,category_id) VALUES(:kerdes,:id)"));
        query.bindValue(":kerdes", kerdes);
        query.bindValue(":id", category_id);
        if(!query.exec())
        {
            QMessageBox::information(this, "Failed", "INSERT INTO Question(question,category_id) VALUES(:kerdes,:id) Failed to execute");

        }
        else
        {
            query.prepare(QString("SELECT id FROM Question WHERE question=:kerdes"));
            query.bindValue(":kerdes", kerdes);
            if(!query.exec())
            {
                QMessageBox::information(this, "Failed", "SELECT id FROM Question WHERE question=:kerdes Failed to execute");

            }
            while (query.next())
            {
                int questionID = query.value(0).toInt();
                QSqlQuery queryAns(QSqlDatabase::database("MyConnect"));
                queryAns.prepare(QString("INSERT INTO Answers(answer,question_id,correct) VALUES(:valasz1,:questionID,:correctNum)"));
                queryAns.bindValue(":valasz1", valasz1);
                queryAns.bindValue(":questionID", questionID);
                if (helyesNum==1)
                    queryAns.bindValue(":correctNum", 1);   //1-True
                else
                    queryAns.bindValue(":correctNum", 0);   //0-False
                if(!queryAns.exec())
                {
                    QMessageBox::information(this, "Failed", "INSERT INTO Answers(answer,question_id,correct) VALUES(:valasz1,:questionID,:correctNum) Failed to execute");

                }

                queryAns.prepare(QString("INSERT INTO Answers(answer,question_id,correct) VALUES(:valasz2,:questionID,:correctNum)"));
                queryAns.bindValue(":valasz2", valasz2);
                queryAns.bindValue(":questionID", questionID);
                if (helyesNum==2)
                    queryAns.bindValue(":correctNum", 1);   //1 - True
                else
                    queryAns.bindValue(":correctNum", 0);   //0 - False
                if(!queryAns.exec())
                {
                    QMessageBox::information(this, "Failed", "...VALUES(:valasz2,:questionID,:correctNum) Failed to execute");

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
                    QMessageBox::information(this, "Failed", "...VALUES(:valasz3,:questionID,:correctNum) Failed to execute");

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
                    QMessageBox::information(this, "Failed", "...VALUES(:valasz4,:questionID,:correctNum) Failed to execute");

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
