#ifndef KERDESHOZZAADASA_H
#define KERDESHOZZAADASA_H

#include "databaseconnection.h"
#include <QWidget>
#include <string>
#include <QMessageBox>
//#include "mainwindow.h"
#include <QMainWindow>
#include <QtSql>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QSqlDriverPlugin>
#include <QDebug>
#include <QTableView>

namespace Ui {
class kerdesHozzaadasa;
}

class kerdesHozzaadasa : public QWidget
{
    Q_OBJECT

public:
    explicit kerdesHozzaadasa(QWidget *parent = nullptr, DatabaseConnection *db = nullptr);
    ~kerdesHozzaadasa();

private:
    Ui::kerdesHozzaadasa *ui;
    DatabaseConnection *db;

 /* std::string getQuestion() const;
    std::string getValasz1() const;
    std::string getValasz2() const;
    std::string getValasz3() const;
    std::string getValasz4() const;*/
private slots:
    void on_hozzaadButton_clicked();
};

#endif // KERDESHOZZAADASA_H
