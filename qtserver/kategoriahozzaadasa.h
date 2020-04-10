#ifndef KATEGORIAHOZZAADASA_H
#define KATEGORIAHOZZAADASA_H

#include <QMainWindow>
#include "databaseconnection.h"

namespace Ui {
class kategoriaHozzaadasa;
}

class kategoriaHozzaadasa : public QMainWindow
{
    Q_OBJECT

public:
    explicit kategoriaHozzaadasa(QWidget *parent = nullptr,DatabaseConnection *db = nullptr);
    ~kategoriaHozzaadasa();

private slots:
    void on_pushButton_clicked();

private:
    Ui::kategoriaHozzaadasa *ui;
    DatabaseConnection *db;
};

#endif // KATEGORIAHOZZAADASA_H
