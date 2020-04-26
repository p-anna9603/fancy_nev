#ifndef JATEKFELULET_H
#define JATEKFELULET_H

#include <QMainWindow>
#include "databaseconnection.h"
#include "jatekosadatok.h"
#include "clickablelabel.h"
#include "termeszetikepek.h"
#include "quizfelulet.h"

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

    void on_KartyaPush_clicked();

    void on_pushButton_clicked();

    void Mouse_Pressed();

    void Mouse_PressedOnLittlePic();

    void on_pushButton_4_clicked();

    void on_tortenelemTema_clicked();

    void on_irodalomTema_clicked();

    void on_egyetemTema_clicked();

    void on_sportTema_clicked();

    void on_jatekrolButton_clicked();

    void on_kartya_vasarlas_clicked();

private:
    Ui::jatekFelulet *ui;
    DatabaseConnection *db;
    QString playerName;
    QMainWindow *vissza;
    jatekosAdatok *adatok;
    termeszetiKepek *term;
    int osszPontszam = 0;
    int kerdesId = 0;
    vector<QString> kisKepekLista;

    void getPoints();
    vector<QString> getKisKepLista();



 //   QLabel *term1;
};


#endif // JATEKFELULET_H
