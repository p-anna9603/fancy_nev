#ifndef JATEKLEIRAS_H
#define JATEKLEIRAS_H

#include <QMainWindow>
#include "databaseconnection.h"
#include <fstream>
#include <streambuf>

namespace Ui {
class jatekLeiras;
}

class jatekLeiras : public QMainWindow
{
    Q_OBJECT

public:
    explicit jatekLeiras(QWidget *parent = nullptr, DatabaseConnection *db=nullptr);
    ~jatekLeiras();
    QString beolvasas() const;

private:
    Ui::jatekLeiras *ui;
    DatabaseConnection *db;
};

#endif // JATEKLEIRAS_H
