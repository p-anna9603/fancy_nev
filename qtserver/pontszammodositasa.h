#ifndef PONTSZAMMODOSITASA_H
#define PONTSZAMMODOSITASA_H

#include <QMainWindow>
#include "databaseconnection.h"

namespace Ui {
class pontszamModositasa;
}

class pontszamModositasa : public QMainWindow
{
    Q_OBJECT

public:
    explicit pontszamModositasa(QWidget *parent = nullptr,DatabaseConnection *db = nullptr);
    ~pontszamModositasa();

private slots:
    void on_mehetGomb_clicked();

private:
    Ui::pontszamModositasa *ui;
    DatabaseConnection *db;
};

#endif // PONTSZAMMODOSITASA_H
