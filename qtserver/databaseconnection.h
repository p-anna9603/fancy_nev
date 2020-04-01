#ifndef DATABASECONNECTION_H
#define DATABASECONNECTION_H

#include <QMainWindow>
#include <QtSql>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QSqlDriverPlugin>
#include <QDialog>
#include <QDebug>
#include <iostream>
using namespace std;

class DatabaseConnection
{
    QSqlDatabase db;
public:
    DatabaseConnection();
    QSqlDatabase getDb() const;




};

#endif // DATABASECONNECTION_H
