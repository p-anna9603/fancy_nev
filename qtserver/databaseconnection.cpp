#include "databaseconnection.h"

QSqlDatabase DatabaseConnection::getDb() const
{
    qDebug()<< "getDb() fv\n";
    return db;
}

DatabaseConnection::DatabaseConnection()
{
    // https://remotemysql.com/phpmyadmin/index.php  <-Server
    db=QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("remotemysql.com");
    db.setPort(3306);
    db.setUserName("W59wkiPNGD");      // <-Username
    db.setPassword("CXaZWFE9Zj");         //<-Password
    db.setDatabaseName("W59wkiPNGD");
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
