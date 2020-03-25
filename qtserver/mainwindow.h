#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QSqlDriverPlugin>
#include "dialog.h"
#include "databaseconnection.h"
#include "adminfelulet.h"
#include <QDebug>
#include <QTableView>
#include <iostream>
using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();


private:
    Ui::MainWindow *ui;
    //meg ez kell:
    DatabaseConnection* database;
};

#endif // MAINWINDOW_H
