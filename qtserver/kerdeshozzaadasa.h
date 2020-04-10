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
#include <string>

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
    void menuLekerdezes() const;
private slots:
    void on_hozzaadButton_clicked();
};

#endif // KERDESHOZZAADASA_H
