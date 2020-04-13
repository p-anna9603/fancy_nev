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
    explicit jatekFelulet(QMainWindow *qMain, const QString &playerName, DatabaseConnection *db = nullptr, QWidget *parent = nullptr);
    ~jatekFelulet();

private slots:
    void on_fiokomButton_clicked();

    void on_visszaButton_clicked();

    void on_EredmenyButton_clicked();

    void on_pontPush_clicked();

private:
    Ui::jatekFelulet *ui;
    DatabaseConnection *db;
    QString playerName;
    QMainWindow *vissza;
    jatekosAdatok *adatok;
};

#endif // JATEKFELULET_H
