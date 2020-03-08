#include "databaseconnection.h"

QSqlDatabase DatabaseConnection::getDb() const
{
    return db;
}

DatabaseConnection::DatabaseConnection()
{
    //http://www.phpmyadmin.co/index.php    <-Server
    db=QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("sql2.freesqldatabase.com");
    db.setUserName("sql2326670");      // <-Username
    db.setPassword("bG5%uY1!");         //<-Password
    db.setDatabaseName("sql2326670");
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
