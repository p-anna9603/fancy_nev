#ifndef FELHASZNALOTORLESE_H
#define FELHASZNALOTORLESE_H

#include <QMainWindow>
#include "databaseconnection.h"

namespace Ui {
class felhasznaloTorlese;
}

class felhasznaloTorlese : public QMainWindow
{
    Q_OBJECT

public:
    explicit felhasznaloTorlese(QWidget *parent = nullptr,DatabaseConnection *db = nullptr);
    ~felhasznaloTorlese();

private slots:
    void on_pushButton_clicked();

private:
    Ui::felhasznaloTorlese *ui;
    DatabaseConnection *db;
};

#endif // FELHASZNALOTORLESE_H
