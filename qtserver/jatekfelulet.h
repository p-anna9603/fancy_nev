#ifndef JATEKFELULET_H
#define JATEKFELULET_H

#include <QMainWindow>
#include "databaseconnection.h"
#include "jatekosadatok.h"

namespace Ui {
class jatekFelulet;
}

class jatekFelulet : public QMainWindow
{
    Q_OBJECT

public:
    explicit jatekFelulet(const QString &playerName, DatabaseConnection *db = nullptr, QWidget *parent = nullptr);
    ~jatekFelulet();

private slots:
    void on_pushButton_clicked();

private:
    Ui::jatekFelulet *ui;
    DatabaseConnection *db;
    QString playerName;
};

#endif // JATEKFELULET_H
