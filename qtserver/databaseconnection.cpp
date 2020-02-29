#include "databaseconnection.h"

QSqlDatabase DatabaseConnection::getDb() const
{
    return db;
}

DatabaseConnection::DatabaseConnection()
{
    db=QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("remotemysql.com");
    db.setUserName("W59wkiPNGD");
    db.setPassword("2JRgxq398t");
    db.setDatabaseName("W59wkiPNGD");
    if(db.open())
    {
       qDebug()<<"Connection, Database connected successfully";
    }
    else
    {
        qDebug()<<"Not Connected, Database not connected";
    }
}
