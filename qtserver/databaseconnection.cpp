#include "databaseconnection.h"

QSqlDatabase DatabaseConnection::getDb() const
{
    qDebug()<< "getDb() fv\n";
    return db;
}

DatabaseConnection::DatabaseConnection()
{
    //  http://myadmin.contu021.bplaced.net/index.php    <-Server
    db=QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost"); //?????
    db.setUserName("contu021_fancy");      // <-Username
    db.setPassword("EhQXX56Qcdkf4HKC");         //<-Password
    db.setDatabaseName("contu021_quizzy");
    if(db.open())
    {
       qDebug()<<"Connection, Database connected successfully";
    }
    else
    {
        qDebug()<<"Not Connected, Database not connected";
        qDebug()<<db.lastError();
    }
}
